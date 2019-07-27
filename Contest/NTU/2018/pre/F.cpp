#include<bits/stdc++.h>
using namespace std;
// #define int long long

const int mod=1000000007;

vector<int> operator*(const vector<int> &a,const vector<int> &b){
    // cout<<"pol pro asz, bsz: "<<a.size()<<" and "<<b.size()<<endl;
    vector<int> rt(a.size()+b.size()-1);
    for(int i=0;i<int(a.size());++i){
        for(int j=0;j<int(b.size());++j){
            rt[i+j]+=1ll*a[i]*b[j]%mod;
            if(rt[i+j]>=mod)rt[i+j]-=mod;
        }
    }
    for(int i=int(rt.size())-1;i>=16;--i)rt[i-15]+=rt[i],rt[i-15]-=(rt[i-15]>=mod?mod:0);
    // for(int i=0;i<min(16,int(rt.size()));++i)if(rt[i]>=mod)rt[i]-=mod;
    if(rt.size()>16)rt.resize(16);
    return rt;
}

struct node{
    node *l,*r;
    vector<int> v;
    node():l(0),r(0),v(1,1){ }
} *root;

#define mid ((l+r)>>1)

void build(node *now,int l,int r){
    if(l==r)return;
    build(now->l=new node(),l,mid);
    build(now->r=new node(),mid+1,r);
}

void modify(node *now,int l,int r,int x,vector<int> &pol){
    if(l==r){
        now->v=pol;
        return;
    }
    if(x<=mid)modify(now->l,l,mid,x,pol);
    else modify(now->r,mid+1,r,x,pol);
    now->v=now->l->v*now->r->v;
}

vector<int> query(node *now,int l,int r,int ql,int qr){
    if(qr<l || r<ql)return vector<int>(1,1);
    if(ql<=l&&r<=qr)return now->v;
    return query(now->l,l,mid,ql,qr)*query(now->r,mid+1,r,ql,qr);
}

int fill1021(const vector<int> &pol){
    int rt=0;
    int pw=1;
    for(int i=0;i<int(pol.size());++i){
        rt+=1ll*pol[i]*pw%mod;
        pw=1ll*pw*1021%mod;
        if(rt>=mod)rt-=mod;
    }
    return rt;
}

int pw(int b,int n,int m,int a=1){
    while(n){
        if(n&1)a=1ll*a*b%mod;
        b=1ll*b*b%mod; n>>=1;
    } return a;
}

int inv(int x){ return pw(x,mod-2,mod); } 

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n,q; cin>>n>>q;
    string s; cin>>s; s="z"+s;
    build(root=new node(),1,n);
    for(int i=1;i<=n;++i){
        // cout<<"adding "<<i<<endl;
        int di=-1;
        if(s[i]>='0' && s[i]<='9')di=s[i]-'0';
        else di=s[i]-'A'+10;
        vector<int> tpol(di+1,0);
        tpol[0]=tpol[di]=1;
        modify(root,1,n,i,tpol);
    }
    while(q--){
        int com; cin>>com;
        if(com==1){
            int x; char c; cin>>x>>c;
            int di=-1;
            s[x]=c;
            if(s[x]>='0' && s[x]<='9')di=s[x]-'0';
            else di=s[x]-'A'+10;
            vector<int> tpol(di+1,0);
            tpol[0]=tpol[di]=1;
            modify(root,1,n,x,tpol);
        }
        else{
            int l,r; cin>>l>>r;
            cout<<(fill1021(query(root,1,n,l,r))-1+mod)%mod<<'\n';
        }
    }
}
