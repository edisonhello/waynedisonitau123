#include<bits/stdc++.h>
using namespace std;

int stat[256][2];

int main(){
    freopen("boolean.in","r",stdin);
    freopen("boolean.out","w",stdout);
    string s; cin>>s;
    string ns;
    vector<string> vars;
    for(char c:s){
        if(c=='|'){
            vars.push_back(ns);
            ns="";
        }
        else {
            ns+=c;
        }
    }
    vars.push_back(ns);
    for(string s:vars){
        if(s.size()==2u){
            stat[s[1]][0]=1;
        }
        else{
            stat[s[0]][1]=1;
        }
    }
    long long ans=1;
    int apps=0;
    bool both=0;
    for(int i=0;i<256;++i){
        if(stat[i][0]==0 && stat[i][1]==0)continue;
        ++apps;
        if(stat[i][0] && stat[i][1])both=1;
        else ans<<=1;
    }
    if(both)cout<<(1ll<<apps)<<endl;
    else cout<<ans-1<<endl;
}
