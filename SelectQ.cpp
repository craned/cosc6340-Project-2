/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/
#include "SelectQ.h"

/*
	This class contains all select query parts. They are empty if Not Applicable.
*/

void SelectQ::clearAll()
{
	setSelectCols("");
	setFromTable("");
	setTempTable("");
	setJoinTable("");
	setJoinFilter("");
	setWhereFilter("");
	setOrderBy("");
	setGroupBy("");
}

void SelectQ::printAll()
{
	cout << "printing all" << endl;
	cout << "select cols " << getSelectCols() << endl;
	cout << "from table " << getFromTable() << endl;
	cout << "temp table " << getTempTable() << endl;
	cout << "join table " << getJoinTable() << endl;
	cout << "join filter " << getJoinFilter() << endl;
	cout << "where filter " << getWhereFilter() << endl;
	cout << "order by " << getOrderBy() << endl;
	cout << "group by " << getGroupBy() << endl;//*/
}
	   
void SelectQ::setSelectCols(string cols)
{
	selectCols = cols;
}
string SelectQ::getSelectCols()
{
	return selectCols;
}

void SelectQ::setFromTable(string table)
{
	fromTable = table;
}
string SelectQ::getFromTable()
{
	return fromTable;
}

void SelectQ::setTempTable(string table)
{
	tempTable = table;
}
string SelectQ::getTempTable()
{
	return tempTable;
}

void SelectQ::setJoinTable(string table)
{
	joinTable = table;
}
string SelectQ::getJoinTable()
{
	return joinTable;
}

void SelectQ::setJoinFilter(string filter)
{
	joinFilter = filter;
}
string SelectQ::getJoinFilter()
{
	return joinFilter;
}

void SelectQ::setWhereFilter(string filter)
{
	whereFilter = filter;
}
string SelectQ::getWhereFilter()
{
	return whereFilter;
}

void SelectQ::setOrderBy(string orderBy)
{
	this->orderBy = orderBy;
}
string SelectQ::getOrderBy()
{
	return orderBy;
}

void SelectQ::setGroupBy(string groupBy)
{
	this->groupBy = groupBy;
}
string SelectQ::getGroupBy()
{
	return groupBy;
}

