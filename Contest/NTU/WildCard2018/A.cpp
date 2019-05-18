#include<bits/stdc++.h>
using namespace std;

string s[555];
vector<int> G[555];
int ind[555];

void go(int idx,int l,int r){
    while(l<=r && idx==int(s[l].size()))++l;
    if(l>=r)return;

    for(int i=l+1;i<=r;++i){
        if(s[i][idx]!=s[i-1][idx]){
            G[s[i-1][idx]].push_back(s[i][idx]);
//             cout<<"add edge "<<s[i-1][idx]<<" to "<<s[i][idx]<<endl;
            go(idx+1,l,i-1);
            l=i;
        }
    }
    go(idx+1,l,r);
}

int main(){
    int n; while(cin>>n,n){
        for(int i=0;i<555;++i)G[i].clear(),ind[i]=0;

        for(int i=1;i<=n;++i)cin>>s[i];
        bool no=0;
        for(int i=2;i<=n;++i){
            if(s[i].size()<s[i-1].size() && s[i-1].substr(0,s[i].size())==s[i]){
                no=1;
            }
        }
        if(no){
            cout<<"no"<<'\n';
            continue;
        }
        go(0,1,n);
        queue<int> q;
        for(int i='a';i<='z';++i){
            for(int j:G[i]){
                ++ind[j];
            }
        }
        for(int i='a';i<='z';++i){
            if(ind[i]==0)q.push(i);
        }
        vector<int> tp;
        while(q.size()){
            int now=q.front(); q.pop();
            tp.push_back(now);
            for(int i:G[now]){
                --ind[i];
                if(ind[i]==0)q.push(i);
            }
        }
        if(tp.size()==26u)cout<<"yes"<<'\n';
        else cout<<"no\n";
    }
}
