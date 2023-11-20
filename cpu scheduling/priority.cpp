#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"


signed main(){
    vector<vector<int>>v;
    cout<<"enter the no. of processes : ";
    int n;cin>>n;
    int mn=INT_MAX;
    int mx=INT_MIN;
    cout<<"enter the arival ,burst time and priority : "<<endl;
    for(int i=0;i<n;i++){
        vector<int>v1;
        int a,b,p;cin>>a>>b>>p;
        v1.push_back(a);
        v1.push_back(b);
        v1.push_back(p);
        
        // v1.push_back(i);
        v.push_back(v1);
        mn=min(mn,a);
        mx=max(mx,a);
    }
    vector<vector<int>>ms;
    vector<int>ct;
    for(int i=0;i<n;i++) ct.push_back(0);
    for(int i=0;i<n;i++){
        vector<int>m;
        ct.push_back(0);
        if(v[i][0]==0){
            m.push_back(-1*v[i][2]);
            m.push_back(v[i][0]);
            m.push_back(i);
            ms.push_back(m);
        }
    }
    vector<int>red;
    int r=0; // current time
    while(true){
        if(red.size()==n){
            break;
        }
        if(ms.size()==0){
            r++;
            for(int i=0;i<n;i++){
                if(v[i][0]==r){
                    vector<int>m1;
                    m1.push_back(-1*v[i][2]);
                    m1.push_back(v[i][0]);
                    m1.push_back(i);
                    ms.push_back(m1);
                };
            }
        }
        else{
            sort(ms.begin(),ms.end());
            int in=ms[0][2];
            int br=v[in][1];
            ct[in]=r+br;
            red.push_back(in);
            r=r+br;
            for(int i=0;i<n;i++){
                if(v[i][0]>r-br and v[i][0]<=r){
                    vector<int>m1;
                    m1.push_back(-1*v[i][2]);
                    m1.push_back(v[i][0]);
                    m1.push_back(i);
                    ms.push_back(m1);
                }
            }
            ms.erase(ms.begin());
        }    
    }
    cout<<endl;
    cout<<"Gantt chart : ";
    for(int i=0;i<n;i++){
        cout<<"p"<<red[i]+1<<" ";
    }
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
    cout<<"id\tat\tbt\tct\ttat\twt"<<endl;
    for(int i=0;i<n;i++){
        cout<<i+1<<"\t";
        for(int j=0;j<5;j++) cout<<v[i][j]<<"        ";
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

