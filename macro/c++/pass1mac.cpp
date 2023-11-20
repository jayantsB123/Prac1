#include<bits/stdc++.h>
using namespace std;

int main(){
    // Declare file stream objects for input and output files
    fstream inp, mnt, mdt, ala;
    inp.open("pass.txt", ios::in);    
    mnt.open("mnt.txt", ios::out);    
    mdt.open("mdt.txt", ios::out);    
    ala.open("ala.txt", ios::out);

    // Initialize MNT with column headers
    mnt << "INDEX  " << "  NAME  " << "  ALA  " << endl;

    // Declare variables
    string line;
    int cnt = 0, flag = 0, ind = 0, num = 1;
    map<string, int> mp, mp1;

    // Read lines from input file
    while(getline(inp, line)){
        // Check if line is "MACRO" to start processing a macro definition
        if(line == "MACRO"){
            flag = 1;
            num = 1;
            continue;
        }
        // Check if line is "MEND" to end processing a macro definition
        if(line == "MEND"){
            flag = 0;
            mdt << line << endl;
            continue;
        }

        // Increment line count
        cnt++;

        // Process lines within a macro definition
        if(flag == 1){
            mdt << line << endl;

            // Extract macro name and index, and populate MNT
            string temp = "";
            for(auto ch : line){
                if(ch == ' '){
                    mnt << ind << "        " << temp << "     " << cnt << endl;
                    ind++;
                    mp1[temp] = 1;  // Mark parameter in ALA
                    break;
                }
                temp += ch;
            }

            // Extract parameters and their positions, and populate ALA
            temp = "";
            for(auto ch : line){
                if(ch == '='){
                    mp[temp] = num;
                    break;
                }
                else if(ch == ' '){
                    temp = "";
                    continue;
                }
                else if(ch == ','){
                    mp[temp] = num;
                    num++;
                    temp = "";
                }
                else temp += ch;
            }

            flag = 2;  // Move to processing lines with arguments
            continue;
        }

        // Process lines with arguments in a macro call
        if(flag == 2){
            string temp = "";
            for(auto ch : line){
                if(ch == ' '){
                    mdt << temp << " ";
                    temp = "";
                } 
                else if(ch == ','){
                    mdt << "#" << mp[temp] << ", ";
                    temp = "";
                }
                else temp += ch;
            }
            mdt << "#" << mp[temp] << endl;
        }

        // Process lines outside of macro definition
        if(flag == 0){
            string temp = "";
            int q = 0, w = 1;
            for(auto ch : line){
                if(ch == ' '){
                    if(mp1[temp] == 1){
                        ala << line << endl;
                        q = 1; 
                        temp = "";
                    }
                }
                else if(ch == ',' and q == 1){
                    ala << w-1 << "   " << temp << "   #" << w << endl;
                    w++;
                    temp = "";  
                }
                else if(ch == '=' and q == 1){
                    break;
                }
                else temp += ch;
            }
            if(q == 1) ala << w-1 << "   " << temp << "   #" << w << endl;
        }
    }
}
