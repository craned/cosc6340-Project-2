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
//    for (int y = 0; y < vColumnNames.size(); ++y)
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


/*******************************************************************************
 This function takes the index of a column and returns the values of the column
 *******************************************************************************/
vector<tuple<int, string> > Table::getRow(int iIndex)
{
  ifstream infile;
  streampos pos;
  string fileName = sTableName + ".tbl";
  infile.open(fileName, ios::binary | ios::in);


  vector < tuple<int, string> > vReturn;
  if(iIndex*get<0>(vSpecs)< get<1>(vSpecs) and iIndex<get<2>(vSpecs)){

    infile.seekg(iIndex*get<0>(vSpecs), ios::beg);
    for (size_t i = 0; i< vColumnNames.size()-1; ++i){
      string sName = get < 1 > (vColumnNames[i]);
      int bSize= get < 4 > (vColumnNames[i]);
      infile.read((char *)&sName, bSize);
      vReturn.push_back(make_tuple( i,sName));
    }

  }else cout<<"index is out of range"<<endl;

  return vReturn;
}

    //Display function
    void Table::displayTable();

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
    void Table::addSpecs(tuple<int, int, int > d){
        vSpecs = d;
    }

    //add a row to the row vector
    void Table::addRow(vector<tuple<int, string> > v)
    {
        ofstream outfile;
        string fileName= sTableName +".tbl";
        outfile.open(fileName, ios::binary | ios::out);

        for (size_t i = 0; i < vColumnNames.size()-1; ++i)
        {
            //string sName = get < 0 > (vColumnNames[i]);
            //string sType = get < 1 > (vColumnNames[i]);
            int bSize= get < 4 > (vColumnNames[i]);
            outfile.write((char*)&(get<1>(v[i])), bSize);
        }

        outfile.close();

    }

    //Getters
    string Table::getTableName()
    {
        return sTableName;
    }

