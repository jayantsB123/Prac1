#include<bits/stdc++.h> // Include necessary header files for input/output operations and data structures
using namespace std;

int main(){
    fstream ic, mc, ltab, stab; // Declare file stream objects for input and output files
    ic.open("IC.txt", ios::in); // Open input file "IC.txt" in read mode
    ltab.open("LITTAB.txt", ios::in); // Open input file "LITTAB.txt" in read mode
    stab.open("SYMTAB.txt", ios::in); // Open input file "SYMTAB.txt" in read mode
    mc.open("MachineCode.txt", ios::out); // Open output file "MachineCode.txt" in write mode

    vector<int> st, lt; // Declare vectors to store values from SYMTAB and LITTAB

    string sa, sb; // Declare strings to store lines from SYMTAB and LITTAB

    // Read values from SYMTAB and store them in the vector 'st'
    while(getline(stab, sa)){
        string temp = "";
        int x = sa.size();
        for(int i = x - 1; i >= 0; --i){
            if(sa[i] == ' ') break;
            temp += sa[i];
        }
        reverse(temp.begin(), temp.end());
        st.push_back(stoi(temp));
    }

    // Read values from LITTAB and store them in the vector 'lt'
    while(getline(ltab, sb)){
        string temp = "";
        int x = sb.size();
        for(int i = x - 1; i >= 0; --i){
            if(sb[i] == ' ') break;
            temp += sb[i];
        }
        reverse(temp.begin(), temp.end());
        lt.push_back(stoi(temp));
    }

    string line;
    // Read lines from IC.txt and process the instructions
    while(getline(ic, line)){
        string temp = "", str = "";
        int flag = 0, last = 0;

        // Iterate through each character in the line
        for(auto ch : line){
            if(ch == '('){
                temp = "";
                str = "";
            }
            else if(ch == ','){
                if(temp == "AD"){
                    flag = 1;
                    break;
                }
                str = temp;
                temp = "";
                continue;
            }
            else if(ch == ')'){
                if(temp == "00"){
                    last = 1;
                    break;
                }
                if(str != "S" and str != "L"){
                    if(str == "DL") mc << "00 00 ";
                    else mc << temp << " ";
                }
                else if(str == "S"){
                    int x = temp[1] - '0';
                    mc << st[x];
                }
                else if(str == "L"){
                    int x = temp[0] - '0';
                    mc << lt[x];
                }
                str = "";
            } else temp += ch;
        }
        if(flag == 1) continue;
        if(last == 1) break;
        mc << endl;
    }
}
