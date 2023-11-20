#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

signed main(){
    cout<<"no. of processes : ";
    int n;cin>>n;
    vector<vector<int>>v;
    int mn=INT_MAX;
    int mx=INT_MIN;
    cout<<"enter arival and brust time for all processes : "<<endl;
    for(int i=0;i<n;i++){
        vector<int>v1;
        int a,b;cin>>a>>b;
        v1.push_back(a);
        v1.push_back(b);
        v.push_back(v1);
        mn=min(mn,a);
        mx=max(mx,a);
    }
    int r=mn;
    vector<vector<int>>ms;
    for(int i=0;i<n;i++){
        if(v[i][0]==mn){
            vector<int>m;
            m.push_back(v[i][1]);
            m.push_back(v[i][0]);
            m.push_back(i);
            ms.push_back(m);
        }
    }
    vector<int>ct;
    vector<int>g;
    for(int i=0;i<n;i++) ct.push_back(0);
    while(true){
        if(ms.size()==0  and r>mx) break;
        if(ms.size()==0) r++;
        else{
            sort(ms.begin(),ms.end());
            ms[0][0]-=1;
            g.push_back(ms[0][2]);
            r++;
            if(ms[0][0]==0){
                ct[ms[0][2]]=r;
                ms.erase(ms.begin());
            }
            for(int i=0;i<n;i++){
                if(v[i][0]==r){
                    vector<int>m1;
                    m1.push_back(v[i][1]);
                    m1.push_back(v[i][0]);
                    m1.push_back(i);
                    ms.push_back(m1);
                }
            }
        }

    }
    cout<<endl;
    cout<<"Gantt chart : ";
    for(auto i : g) cout<<"p"<<i+1<<" ";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    vector<int>tat;
    for(int i=0;i<n;i++){
        tat.push_back(ct[i]-v[i][0]);
    }
    vector<int>wt;
    for(int i=0;i<n;i++){
        wt.push_back(tat[i]-v[i][1]);
    }
    for(int i=0;i<n;i++){
        v[i].push_back(ct[i]);
        v[i].push_back(tat[i]);
        v[i].push_back(wt[i]);
    }
    cout<<"ID\tAT\tBT\tCT\ttat\tWT "<<endl;
    for(int i=0;i<n;i++){
        cout<<i+1<<"       ";
        for(int j=0;j<v[i].size();j++){
            cout<<v[i][j]<<"\t";
        }
        cout<<endl;
    }

    
     int sumTAT = 0, sumWT = 0;
    
    for (int i = 0; i < n; i++) {
        sumTAT += tat[i];
        sumWT += wt[i];
    }
    
    double avgTAT = (double)sumTAT / n;
    double avgWT = (double)sumWT / n;
    
    cout << "Average Turnaround Time = " << avgTAT << endl;
    cout << "Average Waiting Time = " << avgWT << endl;

    return 0;
}