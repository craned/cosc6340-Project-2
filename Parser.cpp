/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/

#include "Parser.h"

const int CREATE_TABLE_SIZE = 12;
//const int INSERT_INTO_SIZE = 11;
//const int WRITE_CLOSE_SIZE = 5;
//const int DELETE_FROM_SIZE = 11;
//const int UPDATE_SIZE = 5;
//const int WHERE_SIZE = 5;
//const int SET_SIZE = 3;
//const int SHOW_TABLE_SIZE = 10;
//const int SINGLE_OP_SIZE = 1;
//const int DOUBLE_OP_SIZE = 2;
//const int VALUES_FROM_SIZE = 11;
//const int VAL_FROM_REL_SIZE = 20;
//const int PRIMARY_KEY_SIZE = 11;

static int nestedLevel = 0;
static int returningNestedLevel = 0;
static string origQuery = "";

//stack <Table> stack;

const string sError = "ERR:: INVALID INPUT";

/*******************************************************************************
 Read a file and call parse function on each line read
 *******************************************************************************/
bool Parser::readFromFile(string sFileName)
{
  ifstream fhIn; //file handler
  string sLineIn; //Hold the line that is read off file
  int iCount = 0;

  //Open the file and validate it opened properly
  fhIn.open(sFileName.c_str());

  if (!fhIn)
  {
    //Output error message
    printf("|--------------------------------------");
    printf("-----------------------------------------\n");
    printf("| ERROR, file did not open, exiting...\n");
    return false; //Ends function
  }

  //Reading the first line from the file
  getline(fhIn, sLineIn, ';');

  //Formatting
  printf("\n|--------------------------------------");
  printf("-----------------------------------------\n");

  //Loop to read in file information
  while (!fhIn.eof() /*&& iCount < 20*/)
  {
    //Keep a record of lines for writing to file
    vValuesRead.push_back(sLineIn);

    //Parse the line of text and interpret it
    parse(sLineIn);

    //Prepare to loop again, read in next record & update
    getline(fhIn, sLineIn, ';');

    //Increase the counter
    iCount++;
  }

  //Close the file
  fhIn.close();
  return true;
}

/*******************************************************************************
 Writes the relation information to a file
 *******************************************************************************/
bool Parser::writeToFile(string sFilename)
{
  fstream outputFile;
  //open the file and write the contents of the class vector in there
  //outputFile.open(sFilename + ".db");
  for (size_t i = 0; i < vValuesRead.size(); ++i)
  {
    outputFile << vValuesRead[i] << '\n';
  }
  outputFile.close();
  return true;
}

/*******************************************************************************
 Remove any additional spaces from the string
 *******************************************************************************/
string Parser::removeSpaces(string sLineIn)
{
  string sOut = "";
  for (size_t i = 0; i < sLineIn.length(); ++i)
  {
    //Apend any values that are not spaces
    if (sLineIn[i] != ' ')
    {
      sOut += sLineIn[i];
    }
  }

  return sOut;
}

/*******************************************************************************
 Parse the line in and call the appropiate functions
 *******************************************************************************/
int Parser::parse(string sLineIn)
{
	nestedLevel = 0;
  //Declare and initialize variables
  //string sTemp;

    //Output the line we are working with so we know we have the parsing correct
    //printf("\n%s\n", sLineIn.c_str());
    origQuery = sLineIn;
    if (!checkParenthesis(sLineIn)) {
  		cout << "ERROR: the parentheses do not match" << endl;
  		return 0;
  	}
    if (!semicolonExists(sLineIn)) {
  		cout << "ERROR: there is no semicolon" << endl;
  		return 0;
  	}
  	
	selectQ.clearAll();
    //cout << "parenthesis ok" << endl;
    if (findCreateTable(sLineIn)) {
        //cout << "Created table " << sLineIn << endl;
    } else if (findInsertInto(sLineIn)) {
        cout << "Values Inserted" << endl;
    } else if (findSelectParen(sLineIn, "")) {//findSelectNew(sLineIn, "")) {
    //} else if (findSelect(sLineIn)) {
    	//selectQ = new SelectQ();
        //cout << "Select found" << endl;
    } else if (findQuit(sLineIn)) {
        cout << "Finished" << endl;
        return 0;
    } else if (findShowTables(sLineIn)) {
        cout << "Show tables" << endl;
    } else if (findShowTable(sLineIn)) { // needs to go before findShowTable
        cout << "Show table" << endl;
    } else if (findDropTable(sLineIn)) {
        cout << "Drop table" << endl;
    } else {
        cout << "ERROR: no match for the query could be found" << endl;
    }

	return 1;
}

bool Parser::semicolonExists(string sLineIn) 
{
	size_t semicolon = sLineIn.find(";");
	if (semicolon == string::npos) {
		return false;
	}
	return true;
}

void Parser::read(){
	e.read();
}

/*******************************************************************************
 Function that sees if CREATE TABLE is in the string and executes the command
 correct format = CREATE TABLE () PRIMARY KEY ()
 *******************************************************************************/
bool Parser::findCreateTable(string sLineIn)
{
    size_t iPosStart = sLineIn.find("CREATE TABLE");

    //Execute if create table was found in the string
    if (iPosStart != string::npos)
    {
        size_t iPosEnd = sLineIn.find("(", iPosStart + 1);

        //execute if '(' was found in the string
        if (iPosEnd != string::npos)
        {
            //get the table name
            string sTableName = sLineIn.substr(iPosStart + CREATE_TABLE_SIZE,
                                               iPosEnd - CREATE_TABLE_SIZE);

            //cout << "tableName create" << sTableName << endl;

            //reposition the position values
            iPosStart = iPosEnd + 1;
            iPosEnd = sLineIn.find("PRIMARY KEY", iPosStart + 1);
            if (iPosEnd == string::npos) {
                iPosEnd = sLineIn.find("PRIMARY KEY", iPosStart + 1);
            }

            //Execute if primary key was found in string
            if (iPosEnd != string::npos)
            {
                //get the column names
                string sColumns = sLineIn.substr(iPosStart,
                                                 iPosEnd - iPosStart);

                //cout << "columns " << sColumns << endl;

                //reposition the position values
                iPosStart = iPosEnd;
                iPosStart = sLineIn.find("(", iPosEnd) + 1;
                iPosEnd = sLineIn.find(")", iPosStart);

                //execute if ')' was found in the string
                if (iPosEnd != string::npos)
                {
                    //get the primary keys
                    string sPrimaryKeys = sLineIn.substr(iPosStart,
                                                         iPosEnd - iPosStart);

                    //cout << "primary keys " << sPrimaryKeys << endl;

                    //remove the spaces from the name of the table
                    sTableName = Utilities::cleanSpaces(sTableName);

                    //call the create table function after the helper functions
                    e.createTable(sTableName, createColVector(sColumns),
                                    createVector(sPrimaryKeys));
                                    
                    //cout << "table " << sTableName << " created " << endl;
                    
                    return true;
                }
            }
        }
    }

    return false;
}

bool Parser::findSelectParen(string sLineIn, string insertSelectTable)
{
	size_t openParen = sLineIn.find("(", 0);
	//cout << "findSelectParen " << sLineIn << endl;
	
	
	if (openParen != string::npos) {
		for (int i = 0; i < sLineIn.length(); i++) {
		//cout << "starting" << endl;
			char queryChar = sLineIn[i];
			if (queryChar == '(') {
				parens.push(i);
			} else if (queryChar == ')') {
				int leftParenIndex = parens.top();
				int subQueryBeg = leftParenIndex + 1;
				//cout << "open paren " << leftParenIndex << endl;
				//cout << "close paren " << i << endl;
				string query = sLineIn.substr(subQueryBeg, i - subQueryBeg);
				//cout << "subquery " << query << endl;
				
				int begTempTable = i;
				while (!isalnum(sLineIn[begTempTable])) {
					begTempTable++;
				}
				
				string tempTable = "";
				while (isalnum(sLineIn[begTempTable])) {
					tempTable += sLineIn[begTempTable];
					begTempTable++;
				}
												
				bool result = findSelectNew(query, tempTable);
				parens.pop();
				
				sLineIn.replace(leftParenIndex, (i+1) - (leftParenIndex), "");
				i = 0;
				while (parens.size() != 0) {
					parens.pop();
				}
				//cout << "query replaced" << endl;//*/
				if (!result) {
					//cout << "bad result" << endl;
					return false;
				}
				
				//cout << "for() end" << endl;
				break;
			}
		}
		
		//if (parens.size() > 0) {
			findSelectParen(sLineIn, insertSelectTable);
		//}
		
		//cout << "subquery " << sLineIn << endl;
		//return findSelectNew(sLineIn, "");
	} else {
		//cout << "query " << sLineIn << endl;
		
		return findSelectNew(sLineIn, insertSelectTable);
	}
}

bool Parser::findSelectNew(string sLineIn, string insertSelectTempName)
{
	if (nestedLevel > 3) {
		cout << "ERROR: too many nested levels" << endl;
		return false;
	}
	
	size_t iPosStart = sLineIn.find("SELECT");
	
	selectQ.clearAll();
	selectQ.setTempTable(insertSelectTempName);

    if (iPosStart != string::npos)
    {
        //cout << "Select found" << endl;
        iPosStart += 6;
        size_t iPosEnd1 = sLineIn.find("FROM", iPosStart);

        if (iPosEnd1 != string::npos)
        {
            //cout << "From found" << endl;
            string colNames = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
            //cout << "colNames " << colNames << endl;
            colNames = Utilities::cleanSpaces(colNames);
            selectQ.setSelectCols(colNames);

            iPosStart = iPosEnd1 + 4 + 1/*for the space*/;	
            
            size_t iPosSemiColon = sLineIn.find(";", iPosStart);
			size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
			size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
            size_t iPosOn = sLineIn.find("ON", iPosStart);
			//size_t iPosGroupBy = sLineIn.find("GROUP BY", iPosStart);
			//size_t iPosOrderBy = sLineIn.find("ORDER BY", iPosStart);
			
			string fromTable = "";
			string joinTable = "";
			string joinFilter = "";
			string whereFilter = "";
            
            // get the from table; we already know it exists
            if (iPosJoin != string::npos) {
				fromTable = sLineIn.substr(iPosStart, iPosJoin - iPosStart);
			} else if (iPosWhere != string::npos) {
				fromTable = sLineIn.substr(iPosStart, iPosWhere - iPosStart);
			} else if (iPosSemiColon != string::npos) {
				fromTable = sLineIn.substr(iPosStart, iPosSemiColon - iPosStart);
			} else {
				fromTable = sLineIn.substr(iPosStart, string::npos);
			}
			fromTable = Utilities::cleanSpaces(fromTable);
			selectQ.setFromTable(fromTable);
			
			// don't want to check for join too early
			if (iPosJoin != string::npos) {
	            
				iPosJoin += 4;
				if (iPosOn != string::npos && iPosOn) {
					joinTable = sLineIn.substr(iPosJoin, iPosOn - iPosJoin);
				} else if (iPosWhere != string::npos) {
					joinTable = sLineIn.substr(iPosJoin, iPosWhere - iPosJoin);
				} else if (iPosSemiColon != string::npos) {
					joinTable = sLineIn.substr(iPosJoin, iPosSemiColon - iPosJoin);
				} else {
					joinTable = sLineIn.substr(iPosJoin, string::npos);
				}
				
				joinTable = Utilities::cleanSpaces(joinTable);
				selectQ.setJoinTable(joinTable);
			}
			
			//cout << "joinFilter " << joinFilter << endl;
			// don't want to check for on too early
			if (iPosOn != string::npos &&
				!joinTable.empty())
			{
				//cout << "checking join filter" << endl;
				iPosOn += 2;
				if (iPosWhere != string::npos) {
					joinFilter = sLineIn.substr(iPosOn, iPosWhere - iPosOn);
				} else if (iPosSemiColon != string::npos) {
					joinFilter = sLineIn.substr(iPosOn, iPosSemiColon - iPosOn);
				} else {
					joinFilter = sLineIn.substr(iPosOn, string::npos);
				}
				
				joinFilter = Utilities::cleanSpaces(joinFilter);
				selectQ.setJoinFilter(joinFilter);
			}
			
			if (iPosWhere != string::npos) {
				iPosWhere += 5;
				
				if (iPosSemiColon != string::npos) {
					whereFilter = sLineIn.substr(iPosWhere, iPosSemiColon - iPosWhere);
				} else {
					whereFilter = sLineIn.substr(iPosWhere, string::npos);
				}
				whereFilter = Utilities::cleanSpaces(whereFilter);
				selectQ.setWhereFilter(whereFilter);
			}
			
			// group by
			
			// order by
			
			selectQ.printAll();
			bool result = e.executeSelect(selectQ.getFromTable(),
							createVector(selectQ.getSelectCols()),
							selectQ.getTempTable(),
							selectQ.getWhereFilter(),
 							selectQ.getJoinTable(),
	                  		selectQ.getJoinFilter());//*/
	        
	        if (!result) {
	        	return false;
	        }
		    
		    return true;
		}
	} else {
		return false;
	}
	
	return true;
}

/*******************************************************************************
 Function that sees if INSERT INTO is in the string and executes the command
 handles both INSERT FROM and INSERT FROM RELATION
 *******************************************************************************/
bool Parser::findInsertInto(string sLineIn)
{
    size_t iPosStart = sLineIn.find("INSERT INTO");

    if (iPosStart != string::npos)
    {
	    //cout << "insert into found" << endl;
        iPosStart += 11;
        size_t iPosValues = sLineIn.find("VALUES", iPosStart);
        size_t iPosEnd1;
        
        // insert into T values (1, 'string', 5);
        // insert into T select B From T1;
        // insert into T3 select T.A from T1 order by B;

        //Execute if values from relation is found
        if (iPosValues != string::npos) // values
        {
        	//Get the name of the table from the string 
            string tableName = sLineIn.substr(iPosStart, 
                                                  iPosValues - iPosStart); 
            tableName = Utilities::cleanSpaces(tableName);
            //cout << tableName << endl;

            //reposition the iterators to get the row values
            iPosStart = sLineIn.find("(") + 1;
            iPosValues = sLineIn.find(")");

            if (iPosStart != string::npos && iPosValues != string::npos)
            {
                //Get the row attributes from the string
                string sRow = sLineIn.substr(iPosStart,
                                             iPosValues - iPosStart);
                //cout << "values " << sRow << endl;
                //values = Utilities::cleanSpaces(values);
                //cout << "values " << values << endl;

                iPosStart = iPosValues;

                //Clean up and add the row to the table
                bool valid= e.createValidate(sLineIn,tableName);
                if(valid==true)
                {
                	vector<tuple<int, string> > rowVector = createRowVector(sRow);
					//cout << "adding Row parser" << endl;
		         	e.addRow(tableName, rowVector);
					//cout << "addedRow parser" << endl;
					
                	return true;
                } else {
                	return false;
                }
            }
        }//change
            //Execute if values from is found
        else if ((iPosEnd1 = sLineIn.find("SELECT", iPosStart)) != string::npos)
        {
        	string selectSubQ = sLineIn.substr(iPosEnd1, string::npos);
            //Get the name of the table from the string
            string tableIntoName = sLineIn.substr(iPosStart, iPosEnd1 - iPosStart);
            //cout << "tableIntoName " << tableIntoName << endl;
            tableIntoName = Utilities::cleanSpaces(tableIntoName);
            //cout << "insert into tableName " << tableName << endl;
            
            /*iPosStart = iPosEnd1 + 6;
            iPosEnd1 = sLineIn.find("FROM", iPosStart);
            string colNames = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
            //colNames = Utilities::cleanSpaces(colNames);
            //cout << "from colNames " << colNames << endl;

            //reposition the iterators to get the row values
            iPosStart = iPosEnd1 + 4;//*/
            
            // Group By isn't required for Phase 1, but this should work when it is
            /*if ((iPosEnd1 = sLineIn.find("ORDER BY", iPosStart)) != string::npos) {
                string tableName = sLineIn.substr(iPosStart,
                                             	iPosEnd1 - iPosStart);
                                             
                //cout << "tableName " << tableName << endl;
                
            	iPosStart = iPosEnd1 + 8;
            	iPosEnd1 = sLineIn.find(";");
            	if (iPosEnd1 != string::npos) {
            		string groupByCol = sLineIn.substr(iPosStart,
            								iPosEnd1 - iPosStart);
            		cout << "group by col " << groupByCol << endl;
            	}
            } else //*/
            
            string tempFromName = "insInto" + tableIntoName;
            findSelectParen(selectSubQ, tempFromName);
            
            //string insertInto = "INSERT INTO 
            
            //cout << tempFromName << " " << tableIntoName << endl;
            e.insertFromSelect(tempFromName, tableIntoName);
            if ((iPosEnd1 = sLineIn.find(";")) != string::npos)
            {
                //Get the tableName from the string
                string tableName = sLineIn.substr(iPosStart,
                                             	iPosEnd1 - iPosStart);
                                             
                //cout << "tableName " << tableName << endl;

                return true;
            }
        }
    }

    return false;
}

/*******************************************************************************
 Function that sees if DROP is in the string and executes the command
 *******************************************************************************/
bool Parser::findDropTable(string sLineIn)
{
	size_t iPosStart = sLineIn.find("DROP TABLE");
    if (iPosStart != string::npos)
    {
	    iPosStart = iPosStart + 10;
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart,
										sLineIn.find(";") - iPosStart);
        sTableName = Utilities::cleanSpaces(sTableName);

        //cout << "tableName " << sTableName << endl;

        // call the function to display table
        e.dropTable(sTableName);

		return true;
	} else {
		return false;
	}
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTable(string sLineIn)
{
	size_t iPosStart = sLineIn.find("SHOW TABLE");
    if (iPosStart != string::npos)
    {
	    iPosStart = iPosStart + 10;
        //Get the name of the table from the string
        string sTableName = sLineIn.substr(iPosStart,
										sLineIn.find(";") - iPosStart);
        sTableName = Utilities::cleanSpaces(sTableName);

        //cout << "tableName " << sTableName << endl;

        // call the function to display table
        e.displayTable(sTableName);

		return true;
	} else {
		return false;
	}
}

/*******************************************************************************
 Function that sees if SHOW TABLES is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTables(string sLineIn)
{
	size_t iPosStart = sLineIn.find("SHOW TABLES;");

    if (iPosStart != string::npos)
    {
        //cout << "found show tables" << endl;
        e.displayTableSchemas();
		return true;
	} else {
		return false;
	}
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findQuit(string sLineIn)
{
	//cout << sLineIn << endl;
  size_t iPosStart = sLineIn.find("QUIT;");

  if (iPosStart != string::npos)
  {
    //cout << "quit" << endl;
	  e.executeQuit();
	  
	  e.writetofile();

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if the parenthesis are balanced in a line
 *******************************************************************************/
bool Parser::checkParenthesis(string sLineIn)
{
  int iBalance = 0;
  for (size_t i = 0; i < sLineIn.length(); ++i)
  {
    if (sLineIn[i] == '(')
    {
      iBalance++;
    }
    else if (sLineIn[i] == ')')
    {
      iBalance--;
    }
    if (iBalance < 0)
    {
      return false;
    }
  }

  if (iBalance == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if the parenthesis are balanced in a line
 *******************************************************************************/
size_t Parser::getMatchingClosingParen(string sLineIn, size_t start)
{
  int iBalance = 0;
  size_t i = start;
  for (; i < sLineIn.length(); ++i)
  {
    if (sLineIn[i] == '(')
    {
      iBalance++;
    }
    else if (sLineIn[i] == ')')
    {
      iBalance--;
    }
	  if (iBalance == 0)
	  {
		return i;
	  }
  }
}

/*******************************************************************************
 Function that does the select
 *******************************************************************************/
void Parser::select(string sNewTableName, string sRestOfLine)
{
  size_t iPos = sRestOfLine.find("select");

  if (iPos != string::npos)
  {
    size_t iParenth1 = sRestOfLine.find("(");
    size_t iParenth2 = sRestOfLine.find(")", iParenth1 + 1);
    string sValues = removeSpaces(
        sRestOfLine.substr(iParenth1 + 1, iParenth2 - iParenth1));
    string sTableNameIn = Utilities::cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
//    vector < string > vValues = makeTokens(sValues);

    if (sTableNameIn == sNewTableName)
    {
//      if (vValues[0] == "Date")
      {
//        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
//            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
      }
//      else
//      {
//        e.selection(sNewTableName, sTableNameIn + " 2", vValues[1], vValues[0],
//            vValues[2]);
//      }

      //delete old table
//      e.dropTable(sTableNameIn);

      //rename new table to old name
//      e.renameTable(sTableNameIn + " 2", sNewTableName);
    }
    else
    {
//      if (vValues[0] == "Date")
//      {
//        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
//            vValues[2] + vValues[3] + vValues[4] + vValues[5] + vValues[6]);
//      }
//      else
//      {
//        e.selection(sTableNameIn, sNewTableName, vValues[1], vValues[0],
//            vValues[2]);
//      }

    }
  }
}
/*******************************************************************************
 Takes in a string, parses it, and creates a vector of strings to send back
 *******************************************************************************/
vector<string> Parser::createVector(string sLineIn)
{
    vector < string > vReturn;
    int iPosStart = 0;
    int iPosEnd = 0;
    int iCount = 0;
    int iAmountOfCommas = 0;

    //Check to see how many commas are in the string
    for (size_t i = 0; i < sLineIn.length(); ++i)
    {
        //Execute if the comma is found and increment the counter
        if (sLineIn[i] == ',')
        {
            iAmountOfCommas++;
        }
    }

    //Loop to parser out the comma separated values
    while (iCount <= iAmountOfCommas)
    {
        iPosEnd = sLineIn.find(",", iPosStart + 1);
        string value = sLineIn.substr(iPosStart, iPosEnd - iPosStart);
        if (value.find("\'") != string::npos) {
        	value = Utilities::cleanSpaces(value);
        }
        ////cout << "value " << value << endl;
        vReturn.push_back(value);
        iPosStart = iPosEnd + 1;
        iCount++;
    }

    //clean up the words that were separated out
//    for (size_t i = 0; i < vReturn.size(); ++i)
//    {
//        vReturn[i] = Utilities::cleanSpaces(vReturn[i]);
//        //cout<<"vReturn: "<<vReturn[i]<<endl;
//    }

    return vReturn;
}





/*******************************************************************************
 Takes in a string, parses it, and creates a vector of strings to send back
 *******************************************************************************/
vector<tuple<int, string> > Parser::createRowVector(string sLineIn)
{
    vector < tuple<int, string> > vRowOut;
    vector < string > vRowAttributes = createVector(sLineIn);

    for (size_t i = 0; i < vRowAttributes.size(); i++)
    {
        int iColIndex = i;
        string sName = vRowAttributes[i];
        ////cout << "sName " << sName << endl;

        vRowOut.push_back(make_tuple(iColIndex, sName));
    }
    return vRowOut;
}
/*******************************************************************************
 Takes in a string, parses it, and creates a vector of columns to send back
 *******************************************************************************/
vector<tuple<string, string, int, bool> > Parser::createColVector(string sLineIn)
{
    //<type, name, primarykey>
    vector < tuple<string, string, int, bool> > vColVectorOut;
    vector < string > vCol = createVector(sLineIn);

    for (size_t i = 0; i < vCol.size(); i++)
    {
        string sType, sName;
        int length = 1;

        //See what type of column it is and create a tuple with the name & type
        size_t iVar = vCol[i].find("CHAR");
        if (iVar != string::npos)
        {
            sType = "string";
            string col = vCol[i];
            sName = col.substr(0, iVar);
            size_t leftParen = col.find("(") + 1;
            size_t rightParen = col.find(")");
            length = stoi(col.substr(leftParen, rightParen - leftParen));
            //cout << "char length " << length << endl;
        }

        size_t iInt = vCol[i].find("INT");
        if (iInt != string::npos)
        {
            sType = "int";
            sName = vCol[i].substr(0, iInt);
        }
        
        ////cout << "colname " << sName << endl;
        sName = Utilities::cleanSpaces(sName);
        //push the newly created column into the vector to send back
        vColVectorOut.push_back(make_tuple(sName, sType, length, false));

    }
    return vColVectorOut;
}
