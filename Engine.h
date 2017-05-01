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
#include <stdlib.h>
#include <ctype.h>
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
                       string joinTable, string joinFilter,
                       string groupBy, string orderBy,
                       string sumCol);
    void deleteATable(string tableName);
    static int convertCharToInt(char* val);
    void deleteATable(Table table);
    void dropTable(string sTableNameIn);
    Table whereClause(string tCurrentTableStr,string whereFilter);
    Table selectClause(string tNewTableStr,vector < string > colNames, string originalTableStr, bool &returnBool);
    Table joinClause(string originalTableStr,string joinTableStr,string joinFilter, bool &returnBool);
    Table sum(Table tableName, string columnName, int foundColIndex,
    							string groupByCol, int foundGroupByIndex);
    //string delSpaces(string str);
    void writetofile();
    void read();
    bool createValidate(string sLineIn,string sTableNameIn);
	void executeQuit();
    static bool sortbyp(const SortTable &lhs,const SortTable &rhs);
    string sortp(string sTableNameIn,int key);
    void insertFromSelect(string sTableNameFrom, string sTableNameTo );
    bool insertselectValidate(Table fromTable, Table toTable);
    bool is_number(const std::string& s);
     static bool sortbyi(const SortTable &lhs,const SortTable &rhs);
    Table groupByClause(Table currentTable, string groupByCol, string sumCol);
    Table orderByClause(Table currentTable, string orderByCol);
    string realColVal(string col);
    string realTableVal(string col);


	};

#endif

