#include<bits/stdc++.h>
using namespace std;

#define int long long



signed main()
{
    cout<<"total no. of processes : ";
    int n;cin>>n;
    
    vector<vector<int>>v;
    int mn=INT_MAX;
    int mx=INT_MIN;
    cout<<"enter the arival and brust time of all processes : "<<endl;
    for(int i=0;i<n;i++){
        int a,b;cin>>a>>b;
        vector<int>v1;
        v1.push_back(a);v1.push_back(b);
        v.push_back(v1);
        mn=min(a,mn);
        mx=max(a,mx);
    }
    vector<vector<int>>v2;
    int r=mn;
    vector<int>red;
    for(int i=0;i<n;i++){
        if(v[i][0]==mn){
            vector<int>m=v[i];
            m.push_back(i);
            v2.push_back(m);
            red.push_back(i);
        }
    }
    
    vector<int>ct;
    for(int i=0;i<n;i++){
        ct.push_back(0);
    }
    while(true){
        if(v2.size()==0 and r>mx) break;
        if(v2.size()==0) r++;
        else{
            sort(v2.begin(),v2.end());
            r=r+v2[0][1];
            for(int i=0;i<n;i++){
                if(v[i][0]>r-v2[0][1] and v[i][0]<=r){
                    vector<int>m1=v[i];
                    m1.push_back(i);
                    v2.push_back(m1);
                    red.push_back(i);
                }
            }
            ct[v2[0][2]]=r;
            v2.erase(v2.begin());
        }
    }
    cout<<endl;
    cout<<"Gantt chart : ";
    for(int i=0;i<n;i++) cout<<"p"<<red[i]<<" ";
    cout<<endl;
    for(int i=0;i<n;i++){
        v[i].push_back(ct[i]); //ct
        v[i].push_back(ct[i]-v[i][0]); //tat
        v[i].push_back(ct[i]-v[i][0]-v[i][1]); //wt
    }
    cout<<"ID\tAT\tBT\tCT\ttat\tWT "<<endl;
    for(int i=0;i<n;i++){
    cout<<i<<"\t"<<v[i][0]<<"\t"<<v[i][1]<<"\t"<<v[i][2]<<"\t"<<v[i][3]<<"\t"<<v[i][4]<<endl;
    }
    
    
     int sumTAT = 0, sumWT = 0;
    
    for (int i = 0; i < n; i++) {
        sumTAT += ct[i]-v[i][0];
        sumWT += ct[i]-v[i][0]-v[i][1];
    }
    
    double avgTAT = (double)sumTAT / n;
    double avgWT = (double)sumWT / n;
    
    cout << "Average Turnaround Time = " << avgTAT << endl;
    cout << "Average Waiting Time = " << avgWT << endl;

    return 0;
}