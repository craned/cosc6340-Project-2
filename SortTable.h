
#ifndef GIT2_SORTTABLE_H
#define GIT2_SORTTABLE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <fstream>
#include "fstream"
#include "Utilities.h"
#include "Table.h"
class SortTable
{
public:
int primarykey;
string value;
vector < std::tuple<int, std::string> > vrow;

void getprimarykey(Table ob, int i){

   /*         int numOfRows=ob.getTNumOfRecords();

                       vector<tuple<int, string, bool, string, int> > vNames = ob.getColumnNames(); 
                       int iColumnIndex=-1;
        for (int a = 0; a < vNames.size(); ++a) { 
             
        if (get<2>(vNames[a])==true) { 
                iColumnIndex = a; 
                primarykey=a;
             
        } 
        
        } */
        primarykey=0;
        
}
void getrow(Table ob, int i){
            vector < std::tuple<int, std::string> > vtemp; 
            vtemp=ob.getRow(i); 
            vrow=vtemp;
            value=get<1> (vtemp[primarykey]);
                
}
};
#endif
