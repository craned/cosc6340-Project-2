/*******************************************************************************
 File: Engine.cpp
 Authors: Gustavo Pedroso UIN: 423002834
 Levi Clark      UIN: 520007880
 Terry Chen      UIN: 121007055
 Daniel He       UIN: 620006827
 Department of Computer Science
 Texas A&M University
 Date  : 2014-02-18
 Formatting: * 80 pt width is used for code, for the most part
 * Hungarian naming convention is used for variables
 * Comments are applied for explanations
 * Spacing and brackets are applied for readability
 This file contains the implementation for the engine
 *******************************************************************************/

#include "Engine.h"

/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
 *******************************************************************************/

vector<Table> vTableList;

void Engine::createTable(string sTableNameIn,
                         vector<tuple<string, string, int, bool> > vColumnNamesIn,
                         /*std::tuple<int, int, int> specs,*/
                         vector<string> vKeys)
{

    Table t(sTableNameIn);

    for (size_t i = 0; i < vColumnNamesIn.size()-1; ++i)
    {
        string sName = Utilities::cleanSpaces(get < 0 > (vColumnNamesIn[i]));
        string sType = Utilities::cleanSpaces(get < 1 > (vColumnNamesIn[i]));
        int length = get < 2 > (vColumnNamesIn[i]);
        bool bKey = get < 3 > (vColumnNamesIn[i]);

        t.addColumn(make_tuple(i, sName, bKey, sType, length));
    }
    
    //t.addSpecs(specs);

    for (size_t i = 0; i < vKeys.size(); ++i)
    {
        t.setPrimaryKey(vKeys[i]);
    }

    //push table into the table list

    vTableList.push_back(t);
}

// If you don't understand these comments, run this query:
// ./dbms "select a,b,k from t1 join t2 on t1.k = t2.kb where b=1;"
void Engine::executeSelect(string tableName, string colNames/* ',' delimited */,
							string whereFilter/* '=' delimited */,
	                		string joinTable,
	                		string joinFilter/* '=' delimited */)
{
	// parameters are empty strings if not found. Only tableName and colNames should exist. colNames can be just '*'.
	// put t.addRow() here
}

/****************************************************************************
   Adds a row to the specified table
   ****************************************************************************/
void Engine::addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn)
{
	cout << "addRow" << endl;
	ofstream out;
	out.open("test.tbl", ios::binary | ios::out);
	
	int num = 1453659877;
	string hiStr = "hi";
	
	Engine::writeStringToFile(hiStr, out);
	Engine::writeIntToFile(num, out);
	out.close();
	

	ifstream in;
	char* hi = new char[hiStr.length()+1];
	char* xC = new char[to_string(num).length()+1];
	
	in.open("test.tbl", ios::binary | ios::in);
	in.read(hi, sizeof(char)*(hiStr.length()+1));
	in.read(xC, sizeof(char)*(to_string(num).length()+1));
	cout << "back in " << hi << endl;
	cout << "xC " << xC << endl;

	int x = Engine::convertCharToInt(xC);
	cout << "x num " << x << endl;

    for (size_t i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            //vTableList[i].addRow(vRowIn);
            return;
        }
    }
}
/*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
void Engine::displayTable(string sTableNameIn)
{
    for (size_t i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            return;
        }
    }
    printf("| The table was not found\n");
}

/*****************************************************************************
   Print out all table schemas
   ****************************************************************************/
void Engine::displayTableSchemas()
{
	//cout << "Grab data from catalog" << endl;
	for (size_t i = 0; i < vTableList.size(); ++i)
    {
        //if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            //return;
        }
    }
}

void Engine::writeStringToFile(string val, ofstream& out)
{
	char* valOut = new char[val.length()+1];
	for (size_t i = 0; i < val.length(); i++) {
		valOut[i] = val[i];
		//cout << "valOut[i] " << valOut[i] << endl;
	}
	valOut[val.length()] = '\0';
	
	out.write(valOut, sizeof(char)*(val.length()+1));
}

void Engine::writeIntToFile(int num, ofstream& out)
{
	string numStr = to_string(num);
	char* numC = new char[numStr.length()+1];
	for (size_t i = 0; i < numStr.length(); i++) {
		numC[i] = numStr[i];
		//cout << "numC[i] " << numC[i] << endl;
	}
	numC[numStr.length()] = '\0';
	
	out.write(numC, sizeof(char)*(numStr.length()+1));
}

int Engine::convertCharToInt(char* val)
{
	string xStr;
	for (size_t i = 0; i < strlen(val); i++) {
		xStr[i] = val[i];
		//cout << "xStr[i] " << xStr[i] << endl;
	}
	return stoi(xStr);
}

