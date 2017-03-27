//
// Created by amirreza shirani on 3/11/17.
//

#ifndef GIT2_TABLE_H
#define GIT2_TABLE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "fstream"
#include "Utilities.h"

using namespace std;

class Table
{
private:
    //sequence num, column name, isPrimary, stype, block size,
    vector<tuple<int, string, bool, string, int > > vColumnNames;

    //vector<vector<tuple<int, string> > > vRows;
    //vector<string> primaryKey;

    //recordSize, totalSize, numOfRecords
    tuple<int, int, int> vSpecs;

    string sTableName;

public:
    //constructors
    Table()
    {};

    //Constructor that takes in a name for the table
    Table(string sTableNameIn)
    {
        sTableName = sTableNameIn;
    }

    //Display function
    void displayTable();

    //Setters
    void setPrimaryKey(string sKeyIn);

    //add a column to the class vector
    void addColumn(tuple<int, string, bool, string, int> s);
    void addSpecs(tuple<int, int, int > d);

    //add a row to the row vector
    void addRow(vector<tuple<int, string> > v);

    //Getters
    string getTableName();

    tuple<int, string, bool, string> getColumnIndex(string sColumnNameIn);

    vector<tuple<int, string> > getRow(int iIndex);

    vector<string> getColumnValues(int iIndex);

};

#endif //GIT2_TABLE_H
