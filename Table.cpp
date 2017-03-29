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
fstream outputFile;

/*******************************************************************************
 Display the table
 *******************************************************************************/
void Table::displayTable()
{
  // Print the lines of the table for a pretty output
  cout << "\n ";

  for (size_t i = 0; i < vColumnNames.size(); ++i)
  {
    cout << "-----------------------";
  }
  cout << "\n";

  cout << " | " << sTableName << "\n ";

  for (size_t i = 0; i < vColumnNames.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

  // Determine how far to space the column bars
  for (size_t i = 0; i < vColumnNames.size(); ++i)
  {
    //get the column values for printing
    string sColName = get < 1 > (vColumnNames[i]);
    bool bPrimaryKey = get < 2 > (vColumnNames[i]);

    //see if it is a primary key, for formatting
    if (bPrimaryKey)
    {
      cout << " | " << setw(COLUMN_WIDTH) << left
                << "*" + sColName + "*";
    }
    else
    {
      cout << " | " << setw(COLUMN_WIDTH) << left << sColName;
    }

  }
  cout << "\n ";

  // Print the row dividers for the number of columns
  for (size_t i = 0; i < vColumnNames.size(); ++i)
  {
    cout << "+----------------------";
  }
  cout << "\n";

//  for (size_t i = 0; i < vRows.size(); ++i)
//  {
//
//    for (size_t a = 0; a < vColumnNames.size(); ++a)
//    {
//      for (vector<tuple<int, string> >::iterator current =
//              vRows[i].begin(); current != vRows[i].end(); ++current)
//      {
//        if (get < 0 > (*current) == get < 0 > (vColumnNames[a]))
//        {
//          string sCurrent = get < 1 > (*current);
//          if (sCurrent.size() > COLUMN_WIDTH)
//          {
//            sCurrent.resize(COLUMN_WIDTH);
//          }
//          cout << " | " << setw(COLUMN_WIDTH) << left
//                    << sCurrent;
//
//          break;
//        }
//      }
//    }
//
//    cout << "\n ";
//    for (size_t y = 0; y < vColumnNames.size(); ++y)
//    {
//      cout << "+----------------------";
//    }
//    cout << "\n";
//  }
//  cout << "\n";
}

/*******************************************************************************
 This function returns the index of the column or -1 if the column is not found
 and the type of the column
 *******************************************************************************/

tuple<int, string, bool, string> Table::getColumnIndex(
        string sColumnNameIn)
{
  for (size_t i = 0; i < vColumnNames.size(); ++i)
  {
    //Execute if the column was found
    if (get < 1 > (vColumnNames[i]) == sColumnNameIn)
    {
      int iColumnIndex = get < 0 > (vColumnNames[i]);
      bool bColumnKey = get < 2 > (vColumnNames[i]);
      string sColumnType = get < 3 > (vColumnNames[i]);

      return make_tuple(iColumnIndex, sColumnType, bColumnKey, sColumnType);
    }
  }

  printf("| We didnt find it\n");
  //The column was not found
  return make_tuple(-1, "n/a", false, "n/a");
}

void Table::printOutTheWholeTable(){
    // Print the lines of the table for a pretty output
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

    // Determine how far to space the column bars
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

    // Print the row dividers for the number of columns
    for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        std::cout << "+----------------------";
    }
    std::cout << "\n";

    for(int i=0; i<tNumOfRecords; i++) {
        for (size_t a = 0; a < vColumnNames.size(); ++a){
            std::vector < std::tuple<int, std::string> > row;
            row =getRow(i);
            for(size_t z=0;z<row.size();z++) {
                if (get<0>(row[z]) == get<0>(vColumnNames[a])) {
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
        for (size_t y = 0; y < vColumnNames.size(); ++y)
        {
            std::cout << "+----------------------";
        }
        std::cout << "\n";
    }
    std::cout<<"\n";
}

void Table::addRow( std::vector<std::tuple<int, std::string> > v) {

    cout << "adding Rows" << endl;
    cout << "in table " << sTableName << endl;
    string tableName = sTableName + ".tbl";
    ofstream out;
    out.open(tableName, ios::binary | ios::out | ios::app);
    for (size_t i = 0; i < vColumnNames.size(); ++i) {
        if(get<3>(vColumnNames[i])=="string") {
            Utilities::cleanSpaces(get<1>(v[i]));
            //cout<<"get<1>(v[i]): "<<get<1>(v[i])<<endl;
            //cout<<"size of get<1>(v[i]): "<<sizeof(get<1>(v[i]))<<endl;
            writeStringToFile(get<1>(v[i]), get<4>(vColumnNames[i]), out);
            //cout << "v" << i << ":" << get<1>(v[i]) << endl;

        }
        else if(get<3>(vColumnNames[i])=="int"){
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
    for (size_t i = 0; i < vColumnNames.size(); ++i) {
        if(get<3>(vColumnNames[i])=="string") {
            int blockSize = get<4>(vColumnNames[i]);
            //cout<<"string block size "<<blockSize<<endl;
            char *c1 = new char[blockSize];
            in.read(c1, sizeof(char) * blockSize);
            //cout << "s1: " << c1 << endl;
            vReturn.push_back(
                    std::make_tuple(i, c1));
        } else if(get<3>(vColumnNames[i])=="int") {
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

    //Setters
    void Table::setPrimaryKey(string sKeyIn)
    {
    	cout << "key " << sKeyIn << endl;
        for (size_t i = 0; i < vColumnNames.size(); ++i)
        {
        	cout << "column name " << get < 1 > (vColumnNames[i]) << endl;
            //Execute if the column name is equal to the parameter name
            if (get < 1 > (vColumnNames[i]) == sKeyIn)
            {
                //set the boolean value in the column tuple to true, to show it is key
                get < 2 > (vColumnNames[i]) = true;
                primaryKey.push_back(sKeyIn);
                return;
            }
        }
		
        printf("ERROR: Primary Key was not set\n");
    }

    //add a column to the class vector
    void Table::addColumn(tuple<int, string, bool, string, int> s)
    {
        vColumnNames.push_back(s);
    }
    /*void Table::addSpecs(tuple<int, int, int > d){
        vSpecs = d;
    }*/

    //Getters
    string Table::getTableName()
    {
        return sTableName;
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
