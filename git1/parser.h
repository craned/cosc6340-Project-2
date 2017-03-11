//
// Created by amirreza shirani on 3/11/17.
//


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
#include "Table.h"
//#include "../../Downloads/DBMS-master/Engine.h"
using namespace std;

class Parser
{
private:
    //Declare private variables
    vector<string> vValuesRead;
//  Engine e;

public:
    //Tree data structure
    struct treeNode
    {
        string data;
        treeNode *leftChild;
        treeNode *rightChild;
    };

    //Tree functions
    void traversal(treeNode *start); //In Order Traversal
    //Declare class methods
    Parser() {};

    bool readFromFile(string sFileName);
    bool writeToFile(string sFileName);
    int parse(string sLineIn);
    void validate();

    //Grammar functions
    bool findCreateTable(string sLineIn);
    bool findSelect(string sLineIn);
    bool findInsertInto(string sLineIn);
    bool findShowTable(string sLineIn);
    bool findShowTables(string sLineIn);
    bool findWrite(string sLineIn);
    bool findOpen(string sLineIn);
    bool findClose(string sLineIn);
    bool findQuit(string sLineIn);
    string getAfterArrow(string sLineIn);

    //helper functions
//  vector<tuple<string, string, bool> > createColVector(string sLineIn);
//  vector<string> createVector(string sLineIn);
//  vector<tuple<int, string> > createRowVector(string sLineIn);
    string cleanSpaces(string sLineIn);
    string removeSpaces(string sLineIn);
    bool checkParenthesis(string sLineIn);
//  vector<string> makeTokens(string sLineIn); //tokenizes some shit
    treeNode * createTree(string sLineIn);
    void projection(string sRestOfLine, string sTableNameOut);
    void rename(string sRestOfLine, string sTableNameOut);
    void op(string sNewTableName, string sRestOfLine);
    void select(string sNewTableName, string sRestOfLine);
//  void evalCondition(vector<string> vTokens, string relationName);
//  void removeBlankTokens(vector<string> & vTokens);

//  Engine getEngine()
//  {
//    return e;
//  }
};


#endif //GIT2_PARSER_H
