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
    void addRow( std::vector<std::tuple<int, std::string> > v) {

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
    vector < std::tuple<int, std::string> > getRow(int iIndex) {
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


    void deleteATable(string tableName){
        string name=tableName+".tbl";
        //setTNumOfRecords(0);
        const char* tName=name.c_str();
        if( remove( tName ) != 0 )
            perror( "Error deleting file" );
        else
            puts( "File successfully deleted" );
    }

};

#endif //GIT2_TABLE_H
