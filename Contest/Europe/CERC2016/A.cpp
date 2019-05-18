#include<bits/stdc++.h>
using namespace std;

struct window{
    int n,m,hh;
    tuple<int,int,int> build(vector<string> &v){
        // cout<<"bulid:"<<endl;
        // for(string s:v)cout<<s<<endl;
        int res=0;
        for(string s:v)for(char c:s){
            res=(7902131ll*res+c)%1000000123;
        }
        return make_tuple(v.size(),v[0].size(),res);
    }
    void flip(vector<string> &v){
        vector<string> t(v[0].size());
        for(int i=0;i<(int)v.size();++i){
            for(int j=0;j<(int)v[0].size();++j){
                t[j]+=v[i][j];
            }
        }
        for(int i=0;i<(int)v[0].size();++i)reverse(t[i].begin(),t[i].end());
        v=t;
    }
    window(vector<string> &v){
        n=10000000,m=0,hh=0;
        tie(n,m,hh)=min(make_tuple(n,m,hh),build(v));
        flip(v);
        tie(n,m,hh)=min(make_tuple(n,m,hh),build(v));
        flip(v);
        tie(n,m,hh)=min(make_tuple(n,m,hh),build(v));
        flip(v);
        tie(n,m,hh)=min(make_tuple(n,m,hh),build(v));
        flip(v);
    }
    bool operator<(const window &b)const{
        return make_tuple(n,m,hh)<make_tuple(b.n,b.m,b.hh);
    }
};

set<window> st;
string mp[123];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,m; cin>>n>>m;
    for(int i=0;i<n;++i)cin>>mp[i];
    bool st1=1;
    for(int i=1;i<n;++i){
        if(mp[i][1]=='#')st1=1;
        else if(st1){
            bool st2=1;
            for(int j=1;j<m;++j){
                if(mp[1][j]=='#')st2=1;
                else if(st2){
                    int ito=i,jto=j;
                    while(mp[ito+1][j]!='#')++ito;
                    while(mp[i][jto+1]!='#')++jto;
                    vector<string> tmp;
                    for(int z=i;z<=ito;++z)tmp.push_back(mp[z].substr(j,jto-j+1));
                    // cout<<i<<" "<<ito<<" "<<j<<" "<<jto<<" "<<endl;
                    st.insert(window(tmp));
                    // cout<<st.size()<<endl;
                    st2=0;
                }
                else continue;
            }
            st1=0;
        }
        else continue;
    }
    cout<<st.size()<<endl;
}
