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

    //std::vector<std::vector<std::tuple<int, std::string> > > ;
    std::vector<std::string> primaryKey;

//    int tRecordSize=0;
//    int tTotalSize=0;
//    int tNumOfRecords=0;

    tuple<int, int, int> vSpecs;
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
//    void addSpecs(std::tuple<int, int, int > d){
//        vSpecs = d;
//    }


    string delSpaces(string &str)
    {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }


    //add a row to the row vector
    void addRow( std::vector<std::tuple<int, std::string> > v) {

        cout << "adding Rows" << endl;
        cout << "in table " << sTableName << endl;
        string tableName = sTableName + ".tbl";
        ofstream out;
        out.open(tableName, ios::binary | ios::out | ios::app);
        for (int i = 0; i < vColumnName.size(); ++i) {
            if(get<3>(vColumnName[i])=="string") {
                delSpaces(get<1>(v[i]));
                cout<<"get<1>(v[i]): "<<get<1>(v[i])<<endl;
                //cout<<"size of get<1>(v[i]): "<<sizeof(get<1>(v[i]))<<endl;
                writeStringToFile(get<1>(v[i]), get<4>(vColumnName[i]), out);
                cout << "v" << i << ":" << get<1>(v[i]) << endl;
            }
            else if(get<3>(vColumnName[i])=="int"){
                std::string::size_type sz;
                //cout<<"sz: "<<sz<<endl;
                int value= stol(get<1>(v[i]),&sz);
                cout<<"size of this int: "<<sizeof(value)<<endl;
                writeIntToFile(value,out);
                //writeStringToFile(get<1>(v[i]), sizeof(int), out);
            }
            else cout<<"type error! "<<endl;
        }

        out.close();
    }
    void getRow(int iIndex) {
        //std::vector<std::vector<std::tuple<int, std::string> > > vReturn;
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
                cout << "c1: " << c1 << endl;
            } else if(get<3>(vColumnName[i])=="int") {
                int c2;
                char* pmemory = ( char* ) &c2;
                //char *c2 = new char[sizeof(int)];
                in.read(pmemory, sizeof(int));
                cout << "c2: " << c2 << endl;
            }

        }
        in.close();
    }
    int getRecordSize()
    {
        int recordSize=0;
        for (int i = 0; i < vColumnName.size(); ++i) {
            cout<<"get<4>(vColumnName[i]: "<<get<4>(vColumnName[i])<<endl;
            recordSize=recordSize+get<4>(vColumnName[i]);
        }
        cout<<"record size is: "<<recordSize<< endl;
        return recordSize;
    }



    //Getters
    std::string getTableName()
    {
        return sTableName;
    }



    void writeStringToFile(string val,int blockSize, ofstream& out)
    {
        char* valOut = new char[blockSize];
        for (int i = 0; i < blockSize; i++) {
            valOut[i] = val[i];
        }
        //valOut[val.length()] = '\0';

        out.write(valOut, sizeof(char)*(blockSize));
        //cout<<"write string.val.length(): "<<valO<<endl ;
    }

    void writeIntToFile(int num, ofstream& out) {

        out.write((char*) &num, sizeof(int));


    }
//        string numStr = to_string(num);
//        char* numC = new char[numStr.length()+1];
//        for (int i = 0; i < numStr.length(); i++) {
//            numC[i] = numStr[i];
//            //cout << "numC[i] " << numC[i] << endl;
//        }
//        numC[numStr.length()] = '\0';
//
//        out.write(numC, sizeof(char)*(numStr.length()+1));
//        cout<<"write INT: numStr.length(): "<<numStr.length()<<endl;
//    }




    std::tuple<int, std::string, bool, std::string> getColumnIndex(
            std::string sColumnNameIn);

    //std::vector<std::tuple<int, std::string> > getRow(int iIndex);

    std::vector<std::string> getColumnValues(int iIndex);

};

#endif //GIT2_TABLE_H
