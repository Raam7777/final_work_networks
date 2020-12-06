#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>

#include "functions.hpp"

//https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c

int main(){
string line;
ifstream file ("sample_input.txt");
if (file.is_open()) {
    while ( getline (file,line) ) {
        cout << line << endl;
        istringstream stream (line);
        string action, prefix, result;
        stream >> action; stream >> prefix; stream >> result;
        if (action == "ADD"){
            ADD(prefix, result);
        }
        else if (action == "FIND"){
            FIND(prefix);
        }
        else if (action == "REMOVE"){
            REMOVE(prefix, result);
        }
        else cout << "ERROR! , Can't perform the function" << endl;
    }
    file.close();
}
else cout << "File not opened" << endl;
}