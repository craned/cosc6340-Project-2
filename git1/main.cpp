#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <tuple>
#include "Parser.h"
using namespace std;


int main() {
        Parser pCommandLineTest;
        string sLineIn;
        string sAgain = "1";

        //Test the parser reading from command line input
        while (sAgain == "1") {
            printf("Enter line for parser: ");
            getline(cin, sLineIn);
            if (sLineIn == "exit") {
                sAgain = "0";
            } else {
                pCommandLineTest.parse(sLineIn);
                //cout << "parse" << endl;
            }
            //printf("Enter another line? 1 or 0: ");
            //getline(cin, sAgain);
        }

        return 0;
    }
