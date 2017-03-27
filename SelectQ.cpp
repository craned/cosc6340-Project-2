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
	orderBy = orderBy;
}
string SelectQ::getOrderBy()
{
	return orderBy;
}

void SelectQ::setGroupBy(string groupBy)
{
	groupBy = groupBy;
}
string SelectQ::getGroupBy()
{
	return groupBy;
}

