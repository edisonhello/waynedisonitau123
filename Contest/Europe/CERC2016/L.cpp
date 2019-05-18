#include<bits/stdc++.h>
using namespace std;

int val[55];
vector<int> x[8];

vector<string> ans;

string itos(int x){
    stack<int> st;
    while(x){
        st.push(x%10);
        x/=10;
    }
    string s;
    while(st.size()){
        s+=st.top()+'0';
        st.pop();
    }
    return s;
}

void build(bool n1,int x1,bool n2,int x2){
    string s;
    if(n1)s+="!";
    s+="x";
    s+=itos(x1);
    s+=" -> ";
    if(n2)s+="!";
    s+="x";
    s+=itos(x2);
    ans.push_back(s);
}

int main(){
    int n; cin>>n;
    for(int i=1;i<=n;++i){
        int t; cin>>t;
        if(t)val[i]|=1;
    }
    for(int i=1;i<=n;++i){
        int t; cin>>t;
        if(t)val[i]|=2;
    }
    for(int i=1;i<=n;++i){
        int t; cin>>t;
        if(t)val[i]|=4;
    }
    for(int i=1;i<=n;++i)x[val[i]].push_back(i);
    for(int i=0;i<8;++i){
        if(x[i].size()>1u){
            for(int j=1;j<int(x[i].size());++j){
                build(0,x[i][0],0,x[i][j]);
                build(0,x[i][j],0,x[i][0]);
            }
        }
    }
    int app=int(!(x[3].empty() && x[4].empty()))+int(!(x[5].empty() && x[2].empty()))+int(!(x[6].empty() && x[1].empty()));
    if(app==3){
        exit((cout<<-1<<endl,0));
    }
    assert(app==2);
    vector<int> tapp;
    if(x[3].size())tapp.push_back(3);
    else if(x[4].size())tapp.push_back(-4);
    if(x[5].size())tapp.push_back(5);
    else if(x[2].size())tapp.push_back(-2);
    if(x[6].size())tapp.push_back(6);
    else if(x[1].size())tapp.push_back(-1);
    int a1=tapp[0],a2=tapp[1];
    build(1^(a1<0),x[abs(a1)][0],0^(a2<0),x[abs(a2)][0]);
    build(1^(a2<0),x[abs(a2)][0],0^(a1<0),x[abs(a1)][0]);
    if(x[3].size() && x[4].size()){
        build(0,x[3][0],1,x[4][0]);
        build(1,x[4][0],0,x[3][0]);
    }
    if(x[2].size() && x[5].size()){
        build(0,x[2][0],1,x[5][0]);
        build(1,x[5][0],0,x[2][0]);
    }
    if(x[1].size() && x[6].size()){
        build(0,x[1][0],1,x[6][0]);
        build(1,x[6][0],0,x[1][0]);
    }
    if(x[0].size()){
        build(0,x[0][0],0,1);
        build(0,x[0][0],1,1);
    }
    if(x[7].size()){
        build(0,1,0,x[7][0]);
        build(1,1,0,x[7][0]);
    }
    cout<<ans.size()<<endl;
    for(auto s:ans)cout<<s<<'\n';
}
