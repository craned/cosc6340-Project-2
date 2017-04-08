/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/

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
#include <cstdio>

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
        return vColumnNames;
    }
	    void calculateRecordSize()
    {
        int count=0;
        for (size_t i = 0; i < vColumnNames.size(); ++i){
            if ((std::get < 3 > (vColumnNames[i])).compare("INT"))
                count=count+4;
            else
                count=count+std::get < 4 > (vColumnNames[i]);
        }
        tRecordSize=count;
    }
	void calculateTotalRecordSize()
    {
        tTotalSize=tRecordSize*tNumOfRecords;
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
	std::vector<std::string> getPrimaryKey()
	{
	return primaryKey;
	}
	


    //add a column to the class vector
    void addColumn(std::tuple<int, std::string, bool, std::string, int> s);
    void addSpecs(tuple<int, int, int > d);

    /*string delSpaces(string &str)
    {
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }*/


    //add a row to the row vector
    void addRow( std::vector<std::tuple<int, std::string> > v);

    //get a row by using index
    vector < std::tuple<int, std::string> > getRow(int iIndex);



    int getRecordSize()
    {
        int recordSize=0;
        for (size_t i = 0; i < vColumnNames.size(); ++i) {
            //cout<<"get<4>(vColumnName[i]: "<<get<4>(vColumnName[i])<<endl;
            recordSize=recordSize+get<4>(vColumnNames[i]);
        }
        //cout<<"record size is: "<<recordSize<< endl;
        return recordSize;
    }



    //Getters
    std::string getTableName();



    void writeStringToFile(string val,int blockSize, ofstream& out);
    void writeIntToFile(int num, ofstream& out);

    std::tuple<int, std::string, bool, std::string> getColumnIndex(
            std::string sColumnNameIn);

    //std::vector<std::tuple<int, std::string> > getRow(int iIndex);

    std::vector<std::string> getColumnValues(int iIndex);

    void deleteATable(string tableName);

    //rename the class table to parameter name
    void rename(string sNewName)
    {
        sTableName = sNewName;
    }
    
    void distinct(){
    
    const int COLUMN_WIDTH = 20;
std::cout << "\n ";

    for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        std::cout << "-----------------------";
    }
    std::cout << "\n";

    std::cout << " | " << sTableName << "\n ";

    for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        std::cout << "+----------------------";
    }
    std::cout << "\n";

    for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        //get the column values for printing
        std::string sColName = std::get < 1 > (vColumnNames[i]);
        bool bPrimaryKey = std::get < 2 > (vColumnNames[i]);

        //see if it is a primary key, for formatting
        if (bPrimaryKey)
        {
            std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
                      << "*" + sColName + "*";
        }
        else
        {
            std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left << sColName;
        }

    }
        std::cout << "\n ";
       for (size_t y = 0; y < vColumnNames.size(); ++y)
        {
            std::cout << "+----------------------";
        }
        std::cout << "\n";
    
     for(int i=0; i<tNumOfRecords; i++) {
        
            std::vector < std::tuple<int, std::string> > row;
            row =getRow(i);
            int rowcounter=0;
            for(int j=i+1; j<tNumOfRecords; j++) {
            std::vector < std::tuple<int, std::string> > row2;
            row2 =getRow(j);
            int counter=0;
            for(size_t z=0;z<row.size();z++) {
                if (get<1>(row[z]) == get<1>(row2[z])) {
                   /* string sCurrent = get<1>(row[z]);
                    //cout << "sCurrent " << sCurrent << endl;
                    if (sCurrent.size() > COLUMN_WIDTH) {
                        sCurrent.resize(COLUMN_WIDTH);
                    }*/
                    counter=counter+1;
                    /*std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
                              << sCurrent;

                    break;*/

                }

            }
           // cout<<counter<<" "<<row.size();
            if(counter!=row.size()){
 
            rowcounter=rowcounter+1;
        }
        if(rowcounter==tNumOfRecords-i-1){
        
        
                   for(size_t z=0;z<row.size();z++) {
            string sCurrent = get<1>(row[z]);
            //cout << "sCurrent " << sCurrent << endl;
            if (sCurrent.size() > COLUMN_WIDTH) {
                        sCurrent.resize(COLUMN_WIDTH);
                    }
            std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
                              << sCurrent;
                              }
            }

 }
        
        std::cout << "\n ";
       for (size_t y = 0; y < vColumnNames.size(); ++y)
        {
            std::cout << "+----------------------";
        }
        std::cout << "\n";
    }
    

}
    
};

#endif //GIT2_TABLE_H
