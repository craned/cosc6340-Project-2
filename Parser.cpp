/*******************************************************************************
 File: Parser.cpp

 Authors: Gustavo Pedroso UIN: 423002834
 Levi Clark      UIN: 520007880
 Terry Chen      UIN: 121007055
 Daniel He       UIN: 620006827

 Department of Computer Science
 Texas A&M University
 Date  : 2/2/2014

 Formatting: * 80 pt width is used for code, for the most part
 * Hungarian naming convention is used for variables
 * Comments are applied for explanations
 * Spacing and brackets are applied for readability

 This file contains the implementation for the parser
 *******************************************************************************/

#include "Parser.h"

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int DELETE_FROM_SIZE = 11;
const int UPDATE_SIZE = 5;
const int WHERE_SIZE = 5;
const int SET_SIZE = 3;
const int SHOW_TABLE_SIZE = 10;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int VAL_FROM_REL_SIZE = 20;
const int PRIMARY_KEY_SIZE = 11;

static int nestedLevel = 0;
static int returningNestedLevel = 1;
static string origQuery = "";

//stack <Table> stack;

//Array of String identifiers for non-symbolic operations
static const string expr[] =
{ "select", "project", "rename", "natural-join" };

//Array of String identifiers for symbolic comparisons
static const string operant[] =
{ "==", "!=", "<=", ">=", "<", ">" };

//Array of Char identifiers for symbolic operations
static const char symExpr[] =
{ '+', '-', '*' };

//Array of all symbols
static const string allOp[] =
{ "==", "!=", "<=", ">=", "<", ">", "+", "-", "*" };

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
string Parser::cleanSpaces(string sLineIn)
{
  string sOut = "";
  for (size_t i = 0; i < sLineIn.length(); ++i)
  {
    //Append the value from the string into the return string, if its alpha
    if (isalnum(sLineIn[i]) || sLineIn[i] == '_' || sLineIn[i] == '/' ||
    	sLineIn[i] == '*' || sLineIn[i] == '=' || sLineIn[i] == '.')
    {
      sOut += sLineIn[i];
    }
  }

  return sOut;
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
    cout << sLineIn << endl;
    origQuery = sLineIn;
    if (!checkParenthesis(sLineIn)) {
  		printf("ERROR: the parentheses do not match\n");
  		return 0;
  	}
    if (!semicolonExists(sLineIn)) {
  		printf("ERROR: there is no semicolon\n");
  		return 0;
  	}
  	
    cout << "parenthesis ok" << endl;
    if (findCreateTable(sLineIn)) {
        printf("CREATE TABLE was found in this line, executed.\n");
    } else if (findInsertInto(sLineIn)) {
        cout << "Insert Into found" << endl;
    } else if (findSelect(sLineIn)) {
        cout << "Select found" << endl;
    } else if (findQuit(sLineIn)) {
        cout << "Finished" << endl;
        return 0;
    } else if (findShowTables(sLineIn)) {
        cout << "Show tables" << endl;
    } else if (findShowTable(sLineIn)) { // needs to go before findShowTable
        cout << "Show table" << endl;
    } else {
        printf("ERROR: no match for the query could be found\n");
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
                                               iPosEnd - CREATE_TABLE_SIZE - 1);

            cout << "table name " << sTableName << endl;

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

                cout << "columns " << sColumns << endl;

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

                    cout << "primary keys " << sPrimaryKeys << endl;

                    //remove the spaces from the name of the table
                    sTableName = Parser::cleanSpaces(sTableName);

                    //call the create table function after the helper functions
                    e.createTable(sTableName, createColVector(sColumns),
                      	createVector(sPrimaryKeys));

                    return true;
                }
            }
        }
    }

    return false;
}

bool Parser::findSelect(string sLineIn)
{
    size_t iPosStart = sLineIn.find("SELECT");

    if (iPosStart != string::npos)
    {
        cout << "Select found" << endl;
        iPosStart += 6;
        size_t iPosEnd1 = sLineIn.find("FROM", iPosStart);

        if (iPosEnd1 != string::npos)
        {
            cout << "From found" << endl;
            string colNames = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
            cout << "colNames " << colNames << endl;

            iPosStart = iPosEnd1 + 4 + 1/*for the space*/;

			// is it nested?
            size_t nestedSelectPos = sLineIn.find("(", iPosStart);
            if (nestedSelectPos != string::npos) {
                nestedLevel++;
                cout << "detected nested query" << endl;
                if (nestedLevel > 3) {
                    cout << "Too many nested SELECT statements" << endl;
                    return false;
                }
                iPosStart += sLineIn.find("FROM") + 4;
                string nestedSelect = sLineIn.substr(nestedSelectPos+1);

                // recursion starts
                this->findSelect(nestedSelect);
                cout << "returned from recursion" << endl;
                // ok, now start using origQuery

                // find temporary table name
                iPosStart = origQuery.find(")", returningNestedLevel) + 1;
                iPosEnd1 = origQuery.find(")", iPosStart);

                if (iPosEnd1 == string::npos) {
                    iPosEnd1 = origQuery.find(";", iPosStart);
                }

                if (iPosEnd1 != string::npos)
                {
                    string tableName = origQuery.substr(iPosStart,
                                                        iPosEnd1 - iPosStart);
                    tableName = Parser::cleanSpaces(tableName);
                    returningNestedLevel = iPosEnd1 - 1;
                    cout << "tableName " << tableName << endl;
                    cout << "colNames " << colNames << endl;
                    return true;
                }
            } else {
                if (nestedLevel == 0) {
                    
                    size_t iPosSemiColon = sLineIn.find(";", iPosStart);
	             	
	             	size_t iPosTableSpace = sLineIn.find(" ", iPosStart);
	             	string tableName = "";
	             	if (iPosTableSpace != string::npos) {
		             	tableName = sLineIn.substr(iPosStart,
	             									iPosTableSpace - iPosStart);
	                	cout << "space tableName " << endl;
	          		} else {
		             	tableName = sLineIn.substr(iPosStart,
	             									iPosSemiColon - iPosStart);
	                	cout << "semic tableName " << endl;
	          		}
	                cout << "tableName " << tableName << endl;
	                
	                size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
	                string joinTable = "";
	                string joinFilter = "";
	             	if (iPosJoin != string::npos) {
	             		iPosStart = iPosJoin + 4 + 1/*space after JOIN*/;
		                size_t iPosSpace = sLineIn.find(" ", iPosStart);
		                joinTable = cleanSpaces(sLineIn.substr(iPosStart, 
		                							iPosSpace - iPosStart));
		                cout << "joinTable " << joinTable << endl;
		                
		                size_t iPosOn = sLineIn.find("ON", iPosStart);
	             		if (iPosOn != string::npos) {
			                size_t iPosEqual = sLineIn.find("=", iPosOn) + 1;
			                size_t iPosTableDotCol = sLineIn.find(".", iPosEqual);
			                size_t iPosJoinEnd = sLineIn.find(" ", iPosTableDotCol);
	             			iPosOn += 2;
	             			joinFilter = cleanSpaces(sLineIn.substr(iPosOn,
	             											iPosJoinEnd - iPosOn));
	             			cout << "joinFilter " << joinFilter << endl;
	             		}
	             	}
	             	
	                size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
	                //cout << "after poswhere " << iPosWhere << endl;
	                string whereFilter = "";
	             	if (iPosWhere != string::npos) {
	             		size_t iPosWhereFilter = iPosWhere + 5;
		                string whereFilter = cleanSpaces(sLineIn.substr(iPosWhereFilter,
		                                            iPosSemiColon - iPosWhereFilter));
		                cout << "where " << whereFilter << endl;
	             	}
	                
	                e.executeSelect(tableName, colNames, whereFilter,
	                				joinTable, joinFilter);
	                return true;
                } else {
                    iPosEnd1 = sLineIn.find(")", iPosStart);
                    returningNestedLevel = iPosEnd1 - 1;
                    if (iPosEnd1 != string::npos)
                    {
                        //cout << sLineIn << endl;
                        string tableName = sLineIn.substr(iPosStart,
                                                          iPosEnd1 - iPosStart);
                        cout << "tableName " << tableName << endl;
                        return true;
                    }
                }
            }
        }
    } else if (nestedLevel > 0) {
        return false;
    }

    return false;
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
	    cout << "insert into found" << endl;
        iPosStart += 11;
        size_t iPosEnd1 = sLineIn.find("VALUES", iPosStart);
        //size_t iPosEnd2 = sLineIn.find("VALUES FROM", iPosStart + 1);
        
        // insert into T values (1, 'string', 5);
        // insert into T select B From T1;
        // insert into T3 select T.A from T1 order by B;

        //Execute if values from relation is found
        if (iPosEnd1 != string::npos) // values
        {
            //Get the name of the table from the string
            string sTableNameOut = sLineIn.substr(iPosStart,
                                                  iPosEnd1 - iPosStart);
            sTableNameOut = Parser::cleanSpaces(sTableNameOut);
            cout << sTableNameOut << endl;

            //reposition the iterators to get the row values
            iPosStart = sLineIn.find("(") + 1;
            iPosEnd1 = sLineIn.find(")");

            if (iPosStart != string::npos && iPosEnd1 != string::npos)
            {
                //Get the row attributes from the string
                string sRow = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
                cout << "values " << sRow << endl;
                //values = cleanSpaces(values);
                //cout << "values " << values << endl;

                iPosStart = iPosEnd1;

//                string sRestOfLine = sLineIn.substr(iPosStart, iPosEnd1);

//                sRestOfLine = removeSpaces(sRestOfLine);

                //WE NEED THE TREE HERE!!!!!!!!!

                //Clean up and add the row to the table
                vector<tuple<int, string> > rowVector = createRowVector(sRow);
                e.addRow(sTableNameOut, rowVector);

                return true;
            }
        }//change
            //Execute if values from is found
        else if ((iPosEnd1 = sLineIn.find("SELECT", iPosStart)) != string::npos)
        {
            //Get the name of the table from the string
            iPosStart = iPosEnd1 + 6;
            iPosEnd1 = sLineIn.find("FROM", iPosStart);
            string colNames = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
            //colNames = cleanSpaces(colNames);
            cout << "from colNames " << colNames << endl;

            //reposition the iterators to get the row values
            iPosStart = iPosEnd1 + 4;
            
            // Group By isn't required for Phase 1, but this should work when it is
            /*if ((iPosEnd1 = sLineIn.find("ORDER BY", iPosStart)) != string::npos) {
            
                string tableName = sLineIn.substr(iPosStart,
                                             	iPosEnd1 - iPosStart);
                                             
                cout << "tableName " << tableName << endl;
                
            	iPosStart = iPosEnd1 + 8;
            	iPosEnd1 = sLineIn.find(";");
            	if (iPosEnd1 != string::npos) {
            		string groupByCol = sLineIn.substr(iPosStart,
            								iPosEnd1 - iPosStart);
            		cout << "group by col " << groupByCol << endl;
            	}
            } else //*/
            if ((iPosEnd1 = sLineIn.find(";")) != string::npos)
            {
                //Get the tableName from the string
                string tableName = sLineIn.substr(iPosStart,
                                             	iPosEnd1 - iPosStart);
                                             
                cout << "tableName " << tableName << endl;

                return true;
            }
        }
    }

    return false;
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTable(string sLineIn)
{
  size_t iPosStart = sLineIn.find("SHOW TABLE");

  if (iPosStart != string::npos)
  {
    //Get the name of the table from the string
    string sTableName = sLineIn.substr(iPosStart + SHOW_TABLE_SIZE);
    sTableName = Parser::cleanSpaces(sTableName);
    
    cout << "table name " << sTableName << endl;

        cout << "table name " << sTableName << endl;

       // call the function to display table
       e.displayTable(sTableName);

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findShowTables(string sLineIn)
{
  size_t iPosStart = sLineIn.find("SHOW TABLES;");

  if (iPosStart != string::npos)
  {
	cout << "found show table" << endl;
	e.displayTableSchemas();

    return true;
  }
  else
  {
    return false;
  }
}

/*******************************************************************************
 Function that sees if SHOW is in the string and executes the command
 *******************************************************************************/
bool Parser::findQuit(string sLineIn)
{
	cout << sLineIn << endl;
  size_t iPosStart = sLineIn.find("QUIT;");

  if (iPosStart != string::npos)
  {
    cout << "quit" << endl;

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
    string sTableNameIn = Parser::cleanSpaces(sRestOfLine.substr(iParenth2 + 1));
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
        vReturn.push_back(sLineIn.substr(iPosStart, iPosEnd - iPosStart));
        iPosStart = iPosEnd + 1;
        iCount++;
    }

    //clean up the words that were separated out
    //for (int i = 0; i < vReturn.size(); ++i)
    {
        //vReturn[i] = cleanSpaces(vReturn[i]);
        //cout<<"vReturn: "<<vReturn[i]<<endl;
    }

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
            cout << "char length " << length << endl;
        }

        size_t iInt = vCol[i].find("INT");
        if (iInt != string::npos)
        {
            sType = "int";
            sName = vCol[i].substr(0, iInt);
        }
        
        //cout << "colname " << sName << endl;

        //push the newly created column into the vector to send back
        vColVectorOut.push_back(make_tuple(sName, sType, length, false));

    }
    return vColVectorOut;
}

