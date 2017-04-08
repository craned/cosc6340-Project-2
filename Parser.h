/*******************************************************************************
 File: Table.cpp

 Author:Amirreza Shirani
 *******************************************************************************/

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <stack>
#include <fstream>
#include "Table.h"
#include "Engine.h"
#include "SelectQ.h"
#include "Utilities.h"

using namespace std;

class Parser
{
private:
    //Declare private variables
    vector<string> vValuesRead;
  Engine e;
  SelectQ selectQ;
  stack<int> parens;

public:
    //Declare class methods
    Parser() {};
	bool queryIsNested = false;		
 	bool returnedFromRecursion = false;		
 	bool foundDeepestQuery = false;
	bool joinSelectRecursion = false;

  bool readFromFile(string sFileName);
  bool writeToFile(string sFileName);
  int parse(string sLineIn);
  void validate();

  //Grammar functions
  bool findCreateTable(string sLineIn);
  bool findSelect(string sLineIn);
  bool findInsertInto(string sLineIn);
  bool findDropTable(string sLineIn);
  bool findShowTable(string sLineIn);
  bool findShowTables(string sLineIn);
  bool findWrite(string sLineIn);
  bool findOpen(string sLineIn);
  bool findClose(string sLineIn);
  bool findQuit(string sLineIn);
  string getAfterArrow(string sLineIn);
    bool findSelectNew(string sLineIn, string insertSelectTempName);
    bool findSelectParen(string sLineIn, string insertSelectTable);
    size_t getMatchingClosingParen(string sLineIn, size_t start);
    bool findJoinWhereGroupInSelect(string sLineIn, size_t iPosStart,											size_t iPosSemiColon, SelectQ selectQ);
    //helper functions
    vector<tuple<string, string, int, bool> > createColVector(string sLineIn);
    vector<string> createVector(string sLineIn);
    vector<tuple<int, string> > createRowVector(string sLineIn);
    //static string cleanSpaces(string sLineIn);
    string removeSpaces(string sLineIn);
    bool checkParenthesis(string sLineIn);
    bool semicolonExists(string sLineIn);
    void projection(string sRestOfLine, string sTableNameOut);
    void select(string sNewTableName, string sRestOfLine);
    void read();

};

#endif
