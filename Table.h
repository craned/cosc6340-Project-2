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
using namespace std;

class Table
{
private:
    //sequence num, column name, isPrimary, stype, block size,
    std::vector<std::tuple<int, std::string, bool, std::string, int > > vColumnName;

    //std::vector<std::vector<std::tuple<int, std::string> > > vRows;
    //std::vector<std::string> primaryKey;

    //recordSize, totalSize, numOfRecords
    std::tuple<int, int, int> vSpecs;

    std::string sTableName;

public:
    //constructors
    Table()
    {
    }
    ;

    //Constructor that takes in a name for the table
    Table(std::string sTableNameIn)
    {
        sTableName = sTableNameIn;
    }

    //Display function
    void displayTable();

    //Setters
    void setPrimaryKey(std::string sKeyIn)
    {
        for (int i = 0; i < vColumnName.size(); ++i)
        {
            //Execute if the column name is equal to the parameter name
            if (std::get < 1 > (vColumnName[i]) == sKeyIn)
            {
                //set the boolean value in the column tuple to true, to show it is key
                std::get < 2 > (vColumnName[i]) = true;
                return;
            }
        }

        printf("| Primary Key was not set\n");
    }

//    void removePrimaryKey(std::string sKeyIn)
//    {
//        for (int i = 0; i < vColumnName.size(); ++i)
//        {
//            //find the column that is the key and set the bool to false, remove key
//            if (std::get < 1 > (vColumnName[i]) == sKeyIn)
//            {
//                std::get < 2 > (vColumnName[i]) = false;
//                return;
//            }
//        }
//
//        printf("| Primary Key was not removed\n");
//    }

    //rename the class table to parameter name
//    void rename(std::string sNewName)
//    {
//        sTableName = sNewName;
//    }

    //add a column to the class vector
    void addColumn(std::tuple<int, std::string, bool, std::string, int> s)
    {
        vColumnName.push_back(s);
    }
    void addSpecs(std::tuple<int, int, int > d){
        vSpecs = d;
    }

    //add a row to the row vector
    void addRow( std::vector<std::tuple<int, std::string> > v)
    {
        ofstream outfile;
        string fileName= sTableName +".tbl";
        outfile.open(fileName, ios::binary | ios::out);

        for (int i = 0; i < vColumnName.size()-1; ++i)
        {
            //string sName = get < 0 > (vColumnName[i]);
            //string sType = get < 1 > (vColumnName[i]);
            int bSize= get < 4 > (vColumnName[i]);
            outfile.write((char*)&(std::get<1>(v[i])), bSize);
        }

        outfile.close();

    }

//    //find the row and delete it from the vector
//    void deleteRow(std::vector<std::tuple<int, std::string> > vRowIn)
//    {
//        for (int i = 0; i < vRows.size(); ++i)
//        {
//            if (vRows[i] == vRowIn)
//            {
//                vRows.erase(vRows.begin() + i);
//                return;
//            }
//        }
//        printf("| The row was not removed\n");
//    }

    //Getters
    std::string getTableName()
    {
        return sTableName;
    }

//    std::vector<std::tuple<int, std::string, bool, std::string> > getColumnNames()
//    {
//        return vColumnName;
//    }

//    std::vector<std::vector<std::tuple<int, std::string> > > getRows()
//    {
////        ifstream infile;
////        string fileName= sTableName + ".tbl";
////        infile.open(fileName, ios::binary | ios::in);
////        infile.read(&x, 7);
//
//        return vRows;
//    }

    std::tuple<int, std::string, bool, std::string> getColumnIndex(
            std::string sColumnNameIn);

    std::vector<std::tuple<int, std::string> > getRow(int iIndex);

    std::vector<std::string> getColumnValues(int iIndex);

};

#endif //GIT2_TABLE_H
