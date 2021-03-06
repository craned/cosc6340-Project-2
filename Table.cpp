/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "Table.h"

const int COLUMN_WIDTH = 20;
//fstream outputFile;

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

  cout << "ERROR: the column was not found" << endl;
  //The column was not found
  return make_tuple(-1, "n/a", false, "n/a");
}
/*****print the whole the table*******/
void Table::printOutTheWholeTable(){
	ofstream outFile;
	outFile.open("output.txt", fstream::out | fstream::app);
	if (!outFile.is_open()) {
		cout << "file not open" << endl;
	} else {
		cout << "file is open" << endl;
		//outFile << "writing\n";
	}
    // Print the lines of the table for a pretty output
    bool toFile = true;
	int PADDING = 6;

//outFile << "column size " << vColumnNames.size();
    // Determine how far to space the column bars
    for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
		int MAX_SPACES = 5;
    	
    	if (get<3>(vColumnNames[i])=="string"){
    		MAX_SPACES = get <4> (vColumnNames[i]) - PADDING;
    		//cout << "string max spaces " << MAX_SPACES << endl;
    	}
    	
        //get the column values for printing
        string sColName = get < 1 > (vColumnNames[i]);
		int numSpaces = MAX_SPACES - sColName.length();
		
		//cout << "here columns1" << endl;
    	if (get<3>(vColumnNames[i])=="string") {
    		//cout << "string numspaces " << numSpaces << endl;
			cout << sColName;
			outFile << sColName;
			//cout << "here columns2" << endl;
		}
		for (int j = 1; j <= numSpaces; j++) {
			//cout << j << "j";
			cout << " ";
			outFile << " ";
			//cout << "here columns3" << endl;
		}
		if (get<3>(vColumnNames[i])=="int"){
			cout << sColName;
			outFile << sColName;
		}
		
		cout << " ";
		outFile << " ";
    }
    cout << "\n";
    outFile << "\n";

//cout << "# of records " << tNumOfRecords;
    for(int i=0; i<tNumOfRecords; i++) {
        for (size_t a = 0; a < vColumnNames.size(); a++){
            std::vector < std::tuple<int, std::string> > row;
            row = getRow(i);
			int MAX_SPACES = 5;

			if (get<3>(vColumnNames[a])=="string"){
				//cout << "here records1" << endl;
				MAX_SPACES = get <4> (vColumnNames[a]) - PADDING;
			}
            
            for(size_t z=0;z<row.size();z++) {
                if (get<0>(row[z]) == get<0>(vColumnNames[a])) {
                	string sColName = get<1> (row[z]);
					
					int numSpaces = MAX_SPACES - sColName.length();
					
						//cout << "here records2" << endl;
                	if (get<3>(vColumnNames[a])=="string"){
						//cout << "here records3" << endl;
						cout << sColName;
						outFile << sColName;
					//	numSpaces = std::get < 4 > (vColumnNames[i]);
					}
					for (int j = 1; j <= numSpaces; j++) {
						//cout << "here records4" << endl;
						cout << " ";
						outFile << " ";
					}
					if (get<3>(vColumnNames[a])=="int"){
						cout << sColName;
						outFile << sColName;
					}
					cout << " ";
					outFile << " ";

                    break;
                }

            }
        }
        
        cout << "\n";
        outFile << "\n";
    }
    
    cout << "\n";
    outFile << "\n";
    
    outFile.close();
}

/***********adding the row to the binary file******/

void Table::addRow( std::vector<std::tuple<int, std::string> > v) {

    //cout << "adding Rows" << endl;
    //cout << "in table " << sTableName << endl;
    string tableName = sTableName + ".tbl";
    ofstream out;
    out.open(tableName, ios::binary | ios::out | ios::app);
    for (size_t i = 0; i < vColumnNames.size(); ++i) {
        if(get<3>(vColumnNames[i])=="string") {
            get<1>(v[i])=Utilities::cleanSpaces(get<1>(v[i]));
            writeStringToFile(get<1>(v[i]), get<4>(vColumnNames[i]), out);
        }
        else if(get<3>(vColumnNames[i])=="int"){
            std::string::size_type sz;
            int value= stol(get<1>(v[i]),&sz);
            writeIntToFile(value,out);

        }
        else cout<<"ERROR: column type mismatch! "<<endl;
    }
    setTNumOfRecords(getTNumOfRecords()+1);
    out.close();
}

//get a row by using index
vector < std::tuple<int, std::string> > Table::getRow(int iIndex) {
    std::vector < std::tuple<int, std::string> > vReturn;
    ifstream in;
    int recordSize=getRecordSize();
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
/****delete the table*****/
void Table::deleteATable(string tableName){
    string name=tableName+".tbl";
    //setTNumOfRecords(0);
    const char* tName=name.c_str();
    if( remove( tName ) != 0 )
        cout << "ERROR: could not delete file" << endl;
    //else
        //cout << "File successfully deleted" << endl;
}
/*****writing the string to the binary file***/
void Table::writeStringToFile(string val,int blockSize, ofstream& out)
{
    
    char* valOut = new char[blockSize];
    for (size_t i = 0; i < blockSize; i++) {
        if(i>=val.length()){
            valOut[i] = '\0';
        }else{
        valOut[i] = val[i];
        }
        //cout<<"valOut[i]: "<<valOut[i]<<endl;
    }
    //valOut[val.length()] = '\0';
    
    out.write(valOut, sizeof(char)*(blockSize));
    //cout<<"write string.val.length(): "<<valO<<endl ;
}
/*****writing int to binary file*****/
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
	
    cout << "ERROR: Primary Key was not set" << endl;
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
