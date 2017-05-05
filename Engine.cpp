/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/

#include "Engine.h"
#include <cstdio>
#include "SortTable.h"
#include <algorithm>
#include <string>
const int COLUMN_WIDTH = 20;
/*******************************************************************************
 This function will take in a vector of column names and trailing primary keys,
 and an integer specifying how many columns are in the vector.
 *******************************************************************************/

vector<Table> vTableList;
vector<string> vSTemplist;
void Engine::createTable(string sTableNameIn,
                         vector<tuple<string, string, int, bool> > vColumnNamesIn,
                         vector<string> vKeys)
{

    bool isTableFound=false;
    for (size_t i = 0; i < vTableList.size(); i++) {
        cout << "existing table: " << vTableList[i].getTableName()<<endl;
        if (vTableList[i].getTableName() == sTableNameIn) {
            isTableFound = true;
//            cout << "vTableList[i].getTableName(): " << vTableList[i].getTableName() << endl;
//            cout << "sTableNameIn: " << sTableNameIn << endl;
            break;
        }
    }
    
    if(isTableFound) {
        cout << "ERROR: this table already exists! SO Not being added!" << endl;
    }else{
        Table t(sTableNameIn);
        
        for (size_t i = 0; i < vColumnNamesIn.size() - 1; ++i) {
            string sName = Utilities::cleanSpaces(get<0>(vColumnNamesIn[i]));
            string sType = Utilities::cleanSpaces(get<1>(vColumnNamesIn[i]));
            int length = get<2>(vColumnNamesIn[i]);
            bool bKey = get<3>(vColumnNamesIn[i]);
            
            if (get<1>(vColumnNamesIn[i]) == "int") {
                length = sizeof(int);
            } else {
                length = length+6;
            }
            
            t.addColumn(make_tuple(i, sName, bKey, sType, length));
        }
        
        //t.addSpecs(specs);
        t.setTNumOfRecords(0);
        t.setTRecordSize(t.getRecordSize());
        //t.setTTotalSize();
        
        for (size_t i = 0; i < vKeys.size(); ++i) {
            t.setPrimaryKey(vKeys[i]);
        }
        
        cout << "TABLE " << sTableNameIn << " created successfully" << endl;
        
        //push table into the table list
        vTableList.push_back(t);
    }
}

/****************************************************************************
 Adds a row to the specified table
 ****************************************************************************/
void Engine::addRow(string sTableNameIn, vector<tuple<int, string> > vRowIn) {
    bool isFoundTable=false;
    for (size_t i = 0; i < vTableList.size(); ++i) {
        if (vTableList[i].getTableName() == sTableNameIn) {
            Table tb=vTableList[i];
            int iColumnIndex= -1;
            int numOfRows=tb.getTNumOfRecords();
            vector<tuple<int, string, bool, string, int> > vNames = vTableList[i].getColumnNames();
            for (size_t a = 0; a < vNames.size(); ++a) {
                
                if (get<2>(vNames[a])==true) {
                    iColumnIndex = a;
                    
                }
                
            }
            if(iColumnIndex!=-1){
                for(int i=0; i<numOfRows; i++){
                    vector < std::tuple<int, std::string> > vtemp;
                    vtemp=tb.getRow(i);
                    string giventemp=get<1> (vRowIn[iColumnIndex]);
                    if(get < 1 > (vtemp[iColumnIndex])==(giventemp)){
                        cout<<"ERROR: duplicate primary key";
                        isFoundTable = true;
                        return;
                    }
                    vtemp.clear();
                }
            }
            
            vTableList[i].addRow(vRowIn);
            isFoundTable = true;
            return;
            
        }
    }
    if(!isFoundTable) cout<<"ERROR: this table does not exist!"<<endl;
}

/*****************************************************************************
   Print out the table with the given name
   ****************************************************************************/
void Engine::displayTable(string sTableNameIn)
{
	const int COLUMN_WIDTH = 20;
    for (size_t i = 0; i < vTableList.size(); ++i)
    {
        if (vTableList[i].getTableName() == sTableNameIn)
        {
            //vTableList[i].displayTable();
            cout<<"\n"<<vTableList[i].getTableName()<<"\n";
            vector<tuple<int, string, bool, string, int > > vColumnNames;
            vColumnNames=vTableList[i].getColumnNames();
            for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        std::cout << "+-----------";
    }
    std::cout << "\n";
            
            
			for (size_t j = 0; j <vColumnNames.size(); ++j)
			{
				//get the column values for printing
				string sColName = get < 1 > (vColumnNames[j]);
				bool bPrimaryKey = get < 2 > (vColumnNames[j]);

				//see if it is a primary key, for formatting
				if (bPrimaryKey)
				{
					cout << " | " << left << "*" + sColName + "*"<<" ";
               if(get < 3 > (vColumnNames[j])=="string"){
               
          cout<<"CHAR";
          int c=get < 4 > (vColumnNames[j])-6;
          cout<<"("<<c<<")";
          }
          else{
          cout<<get < 3 > (vColumnNames[j]);
          }
				}
				else
				{
					cout << " | "  << left << sColName<<" ";
          if(get < 3 > (vColumnNames[j])=="string"){
          cout<<"CHAR";
          int c=get < 4 > (vColumnNames[j])-6;
          cout<<"("<<c<<")";
          }
          else{
          cout<<get < 3 > (vColumnNames[j]);
          }
				}

			}
      cout<<"\n";
      for (size_t i = 0; i < vColumnNames.size(); ++i)
    {
        std::cout << "+-----------";
    }
    std::cout << "\n";
			
			std::vector<std::string> primaryKey=vTableList[i].getPrimaryKey();
			cout<<"Primary keys :";
			for (size_t j = 0; j <primaryKey.size(); ++j)
			{
				cout<<primaryKey[j];
			}
      cout<<"\n";
      cout<<"Number of records : "<<vTableList[i].getTNumOfRecords();		  
      cout<<"\n";  
      vTableList[i].calculateRecordSize();
            cout<<"Size of record : "<<vTableList[i].getTRecordSize();		  
      cout<<"\n";
      vTableList[i].calculateTotalRecordSize();
                  cout<<"Size of All records : "<<vTableList[i].getTTotalSize();		  
      cout<<"\n";    
		    return;
		}
	}
	
	cout << "ERROR: The table was not found" << endl;
}

/*****************************************************************************
   Print out all table schemas
   ****************************************************************************/
void Engine::displayTableSchemas()
{
	//cout << "Grab data from catalog" << endl;
	for (size_t i = 0; i < vTableList.size(); ++i)
    {
        //if (vTableList[i].getTableName() == sTableNameIn)
        {
            displayTable(vTableList[i].getTableName());
            //return;
        }
    }
}

int Engine::convertCharToInt(char* val)
{
	string xStr;
	for (size_t i = 0; i < strlen(val); i++) {
		xStr[i] = val[i];
		//cout << "xStr[i] " << xStr[i] << endl;
	}
	return stoi(xStr);
}

/******************************************************************************/
Table Engine::whereClause(string tCurrentTableStr, string whereFilter){

    Table tCurrentTable;
    for(int h=0; h<vTableList.size();h++){
        if(vTableList[h].getTableName()==tCurrentTableStr){
            tCurrentTable=vTableList[h];
        }
    }

    string sTableNameOut = "w"+ tCurrentTableStr;
    Table tNewTable(sTableNameOut);
    tNewTable.setTNumOfRecords(0);

    if(whereFilter!="") {
        string delimiter = "=";
        string leftSideCondition = whereFilter.substr(0, whereFilter.find(delimiter));
        string rightSideCondition = whereFilter.substr(whereFilter.find(delimiter) + delimiter.length(),
                                                       whereFilter.length());
        string tableName = "";
        tableName= realTableVal(leftSideCondition);
        string columnName = realColVal(leftSideCondition);

        bool columnFound= false;
        if(tableName==""){

            for(int k=0; k<tCurrentTable.getColumnNames().size(); k++) {
                if (columnName == get<1>(tCurrentTable.getColumnNames()[k])) {
                    columnFound = true;
                }
            }
        }

        if(columnFound) {
            tableName = tCurrentTableStr;
        }


        if (tableName == tCurrentTableStr) {
            int iColumnIndex = -1;
            //Input the column names and types into the new table, then determine
            //the rows to copy over
            vector<tuple<int, string, bool, string, int> > vNames =
                    tCurrentTable.getColumnNames();
            cout << "tCurrentTable: " << tCurrentTable.getTableName() << endl;
            for (size_t a = 0; a < vNames.size(); ++a) {
                if ((int) a == get<0>(vNames[a])) {
                    //Add column to new table
                    tNewTable.addColumn(vNames[a]);
                    //cout<<"get<1>(vNames[a])"<<get<1>(vNames[a])<<endl;
                    //cout<<"leftSideCondition:"<<leftSideCondition<<endl;
                    if (get<1>(vNames[a]).compare(columnName) == 0) {
                        iColumnIndex = a;
                    }
                }
            }
            //See if the column exists in the table
            if (iColumnIndex == -1) {
                cout << "ERROR: the column does not exist." << endl;
            } else {
                //get the values for the column
                int numOfRows = tCurrentTable.getTNumOfRecords();
                for (int i = 0; i < numOfRows; i++) {
                    std::vector<std::tuple<int, std::string> > vtemp;
                    vtemp = tCurrentTable.getRow(i);
                    if (get<1>(vtemp[iColumnIndex]).compare(rightSideCondition) == 0) {
                        tNewTable.addRow(tCurrentTable.getRow(i));
                    }
                }
            }
            return tNewTable;
        }

            //not for this table:
        else{
            cout<<"ERROR: " << columnName <<" does not exist in table "<< tCurrentTable.getTableName()<<endl;
            //add columns:
            vector<tuple<int, string, bool, string, int> > vNames =
                    tCurrentTable.getColumnNames();
            for (size_t a = 0; a < vNames.size(); ++a) {
                if ((int) a == get<0>(vNames[a])) {
                    tNewTable.addColumn(vNames[a]);
                }
            }
            //adding rows
            for(int i=0; i<tCurrentTable.getTNumOfRecords(); i++){
                tNewTable.addRow(tCurrentTable.getRow(i));
            }
            return tNewTable;
        }

    }
//    //has no where filter:
//    else{
//        //add columns:
//        vector<tuple<int, string, bool, string, int> > vNames =
//                tCurrentTable.getColumnNames();
//        for (size_t a = 0; a < vNames.size(); ++a) {
//            if ((int) a == get<0>(vNames[a])) {
//                tNewTable.addColumn(vNames[a]);
//            }
//        }
//        //adding rows
//        for(int i=0; i<tCurrentTable.getTNumOfRecords(); i++){
//            tNewTable.addRow(tCurrentTable.getRow(i));
//        }
//        return tNewTable;
//    }

}
/******************************************************************************/
Table Engine::selectClause(string tNewTableStr,vector < string > colNames, string originalTablestr, bool &returnBool, string tempTable, string sumCol){


    Table tNewTable;
    Table originalTable;
    for(int p=0;p<vTableList.size();p++){
        if(vTableList[p].getTableName()==tNewTableStr){
            tNewTable=vTableList[p];
        }
        if(vTableList[p].getTableName()==originalTablestr){
            originalTable=vTableList[p];
        }
    }
    string name = "s"+tNewTableStr;
    if(tempTable !=""){
        name = tempTable;
        vSTemplist.push_back(name);
    }

    Table tNewNewTable(name);
    tNewNewTable.setTNumOfRecords(0);
    vector<int> indexes;
    int seq=0;
    //if there is no selection - select *
    if (colNames.size() == 1 and colNames[0] == "*") {
        //adding columns
        for (size_t i = 0; i < tNewTable.getColumnNames().size(); i++) {
            tNewNewTable.addColumn(tNewTable.getColumnNames()[i]);
        }
        //adding rows
        for (int j = 0; j < tNewTable.getTNumOfRecords(); j++) {
            tNewNewTable.addRow(tNewTable.getRow(j));
        }
        return tNewNewTable;

    //selectionS
    } else {
        for (size_t x = 0; x < colNames.size(); x++) {
        	string sumPlaceholder = "SUMTEAM06COL";
            size_t found = colNames[x].find(sumPlaceholder);
            if (found!=std::string::npos) {
                colNames[x]=sumCol;
            }
            bool isColumnFound=false;
            string tableName = "";
            string columnName = "";
            tableName = realTableVal(colNames[x]);
            columnName = realColVal(colNames[x]);
            //cout<<"tableName "<<tableName<<endl;
            //cout<<"columnName "<<columnName<<endl;
            if (columnName.find(sumPlaceholder) != string::npos) {
            	columnName = columnName.substr(sumPlaceholder.length(), string::npos);
            }

                string wtableName="w"+tableName;
                //when there is no table name
                if(tableName==""){
                    cout << "columnName " << columnName << endl;
                    for (size_t i = 0; i < tNewTable.getColumnNames().size(); i++) {
                        //cout<<"get<1>(tNewTable.getColumnNames()[i]) "<<get<1>(tNewTable.getColumnNames()[i])<<endl;
                        if (columnName == get<1>(tNewTable.getColumnNames()[i])) {
                            tNewNewTable.addColumn(
                                    make_tuple(seq, get<1>(tNewTable.getColumnNames()[i]),
                                               get<2>(tNewTable.getColumnNames()[i]),
                                               get<3>(tNewTable.getColumnNames()[i]),
                                               get<4>(tNewTable.getColumnNames()[i])));
                            seq++;
                            indexes.push_back(get<0>(tNewTable.getColumnNames()[i]));
                            isColumnFound = true;
                        }
                    }
                    if (!isColumnFound) {
                        cout << "ERROR -1: wrong column selected for select-clause!" << endl;
                        returnBool = false;
                    }
                }
                    //when there is a table name and it is the first name
                else if((tableName)== originalTable.getTableName() or wtableName==originalTable.getTableName()) {
                    //cout << "columnName " << columnName << endl;
                    for (size_t i = 0; i < tNewTable.getColumnNames().size(); i++) {
                        //cout<<"get<1>(tNewTable.getColumnNames()[i]) "<<get<1>(tNewTable.getColumnNames()[i])<<endl;
                        if (columnName == get<1>(tNewTable.getColumnNames()[i])) {
                            if (i < originalTable.getColumnNames().size()) {
                                tNewNewTable.addColumn(
                                        make_tuple(seq, get<1>(tNewTable.getColumnNames()[i]),
                                                   get<2>(tNewTable.getColumnNames()[i]),
                                                   get<3>(tNewTable.getColumnNames()[i]),
                                                   get<4>(tNewTable.getColumnNames()[i])));
                                seq++;
                                indexes.push_back(get<0>(tNewTable.getColumnNames()[i]));
                                isColumnFound = true;
                            }
                        }
                    }
                    if (!isColumnFound) {
                        cout << "ERROR -1: wrong column selected for select-clause!" << endl;
                        returnBool = false;
                    }
                }//when there is a table name and it is the second one
                else{
                    for (size_t i = 0; i < tNewTable.getColumnNames().size(); i++) {
                        if (columnName == get<1>(tNewTable.getColumnNames()[i])) {
                            if (i >= originalTable.getColumnNames().size()) {
                                tNewNewTable.addColumn(
                                                       make_tuple(seq, get<1>(tNewTable.getColumnNames()[i]),
                                                                  get<2>(tNewTable.getColumnNames()[i]),
                                                                  get<3>(tNewTable.getColumnNames()[i]),
                                                                  get<4>(tNewTable.getColumnNames()[i])));
                                seq++;
                                indexes.push_back(get<0>(tNewTable.getColumnNames()[i]));
                                isColumnFound = true;
                            }
                        }
                    }
                    if (!isColumnFound){
                        cout << "ERROR -2: wrong column selected for select-clause!" << endl;
                        returnBool=false;
                    }
                }

        }
        //adding rows
        for (int j = 0; j < tNewTable.getTNumOfRecords(); j++) {
            int seq=0;
            vector<std::tuple<int, std::string> > row;
            for (size_t w = 0; w < indexes.size(); w++) {
                for (size_t l = 0; l < tNewTable.getColumnNames().size(); l++) {
                    if (indexes[w] == get<0>(tNewTable.getRow(j)[l])) {
                        row.push_back(make_tuple(seq, get<1>(tNewTable.getRow(j)[l])));
                        seq++;
                    }
                }
            }
            tNewNewTable.addRow(row);
        }

        return tNewNewTable;
    }
}

/******************************************************************************/
Table Engine::joinClause(string originalTableStr,string joinTableStr,string joinFilter, bool &returnBool){
    
    if(joinFilter!="") {

        Table originalTable;
        Table joinTable;
        for(int i=0; i<vTableList.size(); i++){
            if(vTableList[i].getTableName()==originalTableStr){
                originalTable=vTableList[i];
                //cout<<"name of originalTable " <<originalTable.getTableName()<<endl;
            }
            if(vTableList[i].getTableName()==joinTableStr){
                joinTable = vTableList[i];
                //cout<<"name of joinTable " <<joinTable.getTableName()<<endl;
            }
        }

        string delimiter = "=";
        string leftSideCondition = joinFilter.substr(0, joinFilter.find(delimiter));
        string rightSideCondition = joinFilter.substr(joinFilter.find(delimiter) + delimiter.length(),
                                                      joinFilter.length());
        //leftSide
        string leftTable = "";
        string leftColumn = "";
        leftTable = realTableVal(leftSideCondition);
        leftColumn = realColVal(leftSideCondition);
        string lDelimiter = ".";
        //RightSide
        string rightTable = "";
        string rightColumn = "";
        rightTable = realTableVal(rightSideCondition);
        rightColumn = realColVal(rightSideCondition);
//        cout<<"leftTable "<<leftTable<<endl;
//        cout<<"leftColumn "<<leftColumn<<endl;
//        cout<<"rightTable "<<rightTable<<endl;
//        cout<<"rightColumn "<<rightColumn<<endl;
        string name = "J" + originalTable.getTableName() + joinTable.getTableName();
//        cout<<"neme of the new tabel "<<name<< endl;
        Table joinedTable(name);
        joinedTable.setTNumOfRecords(0);
        int indexLeft = -1;
        int indexRight = -1;
        ///////////////////////merging headers
        vector<tuple<int, string, bool, string, int> > vOriginalTableColumn =
                originalTable.getColumnNames();
        vector<tuple<int, string, bool, string, int> > vJoinTableColumn =
                joinTable.getColumnNames();
        //vector<tuple<int, string, bool, string, int> > vCombinedTableColumn;
        ////////////////////////
        string wLeftTable="w"+leftTable;
        string wRightTable="w"+rightTable;

//        cout<<"leftTable "<<leftTable<<endl; 
//        cout<<"originalTable.getTableName() "<<originalTable.getTableName()<<endl;
//         cout<<"rightTable "<<rightTable<<endl;
//         cout<<"joinTable.getTableName() "<<joinTable.getTableName()<<endl;


        if (leftTable!=originalTable.getTableName() and wLeftTable!=originalTable.getTableName()) {
            if (rightTable!=joinTable.getTableName() and wRightTable!=joinTable.getTableName()) {
                leftTable.swap(rightTable);
                leftColumn.swap(rightColumn);
                //cout<<"originalTable.getTableName(): "<<originalTable.getTableName()<<endl;
                //cout<<"leftTable: "<<leftTable<<endl;
                //cout<<"joinTable.getTableName(): "<<joinTable.getTableName()<<endl;
                //cout<<"rightTable: "<<rightTable<<endl;
            }
        }
        if (leftTable==originalTable.getTableName() or wLeftTable ==originalTable.getTableName() ) {
            if (rightTable==joinTable.getTableName() or wRightTable == joinTable.getTableName()) {
                for (size_t i = 0; i < vOriginalTableColumn.size(); i++) {
                    //getting the index
                    if (get<1>(vOriginalTableColumn[i]) == leftColumn) {
                        indexLeft = get<0>(vOriginalTableColumn[i]);
                    }
                    //inserting columns from original table
                    if ((int) i == get<0>(vOriginalTableColumn[i])) {
                        joinedTable.addColumn(vOriginalTableColumn[i]);
                    }
                }
                for (size_t i = 0; i < vJoinTableColumn.size(); i++) {
                    //getting the right index
                    //cout << "get<1>(vJoinTableColumn[i]: " << get<1>(vJoinTableColumn[i]) << endl;
                    //cout << "rightColumn: " << rightColumn << endl;
                    if (get<1>(vJoinTableColumn[i]) == rightColumn) {
                        indexRight = get<0>(vJoinTableColumn[i]);
                    }
                }
                int x = 0;
                for (size_t i = 0; i < vJoinTableColumn.size(); i++) {
                    //inserting columns from join table

                    if ((int) i == get<0>(vJoinTableColumn[i])) {
                        if (get<0>(vJoinTableColumn[i]) != indexRight) {

                            joinedTable.addColumn(
                                    make_tuple(x + vOriginalTableColumn.size(), get<1>(vJoinTableColumn[i]),
                                               get<2>(vJoinTableColumn[i]),
                                               get<3>(vJoinTableColumn[i]),
                                               get<4>(vJoinTableColumn[i])));
                            x++;
                        }
                    }
                }
            }else{
                cout<<"ERROR: Wrong table name"<<endl;
                returnBool=false;
            }
        }else{
            cout<<"ERROR: Wrong table name"<<endl;
            returnBool=false;
        }


        //////////////////////////
        //if (indexLeft != -1 and indexRight != -1) {
        for (int l = 0; l < originalTable.getTNumOfRecords(); l++) {
            for (int r = 0; r < joinTable.getTNumOfRecords(); r++) {
//                cout<<"get<1>(originalTable.getRow(l)[indexLeft]) "<<get<1>(originalTable.getRow(l)[indexLeft])<<endl;
//                cout<<"get<1>(joinTable.getRow(r)[indexRight])" <<get<1>(joinTable.getRow(r)[indexRight])<<endl;
                if (get<1>(originalTable.getRow(l)[indexLeft]) ==
                    get<1>(joinTable.getRow(r)[indexRight])) {

                    vector<std::tuple<int, std::string> > newRow;
                    for (size_t k = 0; k < originalTable.getRow(l).size(); k++) {
                        newRow.push_back(originalTable.getRow(l)[k]);
                    }
                    for (size_t j = 0; j < joinTable.getRow(r).size(); j++) {
                        if (get<0>(joinTable.getRow(r)[j]) != indexRight) {
                            newRow.push_back(joinTable.getRow(r)[j]);
                        }
                    }
                    //fixing the index in the new rows
                    for (size_t u = 0; u < newRow.size(); u++) {
                        get<0>(newRow[u]) = u;
                    }
                    joinedTable.addRow(newRow);
                }
            }
        }
        return joinedTable;
    }

}

/******************************************************************************/
/* Group by function */
/******************************************************************************/
Table Engine::groupByClause(Table currentTable, string groupByCol, string sumCol)
{
	Table temp;
    vector<tuple<int, string, bool,string, int>> vColumnNames = 
    											currentTable.getColumnNames();
	// find group by index
	int groupByIndex = -1;
	cout << "#column Names " << vColumnNames.size() << endl;
	for (int i = 0; i < vColumnNames.size(); i++) {
		cout << "gb test " << get<1>(vColumnNames[i]) << endl;
		if (groupByCol == get<1>(vColumnNames[i])) {
			groupByIndex = get<0>(vColumnNames[i]);
		}
	}
	if (groupByIndex == -1) {
		cout << "ERROR: " << groupByCol << " does not exist1" << endl;
		return temp;
	}
	
	// sort values by group by index
	temp = sortp(currentTable.getTableName(), groupByIndex);
	
	// find index of sum column
	Table finalGB;
	if (!sumCol.empty()) {
		int sumColIndex = -1;
		for (int i = 0; i < vColumnNames.size(); i++) {
			if (sumCol == get<1>(vColumnNames[i])) {
				sumColIndex = get<0>(vColumnNames[i]);
			}
		}
		if (sumColIndex == -1) {
			cout << "ERROR: " << sumCol << " does not exist2" << endl;
			return temp;
		}

cout << "groupByIndex " << groupByIndex << endl;
cout << "sumColIndex " << sumColIndex << endl;
		// sum up cumColIndex by groupByCol
		finalGB = sum(temp, sumCol, sumColIndex,
											groupByCol, groupByIndex);
	} else {
		return temp;
	}
	
	deleteATable(temp);
	return finalGB;
}

/******************************************************************************/
/* order by function */
/******************************************************************************/
Table Engine::orderByClause(Table currentTable, string orderByCol)
{
	Table temp("");
    vector<tuple<int, string, bool,string, int>> vColumnNames = 
    											currentTable.getColumnNames();
    											
	// find order by index
	int orderByIndex = -1;
	for (int i = 0; i < vColumnNames.size(); i++) {
		if (orderByCol == get<1>(vColumnNames[i])) {
			orderByIndex = get<0>(vColumnNames[i]);
		}
	}
	if (orderByIndex == -1) {
		cout << "ERROR: " << orderByCol << " does not exist" << endl;
		return temp;
	}
	
	// sort values by order by index
	temp = sortp(currentTable.getTableName(), orderByIndex);
	
	return temp;
}

/******************************************************************************/
/* Main select function */
/******************************************************************************/
bool Engine::executeSelect(string sTableNameIn, vector < string > colNames,
                           string tempTable,
                           string whereFilter,
                           string joinTable,
                           string joinFilter,
                           string groupByCol,
                           string orderByCol,
                           string sumCol) {
    sTableNameIn = Utilities::cleanSpaces(sTableNameIn);
    tempTable = Utilities::cleanSpaces(tempTable);
    whereFilter = Utilities::cleanSpaces(whereFilter);
    joinTable = Utilities::cleanSpaces(joinTable);
    joinFilter = Utilities::cleanSpaces(joinFilter);
    groupByCol = Utilities::cleanSpaces(groupByCol);
    orderByCol = Utilities::cleanSpaces(orderByCol);
    sumCol = Utilities::cleanSpaces(sumCol);
    for(size_t k=0; k<colNames.size(); k++){
        colNames[k] = Utilities::cleanSpaces(colNames[k]);
    }

    ///////////
    bool returnBool= true;
    string curTableStr= sTableNameIn;
    string curJoinTablestr = joinTable;
    Table whereTableOriginal;
    Table whereTableJoin;
    if(!whereFilter.empty()){
        whereTableOriginal=whereClause(curTableStr, whereFilter);
        vTableList.push_back(whereTableOriginal);
        curTableStr=whereTableOriginal.getTableName();
        //!
        //cout<<"WHERE FILTER"<<endl;
        //whereTableOriginal.printOutTheWholeTable();
        if(!joinFilter.empty()){
            whereTableJoin= whereClause(curJoinTablestr, whereFilter);
            vTableList.push_back(whereTableJoin);
            curJoinTablestr = whereTableJoin.getTableName();
            //!
            //cout<<"WHERE FILTER ON JOIN "<<endl;
            //whereTableJoin.printOutTheWholeTable();
        }
    }

    Table joinedTable;
    if(!joinFilter.empty()){
        joinedTable=joinClause(curTableStr, curJoinTablestr, joinFilter, returnBool);
        vTableList.push_back(joinedTable);
        curTableStr=joinedTable.getTableName();
        //!
        //cout<<"JOIN TABLE"<<endl;
        //joinedTable.printOutTheWholeTable();
    }

    Table selectTable;
    selectTable = selectClause(curTableStr, colNames, sTableNameIn, returnBool, tempTable, sumCol);
    vTableList.push_back(selectTable);
    curTableStr=selectTable.getTableName();
    //!
    //cout<<"SELECT TABLE"<<endl;
    //selectTable.printOutTheWholeTable();

    Table groupByTable;
    if (!groupByCol.empty()) {
    	cout << "executing group by" << endl;
        groupByTable = groupByClause(selectTable, groupByCol, sumCol);
        curTableStr = groupByTable.getTableName();
    }
    Table orderByTable;
    if (!orderByCol.empty()) {
    	if (!groupByCol.empty()) {
        	orderByTable = orderByClause(groupByTable, orderByCol);
        } else {
        	orderByTable = orderByClause(selectTable, orderByCol);
        }
        curTableStr = orderByTable.getTableName();
    }



    if(whereTableOriginal.getTableName()!=curTableStr){
        deleteATable(whereTableOriginal);
    }
    if(whereTableJoin.getTableName() != curTableStr){
        deleteATable(whereTableJoin);
    }
    if(joinedTable.getTableName() != curTableStr){
        deleteATable(joinedTable);
    }
    if(selectTable.getTableName() != curTableStr){
        deleteATable(selectTable);
    }
    if(groupByTable.getTableName() != curTableStr){
        deleteATable(groupByTable);
    }
    if(orderByTable.getTableName() != curTableStr){
        deleteATable(orderByTable);
    }
    //cout<<"curTableStr "<<curTableStr<<endl;
    for(int j=0; j<vTableList.size();j++){
        if(vTableList[j].getTableName()==curTableStr){
            if(tempTable ==""){
                vTableList[j].printOutTheWholeTable();
                deleteATable(vTableList[j]);
                //cout<<vTableList[j].getTableName()<<" got deleted"<<endl;
            } else{
                //vTableList[j].setName(tempTable);
                //cout<<"the new table's name is "<<vTableList[j].getTableName()<<endl;
            }
        }
    }


    return returnBool;

}
/*****************************************************************************
   realColVal takes a column name and returns the pure col name
   ****************************************************************************/
string Engine::realColVal(string col){
    string delimiter = ".";
    std::size_t foundDOT = col.find(delimiter, 0);
    //if it has a DOT
    if (foundDOT != std::string::npos) {
        //cout << "col is in the form of TABLE.COLUMN" << endl;
        string table = col.substr(0, col.find(delimiter));
        string column = col.substr(col.find(delimiter) + delimiter.length(),
                                   col.length());
        return column;
    }else{
        return col;
    }

}
/*****************************************************************************
   realTableVal takes a column name and returns the table name before the column
   ****************************************************************************/
string Engine::realTableVal(string col){
    string delimiter = ".";
    std::size_t foundDOT = col.find(delimiter, 0);
    //if it has a DOT
    if (foundDOT != std::string::npos) {
        //cout << "col is in the form of TABLE.COLUMN" << endl;
        string table = col.substr(0, col.find(delimiter));
        string column = col.substr(col.find(delimiter) + delimiter.length(),
                                   col.length());
        return table;
    }
    else return "";
}
/*****************************************************************************
   deleteATable
   ****************************************************************************/

void Engine::deleteATable(Table table){
    dropTable(table.getTableName());
}
/*****************************************************************************
   DROP the table with the given name
   ****************************************************************************/
void Engine::dropTable(string sTableNameIn)
{
	for (size_t i=0; i<vTableList.size(); i++){
        if (vTableList[i].getTableName() == sTableNameIn){
            vTableList.erase(vTableList.begin()+i);
            vTableList[i].deleteATable(sTableNameIn);
        }
    }
}
/*****************************************************************************
   QUIT: removes all temp Tables
   ****************************************************************************/
void Engine::executeQuit(){
    for (size_t i=0; i<vSTemplist.size(); i++){
        for (size_t j=0; j<vTableList.size(); j++){
            if(vTableList[j].getTableName()==vSTemplist[i]){
                dropTable(vSTemplist[i]);
            }
        }
    }
    for (size_t j=0; j<vTableList.size(); j++){
        cout<<"remaining Table: "<<vTableList[j].getTableName()<<endl;
    }

}
/*****************************************************************************
   insertFromSelect
   ****************************************************************************/
void Engine::insertFromSelect(string sTableNameFrom, string sTableNameTo ){
    //cout<<"sTableNameFrom "<<sTableNameFrom<<" sTableNameTo "<<sTableNameTo<<endl;
    bool foundTable = false;
        bool insertvalidate=false;
    for(int i=0;i<vTableList.size();i++){
        if(sTableNameFrom==vTableList[i].getTableName()) {
            Table fromTable;
            fromTable = vTableList[i];
            for(int j=0;j<vTableList.size();j++) {
                if(sTableNameTo==vTableList[j].getTableName()) {
                    Table toTable = vTableList[j];
                    insertvalidate=insertselectValidate(fromTable, toTable);//checking whether the rows from select can be inserted in to table
                    if(insertvalidate==true)//if the insertvalidate is true then the each record from the select is inserted to the table 
                    for (int k = 0; k < fromTable.getTNumOfRecords(); k++) {
                        addRow(toTable.getTableName(),fromTable.getRow(k));
                        foundTable= true;
                    }
                    else
                    cout<<"couldn't validate data type";
                }
            }
        }
    }
    if(!foundTable) cout<<"couldn't find the table"<<endl;
}
/*****************************************************************************
insertselectValidate
 ****************************************************************************/
bool Engine::insertselectValidate(Table fromTable, Table toTable){//checking whether the rows from select can be inserted in to table
    bool validateinsert = false;
    bool foundTable = false;


          vector<tuple<int, string, bool, string, int > > fromcolumn;
          fromcolumn=fromTable.getColumnNames();//column names of the temporary table created due to select are retreived 

                        vector<tuple<int, string, bool, string, int > > tocolumn;
                        tocolumn=toTable.getColumnNames();//column names of the table to be inserted is retrieved 
                    for (int k = 0; k < tocolumn.size(); k++) {
                        if(get<3>(tocolumn[k])!=get<3>(fromcolumn[k])){// the data types of the columns is checked 
                        validateinsert=false;//if the alteast one data type doesnt match then the validateinsert is false
                        return validateinsert;
                        }
                    }
                   foundTable = true;
                   return true;
}


/*****************************************************************************
 SORT: sorting and showing
 ****************************************************************************/
 bool Engine::sortbyp(const SortTable &lhs,const SortTable &rhs)
 {

 return lhs.value<rhs.value;//sorting the string data type

 }
  bool Engine::sortbyi(const SortTable &lhs,const SortTable &rhs)
 {

 return lhs.valuei<rhs.valuei;//sorting the int data type

 }
 
Table Engine::sortp(string sTableNameIn,int key) {// sorting based on the coulmn index
    for (size_t t=0; t<vTableList.size(); t++) {
        if (vTableList[t].getTableName() == sTableNameIn) {// checking for the table to be sorted
            Table ob=vTableList[t];
            int rNum=ob.getTNumOfRecords();
            std::vector < SortTable> arrang;
            int counter=0;
            int rowcounter=0;
            for (int i=0; i<rNum; i++) {//puting 30 records in the main memory
                if(rowcounter<30) {
                    SortTable temp;
                    temp.getprimarykey(ob,key);
                    temp.getrow(ob,i);
                    std::vector < std::tuple<int, std::string> > row;
                    row =ob.getRow(i);
                    arrang.push_back(temp);
                    rowcounter++;
                    if(rowcounter==30||i==(rNum-1)) {//performing sorting in main memory for those 30 records
                        counter++;
                        if(!is_number(get<1>(row[key])))
                        	sort(arrang.begin(),arrang.end(),sortbyp);
                        else
                        	sort(arrang.begin(),arrang.end(),sortbyi);
                        
                        string tempsortname= "tempsort" + to_string(counter);//storing the those sorted records in temporary table
                        //cout<<tempsortname<<endl;
                        Table tempsort(tempsortname);
                        vector<tuple<int, string, bool, string, int > > vColumnNamesIn=ob.getColumnNames();
                        for (size_t kl = 0; kl < vColumnNamesIn.size(); ++kl) {

                            tempsort.addColumn(vColumnNamesIn[kl]);
                        }
                        tempsort.setTNumOfRecords(0);
                        tempsort.setTRecordSize(0);
                        tempsort.setTTotalSize(0);
                        //cout<<arrang.size();
                        for (size_t k = 0; k < arrang.size(); ++k) {
                          //  cout<<get<1>(arrang[k].vrow[0])<<endl;
                            tempsort.addRow(arrang[k].vrow);
                        }
                        vTableList.push_back(tempsort);
                        rowcounter=0;
                        arrang.clear();
                        tempsortname="";
                    }
                }
            }
            remove("tempsortf.tbl");
//merging the temporary files
            for (size_t i = 0; i < vTableList.size(); ++i) {
                if (vTableList[i].getTableName() == "tempsortf") {
                    vTableList.erase(vTableList.begin()+i);//removing the temsortf table if it already exists
                    //cout<<"hello";
                }
            }
            for (int c=1; c<=counter; ++c) {//going through all the temporary tables one by one and merging them to tempsortmerge
                //cout<<c<<endl;
                
              Table tempsortf;
              int present=0;   
                for (size_t i = 0; i < vTableList.size(); ++i) {
                    if (vTableList[i].getTableName() == "tempsortf") {
                        tempsortf=vTableList[i];
                        //cout<<"asdfasf";
                        present=1;
                    }
                }
                if(present==0){//for the first temporary table 
                            vector<tuple<int, string, bool, string, int > > vColumnNamesIn=ob.getColumnNames();
                for (size_t i = 0; i < vColumnNamesIn.size(); ++i) {
                tempsortf.addColumn(vColumnNamesIn[i]);
                }
                                tempsortf.setTNumOfRecords(0);
                tempsortf.setTRecordSize(0);
                tempsortf.setTTotalSize(0);
                }
                remove("tempsorttemp.tbl");
                Table tempsorttemp("tempsorttemp");//storing the merged results in tempsorttemp
                string tempsortmergename="tempsort"+to_string(c);//temporary sorted table
                //cout<<tempsortmergename;
                Table tempsortmerge;
                vector<tuple<int, string, bool, string, int > > vColumnNamesIn=ob.getColumnNames();
                for (size_t kl = 0; kl < vColumnNamesIn.size(); ++kl) {

                    tempsorttemp.addColumn(vColumnNamesIn[kl]);
                }
                tempsorttemp.setTNumOfRecords(0);
                tempsorttemp.setTRecordSize(0);
                tempsorttemp.setTTotalSize(0);
                int r1=0;
                int r2=0;
                for (size_t i = 0; i < vTableList.size(); ++i) {
                    if (vTableList[i].getTableName() == tempsortmergename) {
                        tempsortmerge=vTableList[i];
                        //cout<<"present"<<endl;
                    }
                }
                //cout<<tempsortf.getTNumOfRecords()<<endl;
                if( tempsortf.getTNumOfRecords()==0) {
                    while(r2 < tempsortmerge.getTNumOfRecords()) {
                        vector < std::tuple<int, std::string> > vrow2;
                        vrow2=tempsortmerge.getRow(r2);
                        tempsorttemp.addRow(vrow2);
                        //cout<<get<1>(vrow2[0])<<endl;
                        r2++;
                    }
                    //cout<<tempsorttemp.getTNumOfRecords();
                }

                else {
                    //cout<<"entered else";
                    //cout<<tempsortf.getTNumOfRecords()<<endl;
                    //cout<<tempsortmerge.getTNumOfRecords()<<endl;
                    //cout<<r1<<r2;
                    
                    while(r1 < tempsortf.getTNumOfRecords()&&r2 < tempsortmerge.getTNumOfRecords()) {
                    //cout<<r1;
                        
                            vector < std::tuple<int, std::string> > vrow1;
                            vector < std::tuple<int, std::string> > vrow2;
                            vrow1=tempsortf.getRow(r1);
                            vrow2=tempsortmerge.getRow(r2);
                            if(!is_number(get<1> (vrow1[key]))){//if the coulumn is string
                            string value1=get<1> (vrow1[key]);
                            string value2=get<1> (vrow2[key]);
                                                       if(value1.compare(value2)<0) {//comparing the two records based on the column
                                                       //if the record in the tempsortf file is less than the sorted table then that record is written to tempsorttemp
                                tempsorttemp.addRow(vrow1);
                               // cout<<value1<<endl;
                                r1++;
                            } else {
                                tempsorttemp.addRow(vrow2);
                                //cout<<value2<<endl;
                                r2++;
                            }
                            }
                            if(is_number(get<1> (vrow1[key]))){//if the column is integer
                            int value1=stoi(get<1> (vrow1[key]));
                            int value2=stoi(get<1> (vrow2[key]));
                                                       if(value1<value2) {
                                tempsorttemp.addRow(vrow1);
                                //cout<<value1<<endl;
                                r1++;
                            } else {
                                tempsorttemp.addRow(vrow2);
                                //cout<<value2<<endl;
                                r2++;
                            }
                            }
 
                            //cout<<value1.compare(value2);*/
                        
                    }
                    //cout<<endl;
                    //cout<<"add";
                    //cout<<r1<<tempsortf.getTNumOfRecords()<<endl;
                    //cout<<r2<<tempsortmerge.getTNumOfRecords()<<endl;
                    if(r1<tempsortf.getTNumOfRecords()){
                    for(int p=r1;p<tempsortf.getTNumOfRecords();p++)
                    {
                    //cout<<"enter 1";
                    vector < std::tuple<int, std::string> > vrow1;
                    vrow1=tempsortf.getRow(p);
                    tempsorttemp.addRow(vrow1);
                               // cout<<value1;
                    }
                    }
                    if(r2<tempsortmerge.getTNumOfRecords()){
                    for(int p=r2;p<tempsortmerge.getTNumOfRecords();p++)
                    {
                            vector < std::tuple<int, std::string> > vrow2;
                    vrow2=tempsortmerge.getRow(p);
                    tempsorttemp.addRow(vrow2);
                                //cout<<value1;
                                cout<<"enter 2";
                    }
                    
                    }
               }
                for (size_t i = 0; i < vTableList.size(); ++i) {
                    if (vTableList[i].getTableName() == "tempsortf") {
                        vTableList.erase(vTableList.begin()+i);
                    }
                }
                tempsorttemp.setName("tempsortf");
                      //  cout<<tempsorttemp.getTableName();
                        remove("tempsortf.tbl");
                        char oldname[]="tempsorttemp.tbl";
                        char newname[]="tempsortf.tbl";
                        rename(oldname,newname);
                        //const char* na=tempsortmergename.c_str();
                        //remove(na);
                vTableList.push_back(tempsorttemp);
                
            }
            //printing the sorted file
            for (size_t i = 0; i < vTableList.size(); ++i) {
                if (vTableList[i].getTableName() == "tempsortf") {
cout<<vTableList[i].getTNumOfRecords();
                    vTableList[i].printOutTheWholeTable();
                }
            }
            //removing the temporary sorted tables
                        for (size_t i = 0; i < vTableList.size(); ++i) {
                        for (int c=1; c<=counter; ++c) {
                        string tempsortmname="tempsort"+to_string(c);
                if (vTableList[i].getTableName() == tempsortmname) {
                      tempsortmname=tempsortmname+".tbl";
                      const char* na=tempsortmname.c_str();
                      //cout<<tempsortmname;
                        remove(na);
                        vTableList.erase(vTableList.begin()+i);
                }
                }
            }
           // remove("tempsortf.tbl");
           Table returntable;
           for (size_t i = 0; i < vTableList.size(); ++i) {
                    if (vTableList[i].getTableName() == "tempsortf") {
                        vTableList[i].setName("tempsortf"+sTableNameIn);
                        returntable=vTableList[i];
                    }
                }
                                   char oldname[]="tempsortf.tbl";
                        string newname="tempsortf"+sTableNameIn+".tbl";
                        const char* newnam=newname.c_str();
                        rename(oldname,newnam);
          return(returntable);
        }
    }
}

Table Engine::sum(Table curTable, string columnName, int colIndex,
									string groupByCol, int groupByIndex)
{
	cout << "sum function " << endl;
	// get key of the column
    Table gBTable("groupByOuterTable");
    gBTable.setTNumOfRecords(0);
    vTableList.push_back(gBTable);
    Table table;
	bool foundTable = false;
	for (size_t i = 0; i < vTableList.size(); ++i) {
        if (vTableList[i].getTableName() == curTable.getTableName()) {
            table = vTableList[i];
            foundTable = true;
            break;
        }
    }
    if (!foundTable) {
    	cout << "ERROR: could not find table " << curTable.getTableName() << " for SUM" << endl;
    	return gBTable;
    }
    
    int newSumIndex = 0;
    int newGroupByIndex = 0;
    if (colIndex < groupByIndex) {
    	newGroupByIndex = 1;
    } else if (groupByIndex < colIndex) {
    	newSumIndex = 1;
    }
    
    cout << "newGroupByIndex " << newGroupByIndex << endl;
    cout << "newSumIndex " << newSumIndex << endl;
    
    
    vector<tuple<int, string, bool,string, int>> vColumnNames = curTable.getColumnNames();
    
    // put the columns in the right order
    if (newGroupByIndex < newSumIndex) {
		for (int i = 0; i < vColumnNames.size(); i++) {
			if (groupByIndex == get<0>(vColumnNames[i])) {
				gBTable.addColumn(
					make_tuple(newGroupByIndex,
							get<1>(vColumnNames[i]),
							get<2>(vColumnNames[i]),
							get<3>(vColumnNames[i]),
							get<4>(vColumnNames[i]))
					//columnName, isPrimary, type, blockSize
				);
			}
		}
	}
	
    // check the index
	for (int i = 0; i < vColumnNames.size(); i++) {
		if (colIndex == get<0>(vColumnNames[i])) {
			gBTable.addColumn(
				make_tuple(newSumIndex, 
						get<1>(vColumnNames[i]),
						get<2>(vColumnNames[i]),
						get<3>(vColumnNames[i]),
						get<4>(vColumnNames[i]))
			);
		}
	}
    if (newGroupByIndex > newSumIndex) {
		for (int i = 0; i < vColumnNames.size(); i++) {
			if (groupByIndex == get<0>(vColumnNames[i])) {
				gBTable.addColumn(
					make_tuple(newGroupByIndex,
							get<1>(vColumnNames[i]),
							get<2>(vColumnNames[i]),
							get<3>(vColumnNames[i]),
							get<4>(vColumnNames[i]))
					//columnName, isPrimary, type, blockSize
				);
			}
		}
	}

	if (colIndex == -1) {
		cout << "ERROR: could not find " << columnName << endl;
		return gBTable;
	}
    
    int sum = 0;
    string oldValue = "";
    for (int j = 0; j < curTable.getTNumOfRecords(); j++) {
    	vector < std::tuple<int, std::string> > curRow = curTable.getRow(j);
    	
    	// find group by value first
    	for (size_t i = 0; i < curRow.size(); i++) {
			int index = get<0>(curRow[i]);
			if (groupByIndex == index) {
		    	string curValue = get<1>(curRow[i]);
		    	if (oldValue.compare(curValue) != 0) {
		    		if (!oldValue.empty()) {
			    		//cout << "oldValue !empty" << endl;
			            vector<tuple<int, string> > row;
						// loop over all rows
						cout << "sum tostring" << to_string(sum) << endl;
						if (newSumIndex < newGroupByIndex) {
							row.push_back(make_tuple(newSumIndex,to_string(sum)));
							row.push_back(make_tuple(newGroupByIndex, oldValue));
						} else {
							row.push_back(make_tuple(newGroupByIndex, oldValue));
							row.push_back(make_tuple(newSumIndex,to_string(sum)));
						}
						cout << "pushed row" << endl;
						gBTable.addRow(row);
						cout << "added row" << endl;
		    			//cout << "sum of rows1 " << oldValue << ":" << sum << endl;
		    		}
		    		oldValue = curValue;
		    		sum = 0;
		    	}
		    	break;
			}
		}
    	
    	// now find sum value
		for (size_t i = 0; i < curRow.size(); i++) {
			int index = get<0>(curRow[i]);
			if (colIndex == index) {
		    	cout << "testing value " << endl;
		    	string actualValue = get<1>(curRow[i]);
		    	//cout << "actual value " << actualValue  << endl;
		    	sum += stoi(actualValue);
		    	
		    	break;
			}
		    
			//vColumnNamesIn[i]);
		}
    }
    
	vector<std::tuple<int, std::string> > rowEnd;
	//cout << "sum to string " << to_string(sum) << endl;
	if (newSumIndex < newGroupByIndex) {
		rowEnd.push_back(make_tuple(newSumIndex, to_string(sum)));
		rowEnd.push_back(make_tuple(newGroupByIndex, oldValue));
	} else {
		rowEnd.push_back(make_tuple(newGroupByIndex, oldValue));
		rowEnd.push_back(make_tuple(newSumIndex, to_string(sum)));
	}
	
	//cout << "pushed row2" << endl;
	gBTable.addRow(rowEnd);
	//cout << "sum of rows2 " << oldValue << ":" << sum << endl;
    
    gBTable.printOutTheWholeTable();
    
    return gBTable;
}

bool Engine::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

 
 
 /*****************************************************************************
 READ
 ****************************************************************************/
void Engine::read(){
    
    ifstream infile;
    //int present=0;
    infile.open("catalog.txt",ios::in);
    
    Table ob;
    string line;
    int count=0;
    while(getline(infile,line)){
        size_t f;
        if((f=line.find("tablename"))!=string::npos) //reads the table name
        {
            //cout<<line;
            //cout<<"gr";
            count=1;
            size_t f1;
            if((f1=line.find("=",f+8))!=string::npos){
                //	cout<<f1;
                string tname=line.substr(f1+1,string::npos);
                ob=Table(tname);
               // cout<<tname;
            }
        }
        else if(count==1)//reads the columns
        {
            
            count=2;
            size_t f1;
            size_t f2;
            if((f1=line.find("="))!=string::npos){
                //cout<<f1;
                int seq=0;
                string coln=line.substr(f1+1,string::npos);
                size_t f6;
                size_t f5;
                f2=line.find(",",f1+1);
                //vector<tuple<string,string,int,bool>> colname;
                string coltemp;
                
                size_t f3;
                f3=line.find(":");
                f5=line.find("(");                
                f6=line.find(")");
                coltemp=line.substr(f1+1,f2-f1-1);
               // cout<<line.substr(f5+1,f6-f5-1);
                //int c2=stoi(line.substr(f5+1,f6-f5-1));
                int comparision=0;
                 comparision=f5-f2;
                if(((f2==string::npos)&&(f5!=string::npos))||(comparision<0&&f5!=string::npos)){
                int c2=stoi(line.substr(f5+1,f6-f5-1));
                c2=c2+6;
                ob.addColumn(make_tuple(seq,line.substr(f1+1,f3-f1-1),false,"string",c2));
                }
                else
                ob.addColumn(make_tuple(seq,line.substr(f1+1,f3-f1-1),false,"int",4));
                while(f2!=string::npos)
                {
                    string coln=line.substr(f2+1,string::npos);
                    size_t f4;
                    f4=line.find(",",f2+1);
                    string coltemp;
                    
                    coltemp=line.substr(f2+1,f4-f2-1);
                    f3=line.find(":",f2+1);
                    f5=line.find("(",f2+1);
                    f6=line.find(")",f2+1);
                    //int c1=stoi(line.substr(f5+1,f6-f5-1));
                   // cout<<line.substr(f2+1,f3-f2-1);
                    seq=seq+1;
                    comparision=0;
                    comparision=f5-f4;

                    if(((f4==string::npos)&&(f5!=string::npos))||(comparision<0&&f5!=string::npos)){
                    int c1=stoi(line.substr(f5+1,f6-f5-1));
                    c1=c1+6;
                    ob.addColumn(make_tuple(seq,line.substr(f2+1,f3-f2-1),false,"string",c1));
                    }
                    else
                    ob.addColumn(make_tuple(seq,line.substr(f2+1,f3-f2-1),false,"int",4));
                    f2=f4;
                    if(f2==line.size()-1)
                    {
                       // cout<<"hei";
                        break;
                    }
                }
                
            }
        }
        
        else if(count==2){//reads primary key columns
            //cout<<line;
            count=3;
            size_t f1;
            size_t f2;
            if((f1=line.find("="))!=string::npos){
                
                string coln=line.substr(f1+1,string::npos);
                
                
                f2=line.find(",",f1+1);
                //vector<string> primkey;
                string coltemp;
                
                coltemp=line.substr(f1+1,f2-f1-1);
                
               // cout<<coltemp<<"\n";
                // primkey.push_back(coltemp);
                ob.setPrimaryKey(coltemp);
                while(f2!=string::npos)
                { //cout<<"prime";
                    string coln=line.substr(f2+1,string::npos);
                    size_t f4;
                    f4=line.find(",",f2+1);
                    string coltemp;
                    
                    coltemp=line.substr(f2+1,f4-f2-1);
                    //cout<<coltemp;
                    ob.setPrimaryKey(coltemp);
                    f2=f4;
                    if(f2==line.size()-1)
                    {
                        //cout<<"hei";
                        break;
                    }
                }
                
            }
        }
        else if(count==3){//reads record size
            //cout<<"Asdfas";
            //cout<<line;
            count=4;
            size_t f1;
            size_t f2;
            if((f1=line.find("="))!=string::npos){
                
                string coln=line.substr(f1+1,string::npos);
                
                f2=line.find(",",f1+1);
                int recordsize;
                
                
                recordsize=stoi(line.substr(f1+1,f2-f1-1));
                ob.setTRecordSize(recordsize);
                //cout<<recordsize<<"\n";
            }
        }
        else if(count==4){//reads total size of records
            
            //cout<<line;
            count=5;
            size_t f1;
            size_t f2;
            if((f1=line.find("="))!=string::npos){
                
                string coln=line.substr(f1+1,string::npos);
                f2=line.find(",",f1+1);
                int totalsize;
                
                
                totalsize=stoi(line.substr(f1+1,f2-f1-1));
                ob.setTTotalSize(totalsize);
                //cout<<totalsize<<"\n";
            }
            
        }
        else if(count==5){//reads number of records
            
            //cout<<line;
            count=0;
            size_t f1;
            size_t f2;
            if((f1=line.find("="))!=string::npos){
                
                string coln=line.substr(f1+1,string::npos);
                f2=line.find(",",f1+1);
                int records;
                
                
                records=stoi(line.substr(f1+1,f2-f1-1));
                ob.setTNumOfRecords(records);
               // cout<<records<<"\n";
            }
            vTableList.push_back(ob);
            ob=Table();
        }
        
        
        
        line.clear();
        
        
    }
    
    infile.close();
}


void Engine::writetofile()
{
    remove("catalog.txt");
    ofstream outfile;
    outfile.open("catalog.txt",ios::out|ios::app);
    for(size_t i=0; i<vTableList.size();++i){
        //string name=cataloglist[i].getTableName();
        outfile<<"tablename="<<vTableList[i].getTableName()<<'\n';//writes the table name
        //cout<<"table";
        vector<tuple<int, string, bool, string, int > > col;
        col=vTableList[i].getColumnNames();
        outfile<<"column=";
        for(size_t j=0;j< col.size();++j){
            if(j<col.size()-1){
            if(get<3>(col[j])=="string"){
            int c=get<4>(col[j])-6;
            outfile<<get<1>(col[j])<<":"<<"CHAR"<<"("<<c<<")"<<",";//writes the columnnames
        
            }
            else
                outfile<<get<1>(col[j])<<":"<<"INT"<<",";
                }
            else{
            if(get<3>(col[j])=="string"){
            int c=get<4>(col[j])-6;
            outfile<<get<1>(col[j])<<":"<<"CHAR"<<"("<<c<<")";
        
            }
            else
                outfile<<get<1>(col[j])<<":"<<"INT";
                }
        }
        vector<string> primarykey;
        primarykey=vTableList[i].getPrimaryKey();
        outfile<<"\n"<<"primarykey=";
        for(size_t k=0;k<primarykey.size();++k){
            if(k<primarykey.size()-1)
                outfile<<primarykey[k]<<",";//writes the primary key columns
            else
                outfile<<primarykey[k];
        }
        int recordsize;
        vTableList[i].calculateRecordSize();
        recordsize=vTableList[i].getTRecordSize();
        outfile<<"\n"<<"recordsize="<<recordsize;//write the record size
        int totalsize;
        vTableList[i].calculateTotalRecordSize();
        totalsize=vTableList[i].getTTotalSize();
        outfile<<"\n"<<"totalsize="<<totalsize;//write the total size;
        int nrecords;
        nrecords=vTableList[i].getTNumOfRecords();//write the total number of records
        outfile<<"\n"<<"records="<<nrecords<<"\n";
    }
    
    outfile.close();
}


bool Engine::createValidate(string sLineIn,string sTableNameIn)//validating the coulmns data type while inserting
{
    vector < string > vReturn;
    int iPosStart = 0;
    int iPosEnd = 0;
    int iCount = 0;
    int iAmountOfCommas = 0;
    Table ob;
    
    for (size_t i=0; i<vTableList.size();i++){
        if(vTableList[i].getTableName()==sTableNameIn){
            
            ob=vTableList[i] ;
        }
    }
       
    //Check to see how many commas are in the string
    for (size_t i = 0; i < sLineIn.length(); ++i)
    {
        //Execute if the comma is found and increment the counter
        if (sLineIn[i] == ',')
        {
            iAmountOfCommas++;
        }
    }
    
    
    vector<tuple<int, string, bool, string, int > > vColumnNames=ob.getColumnNames();
    if(iAmountOfCommas>=vColumnNames.size()){
        return false;
    }
    //Loop to parser out the comma separated values
    while (iCount <= iAmountOfCommas)
    {
        iPosEnd = sLineIn.find(",", iPosStart + 1);
        string value = sLineIn.substr(iPosStart, iPosEnd - iPosStart);
        
        if ((value.find("\'") != string::npos)&&
            (std::get < 3 > (vColumnNames[iCount])=="string"))
        {
            
            value = Utilities::cleanSpaces(value);
        }
        else if((value.find("\'") == string::npos)&&
                (std::get < 3 > (vColumnNames[iCount])=="int") )
        {
            
        } else {
            cout<<"ERROR: column data does not match column type" << endl;
            return false;
        }
        
        //cout << "value " << value << endl;
        vReturn.push_back(value);
        iPosStart = iPosEnd + 1;
        iCount++;
    }
    
    //clean up the words that were separated out
    //    for (size_t i = 0; i < vReturn.size(); ++i)
    //    {
    //        vReturn[i] = Utilities::cleanSpaces(vReturn[i]);
    //        //cout<<"vReturn: "<<vReturn[i]<<endl;
    //    }
    
    return true;
}
