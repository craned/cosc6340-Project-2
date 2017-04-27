/*******************************************************************************
 File: Engine.cpp
 Author: Amirreza Shirani
 Author: Devin Crane
 Author: sakhitha kanyadhara
 *******************************************************************************/
#include <fstream>
#include "Parser.h"
#include <cstdio>

using namespace std;

//string sqlQuery = "";
string sqlQuery = "CREATE TABLE T ( C1 INT, C2 CHAR(20), C3 INT, PRIMARY KEY(C1));";
//string sqlQuery = "INSERT INTO T VALUES(1,'string',5);";
string scriptFile = "";
//string scriptFile = "file";

const string OUTPUT_FILE = "output.txt";

//ofstream out;

string const CREATE_TABLE = "CREATE TABLE ";
string const INSERT_INTO = "INSERT INTO ";
string const SELECT = "SELECT ";
string const SHOW_TABLE = "SHOW TABLE";
string const QUIT = "QUIT;";

//const int CREATE_TABLE_SIZE = 12;
//const int INSERT_INTO_SIZE = 11;
//const int WRITE_CLOSE_SIZE = 5;
//const int DELETE_FROM_SIZE = 11;
//const int UPDATE_SIZE = 5;
//const int WHERE_SIZE = 5;
//const int SET_SIZE = 3;
//const int OPEN_EXIT_SHOW_SIZE = 10;
//const int SINGLE_OP_SIZE = 1;
//const int DOUBLE_OP_SIZE = 2;
//const int VALUES_FROM_SIZE = 11;
//const int VAL_FROM_REL_SIZE = 20;
//const int PRIMARY_KEY_SIZE = 11;

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
    for (size_t i = 0; i < str.length(); i++) {
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
	cout << endl;
    cout << scriptFile << endl;

    ifstream script(scriptFile);
    //script.open
    string line = "";
    string queries = "";
    if (script.is_open()) {
        bool blockCommentActive = false;
        //cout << "open" << endl;
        while (getline(script, line)) {
        	//out << line;
            size_t blockCommentStartPos = line.find("/*");
            size_t blockCommentEndPos = line.find("*/");
            size_t dashDashPos = line.find("--");
            
            if (blockCommentStartPos != string::npos && !blockCommentActive) {
                blockCommentActive = true;
                if (blockCommentEndPos != string::npos) {
                    blockCommentActive = false;
                    line = line.substr(0, blockCommentStartPos) +
                    		line.substr(blockCommentEndPos+2, string::npos);
                } else {
                	line = line.substr(0, blockCommentStartPos);
                }
            }
            if (blockCommentActive && blockCommentEndPos != string::npos) {
                blockCommentActive = false;
                line = line.substr(blockCommentEndPos+2, string::npos);
            }
            
            if (dashDashPos != string::npos && dashDashPos < blockCommentStartPos &&
                (blockCommentEndPos != string::npos && dashDashPos > blockCommentEndPos))
            {
                dashDashPos = line.find("--");
                line = line.substr(0, dashDashPos);
            }
            if (blockCommentActive) {
                continue;
            }
            for (int i = 0; i < line.length(); i++) {
                if ((i+1) < line.length()) {
                    if (line.at(i) == '-' && line.at(i+1) == '-') {
                        line = line.substr(0, i);
                        break;
                    }
                }
            }
            if (line.find("\r") != string::npos) {
                line = line.substr(0, line.find('\r'));
            }
            if (line.find("\n") != string::npos) {
                line = line.substr(0, line.find('\n'));
            }
            cout << line << endl;
            queries += " " + toUpper(line);
            size_t firstSemicolon = queries.find(';', 0);
            if (firstSemicolon != string::npos) {
                firstSemicolon++;
                string query = queries.substr(0, firstSemicolon);
                cout << "executing " << query << endl;
                parser->parse(query);
                queries = queries.substr(firstSemicolon,
                						queries.length() - firstSemicolon);
             }//*/
        }
        
        while (queries.length() > 0) {
        	//out << line;
            size_t firstSemicolon = queries.find(";", 0);
            if (firstSemicolon != string::npos) {
                firstSemicolon++;
                string query = queries.substr(0, firstSemicolon);
                parser->parse(query);
                queries = queries.substr(firstSemicolon,
                						queries.length() - firstSemicolon);
                
                if (queries.find(';') == string::npos) {
                    cout << "ERROR: " << queries << " not executed. No semicolon could be found." << endl;
                    break;
                }
            } else {
                bool allSpaces = true;
                for (int i = 0; i < queries.length(); i++) {
                    if (queries[i] != ' ') {
                        cout << "ERROR: " << queries << " not executed. No semicolon could be found." << endl;
                        allSpaces = false;
                    }
                }
                
                if (allSpaces) {
                    break;
                } else {
                	cout << "ERROR: " << queries << " not executed. No semicolon could be found." << endl;
                	break;
                }
             }
         }//*/

        cout << "Finished reading sql script" << endl;
    } else {
        cout << "ERROR: could not open " << scriptFile << ". Was it named correctly?" << endl;
    }
}

void commandLineSQLInput(string sqlQuery) {
    //cout << sqlQuery << endl;
    while (true) {
        sqlQuery += toUpper(sqlQuery);
        // for production - don't -think- this is needed anymore
//        SQL = "";
//        cout << "SQL > ";
//        getline(cin, SQL);
//        SQL = toupper(SQL);

		//out << sqlQuery;
		size_t firstSemicolon = sqlQuery.find(";");
		if (sqlQuery.find(";") != string::npos) {
		    if (parser->parse(sqlQuery) == 0) {
		        return;
		    }
		    
		    firstSemicolon++;
            sqlQuery = sqlQuery.substr(0, firstSemicolon);
		    sqlQuery = "";
		    cout << "SQL > ";
		}

        // for testing
        getline(cin, sqlQuery);
    }
}

int main(int argc, char *argv[]) {
    //out.open("out2.txt", ios::out);
    //ofstream cout(OUTPUT_FILE);
    //std::cout.rdbuf(cout.rdbuf());
    std::ofstream out("output.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf());

parser = new Parser();
parser->read();
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
    
    out.open(OUTPUT_FILE, ios::out);
    
    cout.rdbuf(out.rdbuf());

   // parser = new Parser();

    string firstArg = argv[1];
    //cout << firstArg << endl;
    if (firstArg.find("script") != string::npos) {
        char* scriptFile = strtok((char*)firstArg.c_str(), "=");
        scriptFile = strtok(NULL, "="); // Advance to actual script file name
        if (scriptFile == NULL) {
        	//out << "ERROR: no sql script could be found";
            cout << "ERROR: no sql script could be found" << endl;
            return 0;
        }

        //cout << scriptFile << endl;
        parseScriptFile(scriptFile);
    } else {
        commandLineSQLInput(firstArg);
    }
    

    std::cout.rdbuf(coutbuf);
       out.close();
    return 0;
}

