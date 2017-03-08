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
        }


    }
    return 0;

}