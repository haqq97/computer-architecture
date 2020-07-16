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
    destTable.insert(pair<string, string>("000", ""));
    destTable.insert(pair<string, string>("001", "M"));
    destTable.insert(pair<string, string>("010", "D"));
    destTable.insert(pair<string, string>("011", "MD"));
    destTable.insert(pair<string, string>("100", "A"));
    destTable.insert(pair<string, string>("101", "AM"));
    destTable.insert(pair<string, string>("110", "AD"));
    destTable.insert(pair<string, string> ("111", "AMD"));
    
    //create empty comp table
    map<string, string> compTable;
    //populate comp table with correct a values
    compTable.insert(pair<string, string>("0101010", "0"));
    compTable.insert(pair<string, string>("0111111", "1"));
    compTable.insert(pair<string, string>("0111010", "-1"));
    compTable.insert(pair<string, string>("0001100", "D"));
    compTable.insert(pair<string, string>("0110000", "A"));
    compTable.insert(pair<string, string>("0001101", "!D"));
    compTable.insert(pair<string, string>("0110001", "!A"));
    compTable.insert(pair<string, string>("0001111", "-D"));
    compTable.insert(pair<string, string>("0110011", "-A"));
    compTable.insert(pair<string, string>("0011111", "D+1"));
    compTable.insert(pair<string, string>("0110111", "A+1"));
    compTable.insert(pair<string, string>("0001110", "D-1"));
    compTable.insert(pair<string, string>("0110010", "A-1"));
    compTable.insert(pair<string, string>("0000010", "D+A"));
    compTable.insert(pair<string, string>("0010011", "D-A"));
    compTable.insert(pair<string, string>("0000111", "A-D"));
    compTable.insert(pair<string, string>("0000000", "D&A"));
    compTable.insert(pair<string, string>("0010101", "D|A"));
    compTable.insert(pair<string, string>("1110000", "M"));
    compTable.insert(pair<string, string>("1110001", "!M"));
    compTable.insert(pair<string, string>("1110011", "-M"));
    compTable.insert(pair<string, string>("1110111", "M+1"));
    compTable.insert(pair<string, string>("1110010", "M-1"));
    compTable.insert(pair<string, string>("1000010", "D+M"));
    compTable.insert(pair<string, string>("1010011", "D-M"));
    compTable.insert(pair<string, string>("1000111", "M-D"));
    compTable.insert(pair<string, string>("1000000", "D&M"));
    compTable.insert(pair<string, string>("1010101", "D|M"));
    
    //create empty jump table
    map<string, string> jumpTable;
    //populate jump table
    jumpTable.insert(pair<string, string>("000", ""));
    jumpTable.insert(pair<string, string>("001", "JGT"));
    jumpTable.insert(pair<string, string>("010", "JEQ"));
    jumpTable.insert(pair<string, string>("011", "JGE"));
    jumpTable.insert(pair<string, string>("100", "JLT"));
    jumpTable.insert(pair<string, string>("101", "JNE"));
    jumpTable.insert(pair<string, string>("110", "JLE"));
    jumpTable.insert(pair<string, string>("111", "JMP"));
    
    
    string line;
    while (getline(cin, line)) {
        if (line.length() != 16) { 
            cout << "ERROR: instruction bit size not 16\n";
            return 0;
        }
        else if (line[0] == '0') { //A-instruction
            cout << "@";
            int value = 0;
            int counter = 14;
            for (int i = 1; i < line.length(); i++) {
                if (line[i] == '1') {
                    value = value + pow(2,counter);
                }
               counter--;
            }
            cout << value;
        }
        else if (line[0] == '1') { //C-instruction
            if (line[1] != '1' && line[2] != '1' ) {
               cout << "ERROR: illegal HACK instruction\n"; 
               return 0;
            }
           string comp = line.substr(3, 7);
           //cout << "comp: " << comp << endl;
           if (compTable.find(comp) == compTable.end()) {
               cout << "ERROR: illegal HACK instruction\n"; 
               return 0;              
           }
            string dest = line.substr(10, 3);
            //cout << "dest: " << dest << endl;
           if (destTable.find(dest) == destTable.end()) {
               cout << "ERROR: illegal HACK instruction\n"; 
               return 0;              
           }
           string jump = line.substr(13, 3);
            //cout << "jump: " << jump << endl;
           if (jumpTable.find(jump) == jumpTable.end()) {
               cout << "ERROR: illegal HACK instruction\n"; 
               return 0;              
           }   
            map<string, string>::iterator cmp;
            map<string, string>::iterator dst;
            map<string, string>::iterator jmp;
            cmp = compTable.find(comp);
            dst = destTable.find(dest);
            jmp = jumpTable.find(jump);
            if (dest != "000") { //dest=comp or dest=comp;jump
                cout << dst->second;
                cout <<"=";
                cout << cmp->second;
                if (jump != "000") {
                    cout << ";";
                    cout << jmp->second;
                }
            }
            else if (dest == "000" ) { //comp;jump or comp
                cout << cmp->second;
                if (jump != "000") {
                    cout << ";";
                    cout << jmp->second;
                }
            }
        }
        else {
                cout << "ERROR: illegal HACK instruction\n"; 
               return 0;
        }
        cout << endl;
    }
    return 0;
}
