#include<bits/stdc++.h>
using namespace std;

string s;

bool notsame(string s,string t){
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    return s!=t;
}

int get(string s,string t){
    if(notsame(s,t))return 1e9;
    int n=int(s.size());
    int ans=0;
    for(int i=0;i<n;++i){
        char want=t[i];
        if(s[i]==want)continue;
        for(int j=i+1;;++j){
            if(s[j]==want){
                for(int k=j;k>=i+1;--k)swap(s[k],s[k-1]),++ans;
                break;
            }
        }
    }
    return ans;
}

int main(){
    int n,m; cin>>n>>m;
    for(int i=1;i<=n;++i){
        int t; cin>>t;
        if(t==0)s+='0';
        else s+='1';
    }
    vector<int> a(m);
    for(int &i:a)cin>>i;
    string sa,ta;
    for(int i=0;i<m;++i){
        for(int j=0;j<a[i];++j){
            sa+=(i&1?'1':'0');
            ta+=(i&1?'0':'1');
        }
    }
    cout<<min(get(s,sa),get(s,ta))<<endl;
}
