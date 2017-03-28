/*******************************************************************************
 File: Table.cpp

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

 This file contains the table implementation file
 *******************************************************************************/

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "Table.h"

const int COLUMN_WIDTH = 20;
std::fstream outputFile;

/*******************************************************************************
 Display the table
 *******************************************************************************/
void Table::displayTable()
{
  // Print the lines of the table for a pretty output
  std::cout << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "-----------------------";
  }
  std::cout << "\n";

  std::cout << " | " << sTableName << "\n ";

  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "+----------------------";
  }
  std::cout << "\n";

  // Determine how far to space the column bars
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //get the column values for printing
    std::string sColName = std::get < 1 > (vColumnName[i]);
    bool bPrimaryKey = std::get < 2 > (vColumnName[i]);

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

  // Print the row dividers for the number of columns
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    std::cout << "+----------------------";
  }
  std::cout << "\n";

//  for (int i = 0; i < vRows.size(); ++i)
//  {
//
//    for (int a = 0; a < vColumnName.size(); ++a)
//    {
//      for (std::vector<std::tuple<int, std::string> >::iterator current =
//              vRows[i].begin(); current != vRows[i].end(); ++current)
//      {
//        if (std::get < 0 > (*current) == std::get < 0 > (vColumnName[a]))
//        {
//          std::string sCurrent = std::get < 1 > (*current);
//          if (sCurrent.size() > COLUMN_WIDTH)
//          {
//            sCurrent.resize(COLUMN_WIDTH);
//          }
//          std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
//                    << sCurrent;
//
//          break;
//        }
//      }
//    }
//
//    std::cout << "\n ";
//    for (int y = 0; y < vColumnName.size(); ++y)
//    {
//      std::cout << "+----------------------";
//    }
//    std::cout << "\n";
//  }
//  std::cout<<"\n";
}

/*******************************************************************************
 This function returns the index of the column or -1 if the column is not found
 and the type of the column
 *******************************************************************************/
std::tuple<int, std::string, bool, std::string> Table::getColumnIndex(
        std::string sColumnNameIn)
{
  for (int i = 0; i < vColumnName.size(); ++i)
  {
    //Execute if the column was found
    if (std::get < 1 > (vColumnName[i]) == sColumnNameIn)
    {
      int iColumnIndex = std::get < 0 > (vColumnName[i]);
      bool bColumnKey = std::get < 2 > (vColumnName[i]);
      std::string sColumnType = std::get < 3 > (vColumnName[i]);

      return std::make_tuple(iColumnIndex, sColumnType, bColumnKey, sColumnType);
    }
  }

  printf("| We didnt find it\n");
  //The column was not found
  return std::make_tuple(-1, "n/a", false, "n/a");
}



void Table::printOutTheWholeTable(){
    // Print the lines of the table for a pretty output
    std::cout << "\n ";

    for (int i = 0; i < vColumnName.size(); ++i)
    {
        std::cout << "-----------------------";
    }
    std::cout << "\n";

    std::cout << " | " << sTableName << "\n ";

    for (int i = 0; i < vColumnName.size(); ++i)
    {
        std::cout << "+----------------------";
    }
    std::cout << "\n";

    // Determine how far to space the column bars
    for (int i = 0; i < vColumnName.size(); ++i)
    {
        //get the column values for printing
        std::string sColName = std::get < 1 > (vColumnName[i]);
        bool bPrimaryKey = std::get < 2 > (vColumnName[i]);

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

    // Print the row dividers for the number of columns
    for (int i = 0; i < vColumnName.size(); ++i)
    {
        std::cout << "+----------------------";
    }
    std::cout << "\n";

    for(int i=0; i<tNumOfRecords; i++) {
        for (int a = 0; a < vColumnName.size(); ++a){
            std::vector < std::tuple<int, std::string> > row;
            row =getRow(i);
            for(int z=0;z<row.size();z++) {
                if (get<0>(row[z]) == get<0>(vColumnName[a])) {
                    string sCurrent = get<1>(row[z]);
                    //cout << "sCurrent " << sCurrent << endl;
                    if (sCurrent.size() > COLUMN_WIDTH) {
                        sCurrent.resize(COLUMN_WIDTH);
                    }
                    std::cout << " | " << std::setw(COLUMN_WIDTH) << std::left
                              << sCurrent;

                    break;

                }

            }
        }
        std::cout << "\n ";
        for (int y = 0; y < vColumnName.size(); ++y)
        {
            std::cout << "+----------------------";
        }
        std::cout << "\n";
    }
    std::cout<<"\n";
}
void Table::setPrimaryKey(std::string sKeyIn)
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

void Table::addRow( std::vector<std::tuple<int, std::string> > v) {

    cout << "adding Rows" << endl;
    cout << "in table " << sTableName << endl;
    string tableName = sTableName + ".tbl";
    ofstream out;
    out.open(tableName, ios::binary | ios::out | ios::app);
    for (int i = 0; i < vColumnName.size(); ++i) {
        if(get<3>(vColumnName[i])=="string") {
            delSpaces(get<1>(v[i]));
            //cout<<"get<1>(v[i]): "<<get<1>(v[i])<<endl;
            //cout<<"size of get<1>(v[i]): "<<sizeof(get<1>(v[i]))<<endl;
            writeStringToFile(get<1>(v[i]), get<4>(vColumnName[i]), out);
            //cout << "v" << i << ":" << get<1>(v[i]) << endl;

        }
        else if(get<3>(vColumnName[i])=="int"){
            std::string::size_type sz;
            //cout<<"sz: "<<sz<<endl;
            int value= stol(get<1>(v[i]),&sz);
            //cout<<"size of this int: "<<sizeof(value)<<endl;
            writeIntToFile(value,out);

        }
        else cout<<"type error! "<<endl;
    }
    setTNumOfRecords(getTNumOfRecords()+1);
    out.close();
}


//get a row by using index
vector < std::tuple<int, std::string> > Table::getRow(int iIndex) {
    std::vector < std::tuple<int, std::string> > vReturn;
    ifstream in;
    int recordSize=getRecordSize();
//        if(iIndex>get<2>vSpecs){
//            //error
//        }else
    string tableName = sTableName + ".tbl";
    in.open(tableName, ios::binary | ios::in);
    in.seekg(recordSize*iIndex, ios::beg);
    for (int i = 0; i < vColumnName.size(); ++i) {
        if(get<3>(vColumnName[i])=="string") {
            int blockSize = get<4>(vColumnName[i]);
            //cout<<"string block size "<<blockSize<<endl;
            char *c1 = new char[blockSize];
            in.read(c1, sizeof(char) * blockSize);
            //cout << "s1: " << c1 << endl;
            vReturn.push_back(
                    std::make_tuple(i, c1));
        } else if(get<3>(vColumnName[i])=="int") {
            int c2;
            char* pmemory = ( char* ) &c2;
            //char *c2 = new char[sizeof(int)];
            in.read(pmemory, sizeof(int));
            //cout << "i1: " << c2 << endl;
            vReturn.push_back(
                    std::make_tuple(i, to_string(c2)));
        }

    }
    in.close();

    return vReturn;
}

void Table::deleteATable(string tableName){
    string name=tableName+".tbl";
    //setTNumOfRecords(0);
    const char* tName=name.c_str();
    if( remove( tName ) != 0 )
        perror( "Error deleting file" );
    else
        puts( "File successfully deleted" );
}

void Table::writeStringToFile(string val,int blockSize, ofstream& out)
{
    char* valOut = new char[blockSize];
    for (int i = 0; i < blockSize; i++) {
        valOut[i] = val[i];
    }
    //valOut[val.length()] = '\0';

    out.write(valOut, sizeof(char)*(blockSize));
    //cout<<"write string.val.length(): "<<valO<<endl ;
}

void Table::writeIntToFile(int num, ofstream& out) {

    out.write((char*) &num, sizeof(int));


}

int Table::getTRecordSize() const {
    return tRecordSize;
}

void Table::setTRecordSize(int tRecordSize) {
    Table::tRecordSize = tRecordSize;
}

int Table::getTTotalSize() const {
    return tTotalSize;
}

void Table::setTTotalSize(int tTotalSize) {
    Table::tTotalSize = tTotalSize;
}

int Table::getTNumOfRecords() const {
    return tNumOfRecords;
}

void Table::setTNumOfRecords(int tNumOfRecords) {
    Table::tNumOfRecords = tNumOfRecords;
}
