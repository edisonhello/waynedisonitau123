#include<bits/stdc++.h>
using namespace std;

unordered_map<string,pair<int,int>> mp;

string status[5][5]={
    {"New Customer",       "Promising",          "About to Sleep", "Lost",           "Lost"},
    {"Potential Loyalist", "Potential Loyalist", "About to Sleep", "Hibernating",    "Lost"},
    {"Potential Loyalist", "Potential Loyalist", "Need Attention", "About to Leave", "About to Leave"},
    {"Loyal Customer",     "Loyal Customer",     "Loyal Customer", "About to Leave", "About to Leave"},
    {"Champion",           "Loyal Customer",     "Loyal Customer", "About to Leave", "Can't Lose Them"}
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int r1,r2,r3,r4;
    int f1,f2,f3,f4;
    cin>>r1>>r2>>r3>>r4;
    cin>>f1>>f2>>f3>>f4;
    int q; cin>>q; for(int t=1;t<=q;++t){
        int a; string s; cin>>a>>s;
        if(a==1){
            auto &p=mp[s];
            p.first=t;
            ++p.second;
        }
        else{
            auto it=mp.find(s);
            if(it==mp.end()){
                cout<<"None"<<'\n';
            }
            else{
                double f=it->second.second-0.5;
                double r=t-it->second.first-0.5;
                int flv=-1;
                if(f<f1)flv=0;
                else if(f<f2)flv=1;
                else if(f<f3)flv=2;
                else if(f<f4)flv=3;
                else flv=4;
                int rlv=-1;
                if(r<r1)rlv=0;
                else if(r<r2)rlv=1;
                else if(r<r3)rlv=2;
                else if(r<r4)rlv=3;
                else rlv=4;
                cout<<status[flv][rlv]<<'\n';
            }
        }
    }
}
