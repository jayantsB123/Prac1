#include<bits/stdc++.h>

using namespace std;


int main()
{
    fstream mdt, mnt, ic, pass2;
    mdt.open("mdt.txt", ios::in);
    mnt.open("mnt.txt", ios::in);
    ic.open("ic.txt", ios::in);
    pass2.open("pass2.txt", ios::out);

    string line="";
    map<string,int>m;
    while(getline(mnt,line))
    {
        string temp="";
        for(auto ch:line)
        {
            if(ch==' ') break;
            else temp+=ch;
        }
        m[temp]++;
    }
}