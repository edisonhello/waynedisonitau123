#include<bits/stdc++.h>
using namespace std;

int bit[300005];

void add(int x,int v){
    ++x;
    for(;x;x-=x&-x)bit[x]+=v;
}
int query(int x,int v=0){
    ++x;
    for(;x<300005;x+=x&-x)v+=bit[x];
    return v;
}

const int maxn = 3e5 + 5;
int st[maxn * 4], tg[maxn * 4], a[maxn];

void build(int l, int r, int o = 0) {
    if (r - l == 1) return st[o] = a[l], void();
    build(l, (l + r) >> 1, o * 2 + 1);
    build((l + r) >> 1, r, o * 2 + 2);
    st[o] = min(st[o * 2 + 1], st[o * 2 + 2]);
    // cout<<"st of "<<l<<" to "<<r<<" is "<<st[o]<<endl;
}

void push(int o) {
    if (tg[o] == 0) return;
    st[o * 2 + 1] += tg[o], tg[o * 2 + 1] += tg[o];
    st[o * 2 + 2] += tg[o], tg[o * 2 + 2] += tg[o];
    tg[o] = 0;
}

void modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (r - l > 1) push(o);
    if (l >= ql && r <= qr) {
        st[o] += v;
        tg[o] += v;
        return;
    }
    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
    st[o] = min(st[o * 2 + 1], st[o * 2 + 2]);
}

int find(int l, int r, int o = 0) {
    if (r - l == 1) return l;
    push(o);
    // cout<<"find "<<l<<" to "<<r<<" right min: "<<st[o*2+2]<<endl;
    if (st[o * 2 + 2] < 2) return find((l + r) >> 1, r, o * 2 + 2);
    else return find(l, (l + r) >> 1, o * 2 + 1);
}
 

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,q; cin>>n>>q;
    string s; cin>>s;
    set<int> r,ll;
    for(int i=0;i<n;++i)if(s[i]==')')r.insert(i);
    // for(int i=0;i<n;++i)if(s[i]=='(')add(i,1);
    for(int i=0;i<n;++i){
        if(s[i]=='(')++a[i];
        else --a[i];
        if(i)a[i]+=a[i-1];
        // cout<<"a["<<i<<"]: "<<a[i]<<endl;
    }
    build(0,n);
    for(int i=0;i<n-1;++i)if(s[i]=='(' && s[i+1]=='(')ll.insert(i);
    auto flip=[&](const int pos)->void{
        if(s[pos]=='('){
            if(pos && s[pos-1]=='(')ll.erase(pos-1);
            if(pos<n-1 && s[pos+1]=='(')ll.erase(pos);
            s[pos]=')';
            // add(pos,-2);
            modify(0,n,pos,n,-2);
            r.insert(pos);
        }
        else{
            r.erase(pos);
            // add(pos,2);
            modify(0,n,pos,n,2);
            s[pos]='(';
            if(pos && s[pos-1]=='(')ll.insert(pos-1);
            if(pos<n-1 && s[pos+1]=='(')ll.insert(pos);
        }
    };
    while(q--){
        int t; cin>>t; --t;
        int cs=(s[t]=='(');
        flip(t);
        // cout<<"opp s: "<<s<<endl;
        if(cs==1){
            int x=*r.begin();
            cout<<x+1<<'\n';
            flip(x);
        }
        else{
            // int x=(*ll.lower_bound(t-1))+1;
            int x=find(0,n)+1;
            // cout<<"query: "<<query(t+1)<<endl;
            // if(query(t)<0)x=(*ll.begin())+1;
            // else x=t;
            cout<<x+1<<'\n';
            flip(x);
        }
        // cout<<"now s: "<<s<<endl;
    }
}
