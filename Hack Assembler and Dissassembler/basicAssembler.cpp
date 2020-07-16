#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <cstdio>
#include <vector>
#include <iterator>
#include <cctype>
#include <cmath>
#include <bitset>

using namespace std;

int main() {

    
    //create empty dest table
    map<string, string> destTable;
    //populate dest table
    destTable.insert(pair<string, string>("null", "000"));
    destTable.insert(pair<string, string>("M", "001"));
    destTable.insert(pair<string, string>("D", "010"));
    destTable.insert(pair<string, string>("MD", "011"));
    destTable.insert(pair<string, string>("A", "100"));
    destTable.insert(pair<string, string>("AM", "101"));
    destTable.insert(pair<string, string>("AD", "110"));
    destTable.insert(pair<string, string>("AMD", "111"));
    
    //create empty comp table
    map<string, string> compTable;
    //populate comp table with correct a values
    compTable.insert(pair<string, string>("0", "0101010"));
    compTable.insert(pair<string, string>("1", "0111111"));
    compTable.insert(pair<string, string>("-1", "0111010"));
    compTable.insert(pair<string, string>("D", "0001100"));
    compTable.insert(pair<string, string>("A", "0110000"));
    compTable.insert(pair<string, string>("!D", "0001101"));
    compTable.insert(pair<string, string>("!A", "0110001"));
    compTable.insert(pair<string, string>("-D", "0001111"));
    compTable.insert(pair<string, string>("-A", "0110011"));
    compTable.insert(pair<string, string>("D+1", "0011111"));
    compTable.insert(pair<string, string>("A+1", "0110111"));
    compTable.insert(pair<string, string>("D-1", "0001110"));
    compTable.insert(pair<string, string>("A-1", "0110010"));
    compTable.insert(pair<string, string>("D+A", "0000010"));
    compTable.insert(pair<string, string>("D-A", "0010011"));
    compTable.insert(pair<string, string>("A-D", "0000111"));
    compTable.insert(pair<string, string>("D&A", "0000000"));
    compTable.insert(pair<string, string>("D|A", "0010101"));
    compTable.insert(pair<string, string>("M", "1110000"));
    compTable.insert(pair<string, string>("!M", "1110001"));
    compTable.insert(pair<string, string>("-M", "1110011"));
    compTable.insert(pair<string, string>("M+1", "1110111"));
    compTable.insert(pair<string, string>("M-1", "1110010"));
    compTable.insert(pair<string, string>("D+M", "1000010"));
    compTable.insert(pair<string, string>("D-M", "1010011"));
    compTable.insert(pair<string, string>("M-D", "1000111"));
    compTable.insert(pair<string, string>("D&M", "1000000"));
    compTable.insert(pair<string, string>("D|M", "1010101"));
    
    //create empty jump table
    map<string, string> jumpTable;
    //populate jump table
    jumpTable.insert(pair<string, string>("null", "000"));
    jumpTable.insert(pair<string, string>("JGT", "001"));
    jumpTable.insert(pair<string, string>("JEQ", "010"));
    jumpTable.insert(pair<string, string>("JGE", "011"));
    jumpTable.insert(pair<string, string>("JLT", "100"));
    jumpTable.insert(pair<string, string>("JNE", "101"));
    jumpTable.insert(pair<string, string>("JLE", "110"));
    jumpTable.insert(pair<string, string>("JMP", "111"));
    
    string line;  
    string input; 
    while (getline(cin, line)) { //keep reading cin and store in line 
        if (!line.empty() && line[0] != '/'  && line[0] != '(') { //skip empty lines, comments, identations
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); //remove all spaces 
            line.erase(remove(line.begin(), line.end(), '\t'), line.end()); //remove all tabs  
            if (line.find('/') > 0) {
               line = line.substr(0, line.find("/", 0)); //remove in-line comments
            }
            input += line + '\n'; 
        }
    }
    stringstream ss(input);
    string validLine;
    string aInstruction;
    while (!ss.eof()) {
        ss >> validLine;
        if (!validLine.empty() ) {
        if (validLine[0] == '@') {  //if it is an A-instruction
            validLine.erase(0,1); //remove @symbol
                int value = stoi(validLine); //convert value to integer
                aInstruction = bitset<16> (value).to_string(); //find binary equivalent
                if (value < -32768 || value > 32767) { 
                    aInstruction = bitset<16> (32).to_string();
            }
            cout << aInstruction << endl;
            validLine.clear();
        }
        else { //C-instruction
            string jump = "000"; //optional
            string comp;
            string dest = "000"; //optional
            cout <<"111";
            if (validLine.find('=') != string::npos) { //dest = comp or dest = comp;jump
                comp = validLine.substr(validLine.find("=", 0)+1, validLine.find(";", 0)-2);
                    map<string, string>::iterator pos;
                    pos = compTable.find(comp);
                    comp = pos->second;
                    cout << comp;
                dest = validLine.substr(0, validLine.find("=", 0));
                    pos = destTable.find(dest);
                    dest = pos->second;
                    cout << dest;
                if (validLine.find(';') != string::npos) { //dest = comp; jump
                    jump = validLine.substr(validLine.find(";", 0)+1, validLine.length()-1);
                    map<string, string>::iterator pos;
                    pos = jumpTable.find(jump);
                    jump = pos->second;
                }
                cout << jump;
            }
            else { //comp;jump
                comp = validLine.substr(0, validLine.find(";", 0));
                    map<string, string>::iterator pos;
                    pos = compTable.find(comp);
                    comp = pos->second;
                    cout << comp;
                cout << dest;
                if (validLine.find(';') != string::npos) {
                    jump = validLine.substr(validLine.find(";", 0)+1, validLine.length()-1);
                    map<string, string>::iterator pos;
                    pos = jumpTable.find(jump);
                    jump = pos->second;
                    cout << jump;
                }   
            }
          cout << endl;
          validLine.clear();  
        } 
      }
    }
    return 0;
}
