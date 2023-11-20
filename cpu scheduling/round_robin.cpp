#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
signed main(){
    cout<<"enter the number of processes : ";
    int n;cin>>n;
    cout<<"Enter time quantam  : ";
    int q; cin>>q;
    vector<vector<int>>v;
    int mn=INT_MAX;
    int mx=INT_MIN;
    vector<int>dm;
    
    for(int i=0;i<n;i++){
        vector<int>v1;
        cout<<"Enter the arival and brust time for  processes "<<i+1<<" : ";
        int a;cin>>a;
        int b;cin>>b;
        v1.push_back(a);
        v1.push_back(b);
        dm.push_back(b);
        mn=min(mn,a);
        v.push_back(v1);
        mx=max(mx,a);
    }
    int r=mn;
    vector<int>temp;
    
    for(int i=0;i<n;i++){
        if(v[i][0]==mn) temp.push_back(i);
    }
    vector<int>ct;
    for(int i=0;i<n;i++){
        ct.push_back(0);
    }
    vector<int>g;
    while(true){
        if(temp.size()==0 and r>mx) break;
        if(temp.size()==0){
            r+=q;
            for(int i=0;i<n;i++){
                if(v[i][0]>r-q and v[i][0]<=r) temp.push_back(i);
            }
        } 
        else{
        int p=temp[0];
        if(v[p][1]-q>0){
            v[p][1]-=q;
            r+=q;
            for(int i=0;i<n;i++){
                if(v[i][0]>r-q and v[i][0]<=r){
                    temp.push_back(i);
                }
            }
            temp.push_back(p);
            g.push_back(p);
            temp.erase(temp.begin());
        }
        else{
            
            r+=v[p][1];
            v[p][1]=0;
            for(int i=0;i<n;i++){
                if(v[i][0]>r-v[p][1] and v[i][0]<=r){
                    temp.push_back(i);
                }
            }
            ct[p]=r;
            g.push_back(p);
            temp.erase(temp.begin());
        }
        }
       
    }
    cout<<endl;
    cout<<"Gantt chart : ";
     for(auto x :g) cout<<"p"<<x+1<<" ";
        cout<<endl;
        cout<<endl;
    vector<int>tat;
    for(int i=0;i<n;i++){
        tat.push_back(ct[i]-v[i][0]);
    }
    vector<int>wt;
    for(int i=0;i<n;i++){
        wt.push_back(tat[i]-dm[i]);
    }
    for(int i=0;i<n;i++){
        v[i][1]=dm[i];
        v[i].push_back(ct[i]);
        v[i].push_back(tat[i]);
        v[i].push_back(wt[i]);
    }
    cout<<"id\tat\tbt\tct\ttat\twt"<<endl;
    for(int i=0;i<n;i++){
        cout<<i+1<<"         ";
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

