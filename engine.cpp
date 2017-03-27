/*******************************************************************************
 File: Engine.cpp
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
 This file contains the implementation for the engine
 *******************************************************************************/

#include "Engine.h"

/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
 *******************************************************************************/

vector<Table> vTableList;

void Engine::createTable(string sTableNameIn,
                         vector<tuple<string, string, int, bool> > vColumnNamesIn,
        /*std::tuple<int, int, int> specs,*/
                         vector<string> vKeys)
{
    for(int i=0; i<vTableList.size();i++){
        if(vTableList[i].getTableName()==sTableNameIn){
            cout<<"this table already exist!"<<endl;
        }
    }

    Table t(sTableNameIn);

    for (int i = 0; i < vColumnNamesIn.size()-1; ++i)
    {
        string sName = get < 0 > (vColumnNamesIn[i]);
        string sType = get < 1 > (vColumnNamesIn[i]);
        int length = get < 2 > (vColumnNamesIn[i]);
        bool bKey = get < 3 > (vColumnNamesIn[i]);

        if(get < 1 > (vColumnNamesIn[i])=="int") length=sizeof(int);

        t.addColumn(make_tuple(i, sName, bKey, sType, length));
    }

    //t.addSpecs(specs);
    t.setTNumOfRecords(0);
    t.setTRecordSize(t.getRecordSize());
    //t.setTTotalSize();

    for (int i = 0; i < vKeys.size(); ++i)
    {
        t.setPrimaryKey(vKeys[i]);
    }

    //push table into the table list

    vTableList.push_back(t);
}

/****************************************************************************
   Adds a row to the specified table
   ****************************************************************************/
void Engine::addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn) {
    for (int i = 0; i < vTableList.size(); ++i) {
        if (vTableList[i].getTableName() == sTableNameIn) {
            vTableList[i].addRow(vRowIn);
            return;

        }
        else{cout<<"this table does not exist!"<<endl;}
    }
}
/****************************************************************************
   get a row to the specified table
   ****************************************************************************/
void Engine::getRow(string sTableNameIn,int iIndex) {
    for (int i = 0; i < vTableList.size(); ++i) {
        if (vTableList[i].getTableName() == sTableNameIn) {
            vTableList[i].getRow(iIndex);
            return;

        }
    }
}
/*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
void Engine::displayTable(string sTableNameIn)
{
    for (int i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            return;
        }
    }
    printf("| The table was not found\n");
}

/*****************************************************************************
   Print out all table schemas
   ****************************************************************************/
void Engine::displayTableSchemas()
{
    //cout << "Grab data from catalog" << endl;
    for (int i = 0; i < vTableList.size(); ++i)
    {
        //if (vTableList[i].getTableName() == sTableNameIn)
        {
            vTableList[i].displayTable();
            //return;
        }
    }
}



int Engine::convertCharToInt(char* val)
{
    string xStr;
    for (int i = 0; i < strlen(val); i++) {
        xStr[i] = val[i];
        //cout << "xStr[i] " << xStr[i] << endl;
    }
    return stoi(xStr);
}

/******************************************************************************/

// If you don't understand these comments, run this query:
// ./dbms "select a,b,k from t1 join t2 on t1.k = t2.kb where b=1;"
void Engine::executeSelect(string sTableNameIn, vector < string > colNames,
                           string whereFilter,
                           string joinTable,
                           string joinFilter)
{
    cout<<"tableName: "<<sTableNameIn<<endl;
    for(int i=0;i<colNames.size();i++){

        cout<<"colNames: "<<colNames[i]<<endl;
    }

    cout<<"whereFilter: "<<whereFilter<<endl;
    cout<<"joinTable: "<<joinTable<<endl;
    cout<<"joinFilter: "<<joinFilter<<endl;

    //spliting whereFilter
    string delimiter = "=";
    string leftSideCondition = whereFilter.substr(0, whereFilter.find(delimiter));
    string rightSideCondition = whereFilter.substr(whereFilter.find(delimiter) + delimiter.length(), whereFilter.length());
    cout<<"leftSideCondition "<<leftSideCondition<<endl;
    cout<<"rightSideCondition "<<rightSideCondition<<endl;

    int iColumnIndex = -1;
    string sColumnType;

    //make a temp table
    string sTableNameOut = sTableNameIn +"T2";
    Table tNewTable(sTableNameOut);


    std::vector < std::tuple<int, std::string> > vtest;
    cout<<"select from table: "<<vTableList[0].getTableName()<<endl;

    for (int i = 0; i < vTableList.size(); ++i) {
        Table tCurrentTable = vTableList[i];

        //Execute if the table is found in the list
        if (tCurrentTable.getTableName() == sTableNameIn) {
            //printout the current table
            tCurrentTable.printOutTheWholeTable();

            //Input the column names and types into the new table, then determine
            //the rows to copy over
            vector<tuple<int, string, bool, string, int> > vNames =
                    tCurrentTable.getColumnNames();

            for (int a = 0; a < vNames.size(); ++a) {
                if (a == get<0>(vNames[a])) {
                    //Add column to new table
                    tNewTable.addColumn(vNames[a]);
                    //cout<<"get<1>(vNames[a])"<<get<1>(vNames[a])<<endl;
                    //cout<<"leftSideCondition:"<<leftSideCondition<<endl;
                    if (get<1>(vNames[a]).compare(leftSideCondition) ==0) {
                        iColumnIndex = a;
                        //sColumnType = get<3>(vNames[a]);
                    }
                }
            }
            //See if the column exists in the table
            if (iColumnIndex == -1) {
                printf("| The column does not exist.\n");
            } else {
                //get the values for the column
                //*******need to be changed*******************************************
                int numOfRows=tCurrentTable.getTNumOfRecords();
                //int numOfRows= 3;

                for(int i=0; i<numOfRows; i++){
                    std::vector < std::tuple<int, std::string> > vtemp;
                    vtemp=tCurrentTable.getRow(i);
                        if(get < 1 > (vtemp[iColumnIndex]).compare(rightSideCondition) == 0){
                            tNewTable.addRow(tCurrentTable.getRow(i));
                        }
                }
            }

        }else{
            cout<<"You are selecting from a table that does not exist! "<<endl;
        }
    }
    vTableList.push_back(tNewTable);
    tNewTable.printOutTheWholeTable();




    //if there is no selection - select *
    if(colNames.size()==1 and colNames[0]=="*") {
        //printing out the whole table:
        tNewTable.printOutTheWholeTable();
        deleteATable(tNewTable);
        tNewTable.setTNumOfRecords(0);
    }else{
        //make a temp table
        string name = tNewTable.getTableName() +"T2";
        Table tNewNewTable(name);
        vector<int> indexes;
        for(int x=0;x<colNames.size();x++) {
            for (int i = 0; i < tNewTable.getColumnNames().size(); i++) {
                if (colNames[x] == get<1>(tNewTable.getColumnNames()[i])) {
                    tNewNewTable.addColumn(
                            make_tuple(x, get<1>(tNewTable.getColumnNames()[i]), get<2>(tNewTable.getColumnNames()[i]),
                                       get<3>(tNewTable.getColumnNames()[i]), get<4>(tNewTable.getColumnNames()[i])));
                    indexes.push_back(get<0>(tNewTable.getColumnNames()[i]));

                }
            }
        }
        for(int j=0;j<tNewTable.getTNumOfRecords();j++) {
            vector<std::tuple<int, std::string> > row;
            for (int l = 0; l < tNewTable.getColumnNames().size(); l++) {
                for (int w = 0; w < indexes.size(); w++) {
                    if (indexes[w] == get<0>(tNewTable.getRow(j)[l])) {
                        row.push_back(make_tuple(w, get<1>(tNewTable.getRow(j)[l])));
                    }
                }
            }
            tNewNewTable.addRow(row);
        }
        vTableList.push_back(tNewNewTable);
        tNewNewTable.printOutTheWholeTable();

        deleteATable(tNewTable);
        deleteATable(tNewNewTable);
        tNewTable.setTNumOfRecords(0);
        tNewNewTable.setTNumOfRecords(0);
        //cout<<"numOfrec"<<tNewTable.getTNumOfRecords()<<endl;
        //cout<<"numOfrec2"<<tNewNewTable.getTNumOfRecords()<<endl;
        for(int i=0; i<vTableList.size(); i++){
            cout<<"remaining tables: "<<vTableList[i].getTableName()<<endl;
        }
    }


}
void Engine::deleteATable(Table table){
    for(int i=0; i<vTableList.size(); i++){
        if (table.getTableName()==vTableList[i].getTableName()){
            vTableList.erase(vTableList.begin()+i);
            table.setTNumOfRecords(0);
            table.deleteATable(table.getTableName());
        }
    }

}
