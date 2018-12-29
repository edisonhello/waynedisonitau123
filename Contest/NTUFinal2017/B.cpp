#include<bits/stdc++.h>
using namespace std;

int cc[256];
int to[1000006];
int v[1000006];

bool canibwt(string s){
    memset(cc,0,sizeof(cc));
    int n=s.size();
    for(int i=0;i<n;++i)v[i]=to[i]=0;
    for(char c:s)++cc[c];
    for(int i=255;i>0;--i)cc[i]=cc[i-1];
    for(int i=1;i<256;++i)cc[i]+=cc[i-1];
    for(int i=0;i<n;++i){
        to[i]=cc[s[i]];
        ++cc[s[i]];
    }
    v[0]=1; int now=to[0],vi=1;
    while(!v[now] && now<n){
        v[now]=1;
        ++vi;
        now=to[now];
    }
    if(vi==n)return 1;
    return 0;
}

void solve(string s){
    if(s.size()==1u){
        cout<<"life is hard"<<'\n';
        return;
    }
    bool allsame=1;
    for(int i=1;i<int(s.size());++i)if(s[i]!=s[i-1])allsame=0;
    if(allsame){
        if(s[0]=='a'){
            cout<<s.substr(0,s.size()-1)<<"b"<<'\n';
        }
        else{
            cout<<"a"<<s.substr(1,s.size()-1)<<'\n';
        }
        return;
    }
    if(s=="za"){
        cout<<"ab"<<'\n';
        return;
    }

    bool need=0;
    int n=s.size();
    for(int k=1;k<=n;++k){
        if(s.size()%k)continue;
        string t;
        for(int i=0;i<int(s.size());i+=k)t+=s[i];
        bool no=0;
        for(int i=0;i<int(s.size());++i){
            if(s[i]!=t[i/k]){
                no=1;
                break;
            }
        }
        if(no)continue;
        if(canibwt(t)){
            need=1;
            break;
        }
    }

    if(!need){
        cout<<s<<'\n';
        return;
    }
    if([&]()->bool{
        for(int i=1;i<n;++i)if(s[i]!='a')return 0;
        return 1;
    }()){
        char mx='a';
        for(char c:s)mx=max(mx,c);
        if(n==2)++mx;
        cout<<s.substr(0,s.size()-1)<<mx<<'\n';
        return;
    }
    cout<<"a"<<s.substr(1,s.size()-1)<<'\n';
}

int main(){
    string s; while(cin>>s){
        solve(s);
    }
}
