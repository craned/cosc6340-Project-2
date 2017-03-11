<<<<<<< HEAD
#include <iostream>
#include <stdio.h>
//changes from reza
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Parser.h"
using namespace std;





int main(int argc, char *argv[]) {
    cout<<"hello world"<<endl;
    Parser pCommandLineTest;
    string sLineIn;
    string sAgain = "1";
    //string quit="";
//Test the parser reading from command line input
    while (sAgain == "1") {
        printf("Enter line for parser: ");
        getline(cin, sLineIn);
        if (sLineIn=="exit"){
            sAgain="0";
        }else{
            pCommandLineTest.parse(sLineIn);
=======
#include "Parser.h"

using namespace std;

//string sqlQuery = "";
//string sqlQuery = "CREATE TABLE T (C1 INT, C2 VARCHAR(5), C3 INT, PRIMARY KEY(C1));";
string sqlQuery = "INSERT INTO T VALUES(1,'string',5);";
string scriptFile = "";
//string scriptFile = "file";

string const CREATE_TABLE = "CREATE TABLE ";
string const INSERT_INTO = "INSERT INTO ";
string const SELECT = "SELECT ";
string const SHOW_TABLE = "SHOW TABLE";
string const QUIT = "QUIT;";

const int CREATE_TABLE_SIZE = 12;
const int INSERT_INTO_SIZE = 11;
const int WRITE_CLOSE_SIZE = 5;
const int DELETE_FROM_SIZE = 11;
const int UPDATE_SIZE = 5;
const int WHERE_SIZE = 5;
const int SET_SIZE = 3;
const int OPEN_EXIT_SHOW_SIZE = 10;
const int SINGLE_OP_SIZE = 1;
const int DOUBLE_OP_SIZE = 2;
const int VALUES_FROM_SIZE = 11;
const int VAL_FROM_REL_SIZE = 20;
const int PRIMARY_KEY_SIZE = 11;

Parser* parser;

void parseSQLQuery(string SQL) {
    if (SQL.find_first_of("C") == 0) {
        cout << "create" << endl;
        if (SQL.find_first_of(CREATE_TABLE) == 0) {

        }
    } else if (SQL.find_first_of("I") == 0) {
        cout << "insert" << endl;
    } else if (SQL.find_first_of("S") == 0) {
        cout << "select" << endl;
    }
}

string toUpper(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

void parseScriptFile(string scriptFile) {
	scriptFile = toUpper(scriptFile);
    cout << scriptFile << endl;
}

void commandLineSQLInput(string sqlQuery) {
    //cout << sqlQuery << endl;
    while (true) {
    	sqlQuery = toUpper(sqlQuery);
        // for production
//        SQL = "";
//        cout << "SQL > ";
//        getline(cin, SQL);
//        SQL = toupper(SQL);

        if (parser->parse(sqlQuery) == 0) {
        	return;
        }

        // for testing
        sqlQuery = "";
        cout << "SQL > ";
        getline(cin, sqlQuery);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "usage: dbms script=<filename> OR dbms \"<SQL query>\"" << endl;
        if (!sqlQuery.empty()) {
            cout << "Running on internal sql query" << endl;
            commandLineSQLInput(sqlQuery);
        } else if (!scriptFile.empty()) {
            cout << "Running on internal sql script" << endl;
            parseScriptFile(scriptFile);
>>>>>>> master
        }

<<<<<<< HEAD
=======
    parser = new Parser();

    string firstArg = argv[1];
	//cout << firstArg << endl;
    if (firstArg.find("script") != string::npos) {
        char* scriptFile = strtok((char*)firstArg.c_str(), "=");
//        cout << scriptFile << endl;
        parseScriptFile(scriptFile);
    } else {
        commandLineSQLInput(firstArg);
    }
>>>>>>> master

    }
    return 0;
<<<<<<< HEAD

}
=======
}

>>>>>>> master
