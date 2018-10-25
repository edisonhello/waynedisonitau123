#include<bits/stdc++.h>
using namespace std;

void no(){
    cout<<-1<<endl;
    exit(0);
}

struct node{
    node *ch[2];
    int bl,wh,sbl,swh;
    node():bl(0),wh(0),sbl(0),swh(0){
        ch[0]=ch[1]=0;
    }
    void pull(){
        sbl=bl+(ch[0]?ch[0]->sbl:0)+(ch[1]?ch[1]->sbl:0);
        swh=wh+(ch[0]?ch[0]->swh:0)+(ch[1]?ch[1]->swh:0);
    }
} *root;

int pint(string s){
    stringstream ss(s);
    int t; ss>>t;
    return t;
}

void parse(string s,int &a,int &b,int &c,int &d,int &mask){
    vector<int> dot;
    int sl=0;
    for(int i=0;i<int(s.size());++i){
        if(s[i]=='.')dot.push_back(i);
        if(s[i]=='/')sl=i;
    }
    a=pint(s.substr(0,dot[0]));
    b=pint(s.substr(dot[0]+1,dot[1]-dot[0]-1));
    c=pint(s.substr(dot[1]+1,dot[2]-dot[1]-1));
    d=pint(s.substr(dot[2]+1,(sl?sl-dot[2]-1:int(s.size())-dot[2]-1)));
    if(sl)mask=pint(s.substr(sl+1,int(s.size())-sl-1));
    else mask=-1;
}

#define uint unsigned int
void parse(uint a,uint b,uint c,uint d,uint &val){
    val=(a<<24)|(b<<16)|(c<<8)|d;
}

void build(node *&now,int dep,uint val,char type,int mask){
    if(!now)now=new node();
    if(dep==mask){
        // cout<<"at "<<now<<" "<<dep<<" "<<type<<endl;
        if(type=='+')++now->wh;
        else ++now->bl;
        now->pull();
        return;
    }
    build(now->ch[!!(val&(1<<(31-dep)))],dep+1,val,type,mask);
    now->pull();
}

vector<pair<uint,int>> ans;

void go(node *now,int dep,uint val){
    if(!now)return;
    if(now->wh && now->sbl)no();
    if(now->bl && now->swh)no();
    if(now->sbl && !now->swh){
        ans.emplace_back(val,dep);
        return;
    }
    if(now->swh && !now->sbl)return;
    go(now->ch[0],dep+1,val);
    go(now->ch[1],dep+1,val|(1ull<<(31-dep)));
}

void parse(uint val,int mask){
    int a=(val>>24)&255;
    int b=(val>>16)&255;
    int c=(val>>8)&255;
    int d=(val>>0)&255;
    cout<<a<<"."<<b<<"."<<c<<"."<<d<<"/"<<mask<<'\n';
}

int main(){
    int n; cin>>n;
    while(n--){
        string s; cin>>s;
        int a,b,c,d,mask;
        parse(s.substr(1,s.size()-1),a,b,c,d,mask);
        if(mask==-1)mask=32;
        uint val;
        parse(a,b,c,d,val);
        // cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<val<<endl;
        build(root,0,val,s[0],mask);
    }
    go(root,0,0);
    cout<<ans.size()<<endl;
    for(auto p:ans){
        parse(p.first,p.second);
    }
}
