#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native,arch=core-avx2")

#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

map<map<int,int>,int> mp;
int qys[15][15];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,cxs,cys; cin>>n>>cxs>>cys;
    map<int,int> tmp;
    mp[tmp]=1;
    stack<string> inputs;
    while(n--){ int t=3; while(t--){ string s; cin>>s; inputs.push(s); } }
    bool mns=inputs.size()&1;
    int q; cin>>q;
    for(int i=1;i<=q;++i)for(int j=0;j<cys;++j)cin>>qys[i][j];
    for(int i=1;i<=q;++i)for(int j=0;j<cys;++j)qys[0][j]=max(qys[0][j],qys[i][j]);
    while(inputs.size()){
        char c[3];
        int x[3];
        int id[3];
        for(int i=0;i<3;++i){
            string s=inputs.top(); inputs.pop();
            c[i]=s[0];
            if(s.size()==2u)x[i]=s[1]-'0';
            else x[i]=(x[1]-'0')*10+s[2]-'0';
            id[i]=(c[i]=='x'?x[i]:100+x[i]);
        }
        for(int i=0;i<3;++i){
            int j=(i+1)%3;
            map<map<int,int>,int> nw;
            for(pair<map<int,int>,int> p:mp){
                ++p.first[id[i]];
                nw[p.first]+=p.second;
            }
            for(pair<map<int,int>,int> p:mp){
                ++p.first[id[j]];
                nw[p.first]-=p.second;
            }
            mp.swap(nw);
            for(auto it=mp.begin();it!=mp.end();){
                if(it->second==0)it=mp.erase(it);
                else{
                    bool kill=0;
                    for(auto &p:it->first){
                        if(p.first>=100 && qys[0][p.first-100]<p.second){ kill=1; break; }
                    }
                    if(kill)it=mp.erase(it);
                    else ++it;
                }
            }
            /* for(auto &p:mp){
                for(auto &pp:p.first){
                    if(pp.first<100)cout<<"x"<<pp.first;
                    else cout<<"y"<<pp.first-100;
                    cout<<"^"<<pp.second<<" ";
                }
                cout<<": "<<p.second<<" + ";
            } */
            // cout<<endl;
        }
    }
    for(int z=1;z<=q;++z){
        vector<pair<vector<int>,int>> ans;
        for(auto &p:mp){
            bool match=1;
            for(int i=0;i<cys;++i){
                auto it=p.first.find(100+i);
                if(it==p.first.end() || it->second!=qys[z][i]){ match=0; break; }
            }
            if(match){
                ans.emplace_back(vector<int>(),0);
                ans.back().second=p.second;
                for(int i=0;i<cxs;++i){
                    auto it=p.first.find(i);
                    int x=0;
                    if(it!=p.first.end())x=it->second;
                    ans.back().first.push_back(x);
                    // cout<<" "<<x;
                }
                // cout<<endl;
            }
        }
        sort(ans.begin(),ans.end());
        for(auto &p:ans){
            // printf("%4d", -p.second);
            cout<<setw(4)<<p.second*(mns?-1:1);
            for(int i:p.first)cout<<" "<<i;
            cout<<'\n';
        }
        if(z != q) cout<<'\n';
    }
}
