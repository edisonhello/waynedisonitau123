#include<bits/stdc++.h>
using namespace std;
#define ld long double

const ld eps=;

struct node{
    node *l,*r;
    ld v[2][3],mx;
    node():l(0),r(0){ v[0][0]=1; v[0][1]=0; v[0][2]=0; v[1][0]=1; v[1][1]=0; v[1][2]=0; mx=0; }
    void addtag(int who,int type,ld val){
        if(type==0){
            v[who][0]*=val;
            v[who][1]*=val;
            v[who][2]*=val;
            mx=v[0][2]+v[1][2];
        }
        else{
            v[who][1]+=val;
            v[who][2]+=val;
            mx=v[0][2]+v[1][2];
        }
    }
    void push(){

    }
    void pull(){
        v[2]=max(l->v[2],r->v[2]);
    }
} *root;

#define mid ((l+r)>>1)
void build(node *now,int l,int r){
    if(l==r){
        // do something
        return;
    }
    build(now->l=new node(),l,mid);
    build(now->r=new node(),mid+1,r);
    now->pull();
}

void modify(node *now,int l,int r,int ml,int mr,int who,int type,ld val){ // 0 for x, 1 for +
    if(mr<l || r<ml)return;
    if(ml<=l && r<=mr){
        now->addtag(who,type,val);
        return;
    }
    now->push();
    modify(now->l,l,mid,ml,mr,who,type,val);
    modify(now->r,mid+1,r,ml,mr,who,type,val);
    now->pull();
}

int query(node *now,int l,int r){
    if(l==r){
        return l;
    }
    now->push();
    if(same(now->l->v[2],now->r->v[2]))return query(now->l,l,mid);
    if(now->l->v[2]>=now->r->v[2])return query(now->l,l,mid);
    return query(now->r,mid+1,r);
}
