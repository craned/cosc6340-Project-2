/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/
#include "Utilities.h"

/************************************************************
Remove any additional spaces from the string
******************************************************************/
string Utilities::cleanSpaces(string sLineIn)
{
  string sOut = "";
  for (size_t i = 0; i < sLineIn.length(); ++i)
  {
	//Append the value from the string into the return string, if its alpha
	if (isalnum(sLineIn[i]) || sLineIn[i] == '_' || sLineIn[i] == '/' ||
		sLineIn[i] == '*' || sLineIn[i] == '=' || sLineIn[i] == '.' ||
		sLineIn[i] == ',')
	{
	  sOut += sLineIn[i];
	}
  }

  return sOut;
}

