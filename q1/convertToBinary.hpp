#include <string>
#include <bits/stdc++.h>

//https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting

using namespace std;

string toBinary(int n) { 
    string s = bitset<64> (n).to_string();  
    auto one = s.find('1'); 
    if(one != string::npos) return s.substr(one); 
    return "0"; 
}