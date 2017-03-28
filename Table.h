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
    std::vector<std::string> primaryKey;
    int tRecordSize;
    int tTotalSize;
    int tNumOfRecords;
    string sTableName;

public:
    int getTRecordSize() const;

    void setTRecordSize(int tRecordSize);

    int getTTotalSize() const;

    void setTTotalSize(int tTotalSize);

    int getTNumOfRecords() const;

    void setTNumOfRecords(int tNumOfRecords);
    //constructors
    Table()
    {
    }
    ;
    std::vector<std::tuple<int, std::string, bool, std::string, int> > getColumnNames()
    {
        return vColumnName;
    }

    void printOutTheWholeTable();

    //Constructor that takes in a name for the table
    Table(std::string sTableNameIn)
    {
        sTableName = sTableNameIn;
    }

    //Display function
    void displayTable();

    //Setters
    void setPrimaryKey(std::string sKeyIn);



    //add a column to the class vector
    void addColumn(std::tuple<int, std::string, bool, std::string, int> s)
    {
        vColumnName.push_back(s);
    }

    string delSpaces(string &str)
    {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }


    //add a row to the row vector
    void addRow( std::vector<std::tuple<int, std::string> > v);

    //get a row by using index
    vector < std::tuple<int, std::string> > getRow(int iIndex);



    int getRecordSize()
    {
        int recordSize=0;
        for (int i = 0; i < vColumnName.size(); ++i) {
            //cout<<"get<4>(vColumnName[i]: "<<get<4>(vColumnName[i])<<endl;
            recordSize=recordSize+get<4>(vColumnName[i]);
        }
        //cout<<"record size is: "<<recordSize<< endl;
        return recordSize;
    }



    //Getters
    std::string getTableName()
    {
        return sTableName;
    }



    void writeStringToFile(string val,int blockSize, ofstream& out);
    void writeIntToFile(int num, ofstream& out);

    std::tuple<int, std::string, bool, std::string> getColumnIndex(
            std::string sColumnNameIn);

    //std::vector<std::tuple<int, std::string> > getRow(int iIndex);

    std::vector<std::string> getColumnValues(int iIndex);

    void deleteATable(string tableName);
};

#endif //GIT2_TABLE_H
