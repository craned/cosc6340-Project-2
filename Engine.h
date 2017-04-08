/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "Table.h"
#include "Utilities.h"
#include "SortTable.h"
using namespace std;

class Engine {
	private:
	    //Declare private variables

	public:

	    //Declare class methods
    Engine() {};
    
    void createTable(string sTableNameIn,
                     vector<tuple<string, string, int, bool> > vColumnNamesIn,
                     /*tuple<int, int, int > vSpecs,*/
                     vector<string> vKeys);
    void displayTable(string sTableNameIn);
    void displayTableSchemas();
    void addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn);
    void getRow(string sTableNameIn,int iIndex);
    bool executeSelect(string tableName, vector < string > colNames,
    				   string tempTable, string whereFilter,
                       string joinTable, string joinFilter);
    void deleteATable(string tableName);
    static int convertCharToInt(char* val);
    void deleteATable(Table table);
    void dropTable(string sTableNameIn);
    Table whereClause(Table tCurrentTable,string whereFilter);
    Table selectClause(Table tNewTable,vector < string > colNames, Table originalTable,string tempTable, bool &returnBool);
    Table joinClause(Table originalTable,Table joinTable,string joinFilter, bool &returnBool);
    //string delSpaces(string str);
    void writetofile();
    void read();
    bool createValidate(string sLineIn,string sTableNameIn);
	void executeQuit();
    static bool sortbyp(const SortTable &lhs,const SortTable &rhs);
    void sortp(string sTableNameIn);
    void insertFromSelect(string sTableNameFrom, string sTableNameTo );
    bool insertselectValidate(Table fromTable, Table toTable);
	};

#endif

