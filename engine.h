/*******************************************************************************
 File: Engine.h
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
 This file contains the header for the engine
 *******************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "table.h"
using namespace std;

class Engine {
private:
    //Declare private variables
    //std::vector<Table> vTableList;

public:

    //Declare class methods
    Engine() {

    };

    void createTable(std::string sTableNameIn,
                     std::vector<std::tuple<std::string, std::string, bool, int> > vColumnNamesIn,
                     std::tuple<int, int, int > vSpecs,
                     std::vector<std::string> vKeys);
    void displayTable(string sTableNameIn);
    void addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn);



};



#endif