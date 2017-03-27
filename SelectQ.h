
#ifndef SELECTQ_H
#define SELECTQ_H

#include <string>
#include <cstdlib>
#include <iomanip>
#include <string.h>

using namespace std;

class SelectQ {
	private:
	    //Declare private variables
	    string selectCols = "";
	    string fromTable = "";
	    string tempTable = "";
	    string joinTable = "";
	    string joinFilter = "";
	    string whereFilter = "";
	    string orderBy = "";
	    string groupBy = "";

	public:

	    //Declare class methods
	    SelectQ() {};
	    
	    void clearAll();
	    
	    void setSelectCols(string cols);
	    string getSelectCols();
	    
	    void setFromTable(string table);
	    string getFromTable();
	    
	    void setTempTable(string table);
	    string getTempTable();
	    
	    void setJoinTable(string table);
	    string getJoinTable();
	    
	    void setJoinFilter(string filter);
	    string getJoinFilter();
	    
	    void setWhereFilter(string filter);
	    string getWhereFilter();
	    
	    void setOrderBy(string orderBy);
	    string getOrderBy();
	    
	    void setGroupBy(string groupBy);
	    string getGroupBy();
	        
};

#endif

