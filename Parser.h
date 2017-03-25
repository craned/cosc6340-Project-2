/*******************************************************************************
 File: Parser.h
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
 This file contains the header for the parser
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

using namespace std;

class Parser
{
private:
    //Declare private variables
    vector<string> vValuesRead;
    Engine e;

public:
    //Tree data structure
//    struct treeNode
//    {
//        string data;
//        treeNode *leftChild;
//        treeNode *rightChild;
//    };

    //Tree functions
//    void traversal(treeNode *start); //In Order Traversal
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
    vector<tuple<string, string, int, bool> > createColVector(string sLineIn);
    vector<string> createVector(string sLineIn);
    vector<tuple<int, string> > createRowVector(string sLineIn);
    static string cleanSpaces(string sLineIn);
    string removeSpaces(string sLineIn);
    bool checkParenthesis(string sLineIn);
    bool semicolonExists(string sLineIn);
//  vector<string> makeTokens(string sLineIn); //tokenizes some shit
//    treeNode * createTree(string sLineIn);
    void projection(string sRestOfLine, string sTableNameOut);
//    void rename(string sRestOfLine, string sTableNameOut);
//    void op(string sNewTableName, string sRestOfLine);
    void select(string sNewTableName, string sRestOfLine);
//  void evalCondition(vector<string> vTokens, string relationName);
//  void removeBlankTokens(vector<string> & vTokens);

//  Engine getEngine()
//  {
//    return e;
//  }
};

#endif