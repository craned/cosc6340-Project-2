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
  		printf("ERROR: the parentheses do not match\n");
  		return 0;
  	}
    if (!semicolonExists(sLineIn)) {
  		printf("ERROR: there is no semicolon\n");
  		return 0;
  	}
  	
    cout << "parenthesis ok" << endl;
    if (findCreateTable(sLineIn)) {
        //cout << "Created table " << sLineIn << endl;
    } else if (findInsertInto(sLineIn)) {
        cout << "Values Inserted" << endl;
    } else if (findSelectNew(sLineIn, "")) {
    //} else if (findSelect(sLineIn)) {
    	//selectQ = new SelectQ();
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
                                               iPosEnd - CREATE_TABLE_SIZE - 1);

            cout << "tableName create" << sTableName << endl;

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
                    sTableName = Utilities::cleanSpaces(sTableName);

                    //call the create table function after the helper functions
                    e.createTable(sTableName, createColVector(sColumns),
                                    createVector(sPrimaryKeys));
                                    
                    cout << "table " << sTableName << " created " << endl;
                     
                    e.writetofile();
                    return true;
                }
            }
        }
    }

    return false;
}

bool queryIsNested = false;
bool returnedFromRecursion = false;
bool Parser::findSelectNew(string sLineIn, string insertSelectTempName)
{
	if (nestedLevel > 3) {
		cout << "ERROR: too many nested levels" << endl;
		return false;
	}
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
            selectQ.setSelectCols(colNames);

            iPosStart = iPosEnd1 + 4 + 1/*for the space*/;	
            
            size_t iPosSemiColon = sLineIn.find(";", iPosStart);
			size_t iPosLParen = sLineIn.find("(", iPosStart);
			size_t iPosRParen = sLineIn.find(")", iPosStart);
			size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
			size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
            size_t iPosOn = sLineIn.find("ON", iPosStart);
			//size_t iPosGroupBy = sLineIn.find("GROUP BY", iPosStart);
			//size_t iPosOrderBy = sLineIn.find("ORDER BY", iPosStart);
			
			if (iPosLParen != string::npos) { // recursion exists if true
				if ((iPosJoin == string::npos && iPosWhere == string::npos) ||
					(iPosJoin != string::npos && iPosLParen < iPosJoin) ||
					(iPosWhere != string::npos && iPosLParen < iPosWhere))
				{
					string subQuery = sLineIn.substr(iPosLParen+1);
					cout << "subQuery " << subQuery << endl;
					nestedLevel++;
					findSelectNew(subQuery, insertSelectTempName);
		            nestedLevel--;
		            returnedFromRecursion = true;
		            cout << "returned from recursion" << endl;
		            // ok, now start using origQuery

		            // find temporary table name
		            iPosStart = origQuery.find(")", returningNestedLevel) + 1;
					iPosRParen = origQuery.find(")", iPosStart);
					sLineIn = origQuery;
					if (iPosRParen != string::npos) {
			            string tempTableName = sLineIn.substr(iPosStart,
			                 	                     iPosRParen - iPosStart);
						selectQ.setTempTable(tempTableName);
					} else {
						string tempTableName = origQuery.substr(iPosStart,
														iPosSemiColon - iPosStart);
						cout << "tableName " << tempTableName << endl;
						selectQ.setTempTable(tempTableName);
					}
					
					selectQ.printAll();
					e.executeSelect(selectQ.getFromTable(),
									createVector(selectQ.getSelectCols()),
									selectQ.getTempTable(),
									selectQ.getWhereFilter(),
 									selectQ.getJoinTable(),
        		              		selectQ.getJoinFilter());
					
					selectQ.setSelectCols(colNames);
					selectQ.setFromTable(selectQ.getTempTable());
					selectQ.setTempTable("");
				}
				
			}
			
			string tableName = "";
			string joinTable = "";
			string joinFilter = "";
			string whereFilter = "";
			// don't want to check for join too early
			if (iPosJoin != string::npos && iPosJoin < iPosLParen) {
				//cout << "checking join clause" << endl;
				tableName = sLineIn.substr(iPosStart,
											iPosJoin - iPosStart);
	            
				iPosJoin += 4;
				//iPosStart = iPosJoin;
				if (iPosOn != string::npos && iPosOn < iPosRParen) {
					joinTable = sLineIn.substr(iPosJoin, iPosOn - iPosJoin);
				} else if (iPosWhere != string::npos && iPosWhere < iPosRParen) {
					joinTable = sLineIn.substr(iPosJoin, iPosWhere - iPosJoin);
				} else if (iPosRParen != string::npos && iPosJoin < iPosRParen) {
					joinTable = sLineIn.substr(iPosJoin, iPosRParen - iPosJoin);
				} else {
					joinTable = sLineIn.substr(iPosJoin, iPosSemiColon - iPosJoin);
				}
				
				joinTable = Utilities::cleanSpaces(joinTable);
				selectQ.setJoinTable(joinTable);
			} else {
				selectQ.setJoinTable("");
			}
			
			cout << "joinFilter " << joinFilter << endl;
			// don't want to check for on too early
			if (iPosOn != string::npos && iPosOn < iPosLParen) {
				//cout << "checking join filter" << endl;
				iPosOn += 2;
				if (iPosWhere != string::npos && iPosWhere < iPosRParen) {
					joinFilter = sLineIn.substr(iPosOn, iPosWhere - iPosOn);
				} else if (iPosRParen != string::npos && iPosOn < iPosRParen) {
					joinFilter = sLineIn.substr(iPosOn, iPosRParen - iPosOn);
				} else {
					joinFilter = sLineIn.substr(iPosOn, iPosSemiColon - iPosOn);
				}
				
				joinFilter = Utilities::cleanSpaces(joinFilter);
				selectQ.setJoinFilter(joinFilter);
			} else {
				selectQ.setJoinFilter("");
			}
			cout << "joinFilter " << joinFilter << endl;
			
			// don't want to check for where too early
			if (iPosWhere != string::npos && iPosWhere < iPosLParen) {
				//cout << "checking where clause" << endl;
				if (tableName.length() == 0) {
					tableName = sLineIn.substr(iPosStart,
											iPosWhere - iPosStart);
				}
				
				iPosWhere += 5;
				//iPosStart = iPosWhere;
				if (iPosRParen != string::npos && iPosWhere < iPosRParen) {
					whereFilter = sLineIn.substr(iPosWhere, iPosRParen - iPosWhere);
				} else {
					whereFilter = sLineIn.substr(iPosWhere,
												iPosSemiColon - iPosWhere);
				}
				
				whereFilter = Utilities::cleanSpaces(whereFilter);
				selectQ.setWhereFilter(whereFilter);
			} else{
				selectQ.setWhereFilter("");
			}
			cout << "whereFilter " << whereFilter << endl;
			
			// group by
			
			// order by
			
			//cout << "tableName " << tableName << endl;
			if (!tableName.empty()) {
				selectQ.setFromTable(tableName);
			}
			
			// is this the end of the nested queries?
			if (iPosRParen != string::npos) { // and if !returnedfromrecurison
				queryIsNested = true;
				//cout << ") found " << endl;
                //iPosEnd1 = sLineIn.find(")", iPosStart);
				returningNestedLevel = iPosRParen - 1;
				//cout << "returningNestedLevel " << returningNestedLevel << endl;
                if (iPosEnd1 != string::npos)
                {
                    //cout << sLineIn << endl;
                    // was already found if there was a join or where clause
                    if (tableName.length() == 0) {
		                tableName = sLineIn.substr(iPosStart,
		                                          iPosRParen - iPosStart);
		      			selectQ.setFromTable(tableName);
          			}

	                cout << "deepest nested tableName " << tableName << endl;
	                
                    return true;
                }
			} else if (iPosRParen != string::npos && returnedFromRecursion){
				return true;
			}
			
			if (tableName.length() == 0) {
		        tableName = sLineIn.substr(iPosStart,
		                                  iPosSemiColon - iPosStart);
		                                  
			    tableName = Utilities::cleanSpaces(tableName);
			    cout << "tableName was still empty " << tableName << endl;
			    selectQ.setFromTable(tableName);
	        }
	        
	        if (!insertSelectTempName.empty()) {
	        	selectQ.setTempTable(insertSelectTempName);
	        }
			
			selectQ.printAll();
			e.executeSelect(selectQ.getFromTable(),
							createVector(selectQ.getSelectCols()),
							selectQ.getTempTable(),
							selectQ.getWhereFilter(),
 							selectQ.getJoinTable(),
                      		selectQ.getJoinFilter());
		}
	} else {
		return false;
	}
	
	return true;
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
            selectQ.setSelectCols(colNames);

            iPosStart = iPosEnd1 + 4 + 1/*for the space*/;	
            
            size_t iPosSemiColon = sLineIn.find(";", iPosStart);
			size_t nestedSelectPos = sLineIn.find("(", iPosStart);
			size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
			size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
			if (iPosJoin < nestedSelectPos || iPosWhere < nestedSelectPos) {
				// get fromTable
				string tableName = "";
				if (iPosJoin == string::npos) {
					tableName = sLineIn.substr(iPosStart,
													iPosWhere - iPosStart);
				} else {
					tableName = sLineIn.substr(iPosStart,
													iPosJoin - iPosStart);
				}
				cout << "tableName " << tableName << endl;
				selectQ.setFromTable(tableName);
	            return findJoinWhereGroupInSelect(sLineIn, iPosStart,
            								iPosSemiColon, selectQ);
        	}

			// is it nested?
            //size_t nestedSelectPos = sLineIn.find("(", iPosStart);
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
                nestedLevel--;
                cout << "returned from recursion" << endl;
                // ok, now start using origQuery

                // find temporary table name
                iPosStart = origQuery.find(")", returningNestedLevel) + 1;
                //cout << "iPosStart " << iPosStart << endl;
                iPosEnd1 = origQuery.find(")", iPosStart+1);
                //cout << "iPosEnd1 " << iPosEnd1 << endl;

                if (iPosEnd1 == string::npos || (iPosEnd1-iPosStart) > 6) {
                    iPosEnd1 = origQuery.find(";", iPosStart);
                }

                if (iPosEnd1 != string::npos)
                {
                    //cout << "iPosStart " << iPosStart << endl;
                    //cout << "iPosEnd1 " << iPosEnd1 << endl;
                    string tempTableName = origQuery.substr(iPosStart,
                                                        iPosEnd1 - iPosStart);
                    //cout << "tempTableName substr " << tempTableName << endl;

                    tempTableName = Utilities::cleanSpaces(tempTableName);
                    selectQ.setTempTable(tempTableName);
                    returningNestedLevel = iPosEnd1 - 1;
                    cout << "tempTableName " << tempTableName << endl;
                    //cout << "colNames 1" << colNames << endl;
	          			
          			selectQ.printAll();
          			//e.executeSelect();
          			
                    selectQ.setFromTable(selectQ.getTempTable());
                    selectQ.setTempTable("");
                    selectQ.setSelectCols(colNames);
                    cout << "nested level " << nestedLevel << endl;
                    if (nestedLevel == 0) {
                    	selectQ.printAll();
                    }

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
	          		} else {
		             	tableName = sLineIn.substr(iPosStart,
	             									iPosSemiColon - iPosStart);
	          		}
	          		selectQ.setFromTable(tableName);
	                cout << "tableName " << tableName << endl;
	                
	                size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
	                string joinTable = "";
	                string joinFilter = "";
	             	if (iPosJoin != string::npos) {
	             		iPosStart = iPosJoin + 4 + 1/*space after JOIN*/;
		                size_t iPosSpace = sLineIn.find(" ", iPosStart);
		                joinTable = Utilities::cleanSpaces(sLineIn.substr(iPosStart, 
		                							iPosSpace - iPosStart));
		                cout << "joinTable " << joinTable << endl;
		                selectQ.setJoinTable(joinTable);
		                
		                size_t iPosOn = sLineIn.find("ON", iPosStart);
	             		if (iPosOn != string::npos) {
			                size_t iPosEqual = sLineIn.find("=", iPosOn) + 1;
			                size_t iPosTableDotCol = sLineIn.find(".", iPosEqual);
			                size_t iPosJoinEnd = sLineIn.find(" ", iPosTableDotCol);
	             			iPosOn += 2;
	             			joinFilter = Utilities::cleanSpaces(sLineIn.substr(iPosOn,
	             											iPosJoinEnd - iPosOn));
	             			cout << "joinFilter " << joinFilter << endl;
	             			selectQ.setJoinFilter(joinFilter);
	             		}
	             	}
	             	
	                size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
	                //cout << "after poswhere " << iPosWhere << endl;
	                string whereFilter = "";
	             	if (iPosWhere != string::npos) {
	             		size_t iPosWhereFilter = iPosWhere + 5;
		                whereFilter = Utilities::cleanSpaces(sLineIn.substr(iPosWhereFilter,
		                                            iPosSemiColon - iPosWhereFilter));
                        
                        whereFilter = Utilities::cleanSpaces(whereFilter);
		                cout << "where " << whereFilter << endl;
		                selectQ.setWhereFilter(whereFilter);
                    }
                    
                    vector <string> vColNames;
                    vColNames=createVector(colNames);
                    for(size_t j=0; j<vColNames.size();j++){
                        vColNames[j]=Utilities::cleanSpaces(vColNames[j]);
                    }
	                
	                selectQ.printAll();
	                //e.executeSelect(tableName, vColNames, whereFilter,
	                	//			joinTable, joinFilter);
	                return true;
	                //return findJoinWhereGroupInSelect(sLineIn, iPosStart,
            			//								iPosSemiColon, selectQ);//*/
                } else {
                    iPosEnd1 = sLineIn.find(")", iPosStart);
                    returningNestedLevel = iPosEnd1 - 1;
                    if (iPosEnd1 != string::npos)
                    {
                        //cout << sLineIn << endl;
                        string tableName = sLineIn.substr(iPosStart,
                                                          iPosEnd1 - iPosStart);
                        cout << "deepest nested tableName " << tableName << endl;
	          			selectQ.setFromTable(tableName);
	          			
                        return true;
                    }
                }
            }
        }
    } else/* if (nestedLevel > 0) */{
        return false;
    }

    return false;
}

bool Parser::findJoinWhereGroupInSelect(string sLineIn, size_t iPosStart,
										size_t iPosSemiColon, SelectQ selectQ)
{
	size_t iPosJoin = sLineIn.find("JOIN", iPosStart);
    string joinTable = "";
    string joinFilter = "";
 	if (iPosJoin != string::npos) {
 		iPosStart = iPosJoin + 4 + 1/*space after JOIN*/;
        size_t iPosSpace = sLineIn.find(" ", iPosStart);
        joinTable = Utilities::cleanSpaces(sLineIn.substr(iPosStart, 
        							iPosSpace - iPosStart));
        cout << "joinTable " << joinTable << endl;
        selectQ.setJoinTable(joinTable);
        
        size_t iPosOn = sLineIn.find("ON", iPosStart);
 		if (iPosOn != string::npos) {
            size_t iPosEqual = sLineIn.find("=", iPosOn) + 1;
            size_t iPosTableDotCol = sLineIn.find(".", iPosEqual);
            size_t iPosJoinEnd = sLineIn.find(" ", iPosTableDotCol);
 			iPosOn += 2;
 			joinFilter = Utilities::cleanSpaces(sLineIn.substr(iPosOn,
 											iPosJoinEnd - iPosOn));
 			cout << "joinFilter " << joinFilter << endl;
 			selectQ.setJoinFilter(joinFilter);
 		}
 	}
 	
    size_t iPosWhere = sLineIn.find("WHERE", iPosStart);
    //cout << "after poswhere " << iPosWhere << endl;
    string whereFilter = "";
 	if (iPosWhere != string::npos) {
 		size_t iPosWhereFilter = iPosWhere + 5;
 		size_t iPosCloseParen = sLineIn.find(")", iPosWhereFilter);
 		string whereFilter = "";
 		if (iPosCloseParen != string::npos && iPosCloseParen < iPosSemiColon) {
        	whereFilter = sLineIn.substr(iPosWhereFilter,
	                                    iPosCloseParen - iPosWhereFilter);
        } else {
        	whereFilter = sLineIn.substr(iPosWhereFilter,
	                                    iPosSemiColon - iPosWhereFilter);
        }
        whereFilter = Utilities::cleanSpaces(whereFilter);
        cout << "where " << whereFilter << endl;
        selectQ.setWhereFilter(whereFilter);
    }
    
    vector <string> vColNames;
    vColNames=createVector(selectQ.getSelectCols());
    for(size_t j=0; j<vColNames.size();j++){
        vColNames[j]=Utilities::cleanSpaces(vColNames[j]);
    }
    
    selectQ.printAll();
    //e.executeSelect(selectQ.getFromTable(), vColNames,
		//			whereFilter, joinTable, joinFilter);
	
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
	    cout << "insert into found" << endl;
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
            cout << tableName << endl;

            //reposition the iterators to get the row values
            iPosStart = sLineIn.find("(") + 1;
            iPosValues = sLineIn.find(")");

            if (iPosStart != string::npos && iPosValues != string::npos)
            {
                //Get the row attributes from the string
                string sRow = sLineIn.substr(iPosStart,
                                             iPosValues - iPosStart);
                cout << "values " << sRow << endl;
                //values = Utilities::cleanSpaces(values);
                //cout << "values " << values << endl;

                iPosStart = iPosValues;

                //Clean up and add the row to the table
                vector<tuple<int, string> > rowVector = createRowVector(sRow);
                e.addRow(tableName, rowVector);

                return true;
            }
        }//change
            //Execute if values from is found
        else if ((iPosEnd1 = sLineIn.find("SELECT", iPosStart)) != string::npos)
        {
        	string selectSubQ = sLineIn.substr(iPosEnd1,
        									sLineIn.find(";")-iPosEnd1);
            //Get the name of the table from the string
            string tableName = sLineIn.substr(iPosStart, iPosEnd1 - iPosStart);
            tableName = Utilities::cleanSpaces(tableName);
            cout << "insert into tableName " << tableName << endl;
            
            iPosStart = iPosEnd1 + 6;
            iPosEnd1 = sLineIn.find("FROM", iPosStart);
            string colNames = sLineIn.substr(iPosStart,
                                             iPosEnd1 - iPosStart);
            //colNames = Utilities::cleanSpaces(colNames);
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
            
            string tempName = "insInto" + tableName;
            findSelectNew(selectSubQ, tempName);
            //e.insertFrom(tableName, tempName);
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
        string sTableName = sLineIn.substr(iPosStart,
										sLineIn.find(";") - iPosStart);
        sTableName = Utilities::cleanSpaces(sTableName);

        cout << "tableName " << sTableName << endl;

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
        cout << "found show tables" << endl;
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
  e.writetofile();
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
        //cout << "value " << value << endl;
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
        //cout << "sName " << sName << endl;

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
        sName = Utilities::cleanSpaces(sName);
        //push the newly created column into the vector to send back
        vColVectorOut.push_back(make_tuple(sName, sType, length, false));

    }
    return vColVectorOut;
}
