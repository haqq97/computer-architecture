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
   
    

    //create empty symbol table 
    map<string, int> symbolTable; 
  
    //populate symbol table with in-built symbols
    symbolTable.insert(pair<string, int>("R0", 0));
    symbolTable.insert(pair<string, int>("SP", 0));
    symbolTable.insert(pair<string, int>("R1", 1)); 
    symbolTable.insert(pair<string, int>("LCL", 1)); 
    symbolTable.insert(pair<string, int>("R2", 2)); 
    symbolTable.insert(pair<string, int>("ARG", 2)); 
    symbolTable.insert(pair<string, int>("R3", 3)); 
    symbolTable.insert(pair<string, int>("THIS", 3)); 
    symbolTable.insert(pair<string, int>("R4", 4)); 
    symbolTable.insert(pair<string, int>("THAT", 4)); 
    symbolTable.insert(pair<string, int>("R5", 5)); 
    symbolTable.insert(pair<string, int>("R6", 6)); 
    symbolTable.insert(pair<string, int>("R7", 7)); 
    symbolTable.insert(pair<string, int>("R8", 8)); 
    symbolTable.insert(pair<string, int>("R9", 9)); 
    symbolTable.insert(pair<string, int>("R10", 10)); 
    symbolTable.insert(pair<string, int>("R11", 11)); 
    symbolTable.insert(pair<string, int>("R12", 12)); 
    symbolTable.insert(pair<string, int>("R13", 13)); 
    symbolTable.insert(pair<string, int>("R14", 14)); 
    symbolTable.insert(pair<string, int>("R15", 15)); 
    symbolTable.insert(pair<string, int>("KBD", 24576));
    symbolTable.insert(pair<string, int>("SCREEN", 16384));
    
    string line;  
    string input;
    int counter = 0;
    while (getline(cin, line)) {
        //remove spaces, tabs, comments:
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); //remove all spaces 
        line.erase(remove(line.begin(), line.end(), '\t'), line.end()); //remove all tabs 
        line = line.substr(0, line.find("//")); //remove all comments
        if (line[0] == '(') { //if labels are present
          string label = line.substr(1, line.find(')')-1);
          symbolTable.insert(pair<string, int>(label, counter));
          line.clear();
         }
        if (!line.empty()) { 
              if (line[0] == '@') {
                  if (line.length() > 2 && line[line.length()-1] == ';') {  //@sth;
                    cout << "ERROR: end of line expected but semicolon is found\n";
                    return 0;
                  }
              }
              else if (line.find(';') != string::npos) { //check if jump is present
                  if (line[0] == ';') {
                     cout << "ERROR: end of line expected but semicolon is found\n";
                     return 0;                     
                  }
                  string jumpCheck = line.substr(line.find(";", 0) + 1, line.length()-line.find(";", 0));
                  if (!jumpCheck.empty() && jumpCheck[jumpCheck.length()-1] == ';') { //check for jump; error
                     cout << "ERROR: end of line expected but semicolon is found\n";
                     return 0;                      
                  } 
                  else if (!jumpCheck.empty() && jumpTable.find(jumpCheck) == jumpTable.end() ) {
                      cout << "ERROR: expression expected\n";
                      return 0;
                  }
                  else if (jumpCheck.empty()) {
                      line.erase(remove(line.begin(), line.end(), ';'), line.end());
                  }
              }
              else if (line.find('=') != string::npos) { //dest and comp must be present
                 string destCheck = line.substr(0, line.find("=", 0));
                 //cout << "dest = " << destCheck << endl;
                  if (destTable.find(destCheck) == destTable.end()) { //check if dest is valid
                    cout << "ERROR: expression expected\n";
                    return 0;
                   }
                  string compCheck = line.substr(line.find("=", 0)+1, line.find(";", 0)-line.find("=", 0)-1);
                  //cout << "comp = " << compCheck << endl;
                  if (compTable.find(compCheck) == compTable.end()) { //check if comp is valid 
                    cout << "ERROR: expression expected\n";
                    return 0;
                   }
                }
            else {
                if (compTable.find(line) == compTable.end()) {
                    cout << "ERROR: expression expected\n";
                    return 0;                   
                 }
            }
          input += line + '\n';  
          counter++;
        }
    } 
   // cout << input;
    stringstream ss(input);
    string validLine;
    string aIsString;
    string aIsNumber;
    int entryIndex = 16;
    while (!ss.eof()) {
        ss >> validLine;
        if (!validLine.empty() ) {
        if (validLine[0] == '@') {  //if it is an A-instruction
            validLine.erase(0,1);
            if (isdigit(validLine[0])) { //if A-instruction is a number
                int value = stoi(validLine); //convert value to integer
                aIsNumber = bitset<16> (value).to_string(); //find binary equivalent
                if (value < -32768 || value > 32767) { 
                    aIsNumber = bitset<16> (16).to_string();
                   }
                    cout << aIsNumber << endl;
                    validLine.clear();
            }
            else { //if A-instruction is a label or built-in symbol
                if (symbolTable.find(validLine)!= symbolTable.end()) { //if found in table, display binary equiv
                map<string, int>::iterator pos;
                pos = symbolTable.find(validLine);
                int value2 = pos->second;
                aIsString = bitset<16> (value2).to_string();
                cout << aIsString << endl; 
                }
                else { //if A-instruction is a new variable
                   symbolTable.insert(pair<string, int>(validLine, entryIndex)); 
                   aIsString = bitset<16> (entryIndex).to_string();;
                   cout << aIsString << endl; 
                   entryIndex++; //increment index for next variable
                }
            }
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