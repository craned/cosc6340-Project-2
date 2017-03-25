#include <fstream>
#include "Parser.h"

using namespace std;

//string sqlQuery = "";
string sqlQuery = "CREATE TABLE T ( C1 INT, C2 CHAR(20), C3 INT, PRIMARY KEY(C1));";
//string sqlQuery = "INSERT INTO T VALUES(1,'string',5);";
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
    bool toUpper = true;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\'') {
            toUpper = false;
        } else {
            if (toUpper) {
                str[i] = toupper(str[i]);
            } else {
                str[i] = str[i];
                if (str[i] == '\'') {
                    toUpper = true;
                }
            }
        }
    }
    return str;
}

void parseScriptFile(string scriptFile) {
    cout << scriptFile << endl;

    ifstream script(scriptFile);
    //script.open
    string line = "";
    string queries = "";
    if (script.is_open()) {
        //cout << "open" << endl;
        while (getline(script, line)) {
            queries += toUpper(line);
            cout << queries << endl;
            size_t firstSemicolon = queries.find(";") + 1;
            if (firstSemicolon != string::npos) {
                string query = queries.substr(0, firstSemicolon);
                parser->parse(query);
                queries = queries.substr(firstSemicolon, queries.length() - firstSemicolon);
            }
        }

        /*while (true) {
            size_t firstSemicolon = queries.find_first_of(";");
            if (firstSemicolon == string::npos || queries.length() == 0) {
                cout << "End of queries that end in a semicolon" << endl;
                break;
            } else {
                string query = queries.substr(0, firstSemicolon);
                parser->parse(query);
                queries = queries.substr(firstSemicolon, queries.length() - firstSemicolon);
            }
        }*/

        cout << "Finished reading sql script" << endl;
    } else {
        cout << "ERROR: could not open " << scriptFile << ". Was it named correctly?" << endl;
    }
}

void commandLineSQLInput(string sqlQuery) {
    //cout << sqlQuery << endl;
    while (true) {
        sqlQuery = toUpper(sqlQuery);
        // for production - don't -think- this is needed anymore
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
        }
        return 0;
    }

    parser = new Parser();

    string firstArg = argv[1];
    //cout << firstArg << endl;
    if (firstArg.find("script") != string::npos) {
        char* scriptFile = strtok((char*)firstArg.c_str(), "=");
        scriptFile = strtok(NULL, "="); // Advance to actual script file name
        if (scriptFile == NULL) {
            cout << "ERROR: no sql script could be found" << endl;
            return 0;
        }

        //cout << scriptFile << endl;
        parseScriptFile(scriptFile);
    } else {
        commandLineSQLInput(firstArg);
    }

    return 0;
}

