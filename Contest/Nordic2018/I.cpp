#include<bits/stdc++.h>
using namespace std;

pair<string,string> a[1004];

bool bigger(string s,string t){
    if(s.size()!=t.size())return s.size()>t.size();
    for(int i=0;i<int(s.size());++i)if(s[i]!=t[i])return s[i]>t[i];
    return false;
}

string add(string s,string t){
    if(bigger(t,s))swap(s,t);
    reverse(s.begin(),s.end());
    reverse(t.begin(),t.end());
    for(int i=0;i<int(t.size());++i)s[i]+=t[i]-'0';
    for(int i=0;i<int(s.size())-1;++i)if(s[i]>'9')s[i]-=10,++s[i+1];
    if(s.back()>'9')s.back()-=10,s.push_back('1');
    reverse(s.begin(),s.end());
    return s;
}

int main(){
    int n; cin>>n;
    string tar; cin>>tar;
    for(int i=0;i<n;++i){
        cin>>a[i].first>>a[i].second;
    }
    sort(a,a+n,[](const pair<string,string> &a,const pair<string,string> &b){
        return bigger(a.second,b.second);
    });
    string now="0";
    vector<string> ans;
    for(int i=0;i<n;++i){
        if(bigger(add(now,a[i].second),tar))continue;
        now=add(now,a[i].second);
        ans.push_back(a[i].first);
    }
    if(now==tar){
        cout<<ans.size()<<endl;
        for(string s:ans)cout<<s<<endl;
    }
    else cout<<0;
}
