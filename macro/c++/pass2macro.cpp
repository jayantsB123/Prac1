#include<bits/stdc++.h>
using namespace std;

int main() {
    // File streams for input and output
    fstream mdt, mnt, ic, pass2;
    mdt.open("mdt.txt", ios::in);
    mnt.open("mnt.txt", ios::in);
    ic.open("ic.txt", ios::in);
    pass2.open("pass2.txt", ios::out);

    // Read Macro Name Table (MNT) and count occurrences
    string line = "";
    map<string, int> m;
    while (getline(mnt, line)) {
        string temp = "";
        for (auto ch : line) {
            if (ch == ' ')
                break;
            else
                temp += ch;
        }
        m[temp]++;
    }

    // Map to store macro definitions
    map<string, vector<string>> macro;
    while (getline(ic, line)) {
        string temp = "";
        for (auto ch : line) {
            if (ch == ' ')
                break;
            else
                temp += ch;
        }
        string macro_name = temp;
        if (m[temp]) {
            bool check = 0;
            temp = "";
            for (auto ch : line) {
                if (ch == ' ') {
                    check = 1;
                } else if (ch == '=') {
                    temp = "";
                } else if (ch == ',') {
                    macro[macro_name].push_back(temp);
                    temp = "";
                } else if (check)
                    temp += ch;
            }
            macro[macro_name].push_back(temp);
        }
    }

    // Map to store expanded macro calls
    map<string, vector<string>> ans;
    string answer = "";
    string macro_name = "";
    bool check = 1;
    while (getline(mdt, line)) {
        string temp = "";
        for (auto ch : line) {
            if (ch == ' ')
                break;
            else
                temp += ch;
        }
        if (temp == "MEND")
            check = 1;
        else if (check == 1) {
            macro_name = temp;
            check = 0;
        } else if (!check) {
            temp = "";
            answer = "";
            for (auto ch : line) {
                if (ch == ' ') {
                    answer += temp + " ";
                    temp = "";
                } else if (ch == ',') {
                    answer += macro[macro_name][temp[1] - '0'] + ',';
                    temp = "";
                } else {
                    temp += ch;
                }
            }
            answer += macro[macro_name][temp[1] - '0'] + ',';
            ans[macro_name].push_back(answer);
        }
    }

    // Close and reopen input file
    ic.close();
    ic.open("ic.txt", ios::in);
    
    // Process intermediate code and write to output
    while (getline(ic, line)) {
        string temp = "";
        for (auto ch : line) {
            if (ch == ' ')
                break;
            else
                temp += ch;
        }
        if (m[temp]) {
            for (auto x : ans[temp]) {
                pass2 << x << endl;
            }
        } else
            pass2 << line << endl;
    }

    // Close all file streams
    ic.close();
    mdt.close();
    mnt.close();
    pass2.close();
}
