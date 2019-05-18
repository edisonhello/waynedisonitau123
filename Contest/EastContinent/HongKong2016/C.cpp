#include<bits/stdc++.h>
using namespace std;

struct node{
    node *l,*r;
    int mn,mx;
    void pull(){ mn=min(l->mn,r->mn); mx=max(l->mx,r->mx); }
    node(int v=0):l(0),r(0),mn(v),mx(v){}
} *roota,*rootb;

// int x[50005][2],y[50005][  2][      2][      2];
//               [    i][a/b][pre/suf][min/max];
int a[50005],b[50005];

#define mid ((l+r)>>1)
void build(node *now,int l,int r,int *a){
    if(l==r){
        now->mn=now->mx=a[l];
        return;
    }
    build(now->l=new node(),l,mid,a);
    build(now->r=new node(),mid+1,r,a);
    now->pull();
}

int qmin(node *now,int l,int r,int ql,int qr){
    if(qr<l || r<ql)return 1e9;
    if(ql<=l && r<=qr)return now->mn;
    return min(qmin(now->l,l,mid,ql,qr),qmin(now->r,mid+1,r,ql,qr));
}

int qmax(node *now,int l,int r,int ql,int qr){
    if(qr<l || r<ql)return 0;
    if(ql<=l && r<=qr)return now->mx;
    return max(qmax(now->l,l,mid,ql,qr),qmax(now->r,mid+1,r,ql,qr));
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i]>>b[i];
    build(roota=new node(),1,n,a);
    build(rootb=new node(),1,n,b);
    for(int clcm=n-1;clcm>=0;--clcm){
        int cgcd=n-1-clcm;
        if(clcm>=2){
            cout<<qmax(roota,1,n,1,n)<<" "<<qmax(rootb,1,n,1,n)<<" ";
        }
        else if(clcm==1){
            double val=-1;
            int aa=-1,bb=-1;
            for(int i=1;i<=n;++i){
                int aaa=max(a[i],min(qmin(roota,1,n,1,i-1),qmin(roota,1,n,i+1,n)));
                int bbb=max(b[i],min(qmin(rootb,1,n,1,i-1),qmin(rootb,1,n,i+1,n)));
                double vvv=log(double(2))*aaa+log(double(3))*bbb;
                if(vvv>val){
                    val=vvv;
                    aa=aaa; bb=bbb;
                }
            }
            cout<<aa<<" "<<bb<<" ";
        }
        else{
            cout<<qmin(roota,1,n,1,n)<<" "<<qmin(rootb,1,n,1,n)<<" ";
        }

        if(cgcd>=2){
            cout<<qmin(roota,1,n,1,n)<<" "<<qmin(rootb,1,n,1,n)<<"\n";
        }
        else if(cgcd==1){
            double val=1e9;
            int aa=-1,bb=-1;
            for(int i=1;i<=n;++i){
                int aaa=min(a[i],max(qmax(roota,1,n,1,i-1),qmax(roota,1,n,i+1,n)));
                int bbb=min(b[i],max(qmax(rootb,1,n,1,i-1),qmax(rootb,1,n,i+1,n)));
                double vvv=log(double(2))*aaa+log(double(3))*bbb;
                if(vvv<val){
                    val=vvv;
                    aa=aaa; bb=bbb;
                }
            }
            cout<<aa<<" "<<bb<<"\n";
        }
        else{
            cout<<qmax(roota,1,n,1,n)<<" "<<qmax(rootb,1,n,1,n)<<"\n";
        }
    }
}
