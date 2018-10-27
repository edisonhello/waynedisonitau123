#include<bits/stdc++.h>
using namespace std;

struct cube{
    int x1,x2,y1,y2;
    void jizz(){
        swap(x1,y1);
        swap(x2,y2);
    }
};



struct segtree{
    struct node{
        node *l,*r;
        int mx,tag;
        node():l(0),r(0),mx(0),tag(0){}
        void pull(){ mx=max(l->mx,r->mx); }
        void push(){ l->addtag(tag); r->addtag(tag); tag=0; }
        void addtag(int x){ mx=max(mx,x); tag=max(tag,x); }
    } *root,pool[20000];
    int ptr,N;

    segtree(){
        root=0;
        ptr=0;
        N=0;
    }

    node *gnode(){
        pool[ptr].l=0;
        pool[ptr].r=0;
        pool[ptr].mx=0;
        pool[ptr].tag=0;
        return &pool[ptr++];
    }
    
    void init(int x){
        N=x;
        ptr=0;
        build(root=gnode(),0,N-1);
    }
#define mid ((l+r)>>1)
    void build(node *now,int l,int r){
        if(l==r){
            now->mx=0;
            return;
        }
        build(now->l=gnode(),l,mid);
        build(now->r=gnode(),mid+1,r);
        now->pull();
    }
    void modify(node *now,int l,int r,int ml,int mr,int x){
        if(ml<=l && r<=mr){
            now->addtag(x);
            return;
        }
        if(r<ml || mr<l)return;
        now->push();
        modify(now->l,l,mid,ml,mr,x);
        modify(now->r,mid+1,r,ml,mr,x);
        now->pull();
    }
    void modify(int l,int r,int x){
        modify(root,0,N-1,l,r,x);
    }
    int query(node *now,int l,int r,int ql,int qr){
        if(qr<l || r<ql)return 0;
        if(ql<=l&&r<=qr)return now->mx;
        now->push();
        return max(query(now->l,l,mid,ql,qr),query(now->r,mid+1,r,ql,qr));
    }
    int query(int l,int r){ return query(root,0,N-1,l,r); }
} seg;

vector<cube> v;



int meow(){
    sort(v.begin(),v.end(),[&](const cube &a,const cube &b){ return a.y1<b.y1; });
    // cout<<"in meow"<<endl;
    // cout<<"from: "<<endl;
    // for(auto &c:v)cout<<c.x1<<" "<<c.y1<<" "<<c.x2<<" "<<c.y2<<endl;
    vector<int> xs(v.size()<<1); int ptr=0;
    for(auto &c:v)xs[ptr++]=c.x1,xs[ptr++]=c.x2;
    sort(xs.begin(),xs.end());
    xs.resize(unique(xs.begin(),xs.end())-xs.begin());
    // cout<<"xs: "; for(int i:xs)cout<<i<<" "; cout<<endl;
    seg.init(xs.size());
    int rt=0;
    for(auto &c:v){
        int L=lower_bound(xs.begin(),xs.end(),c.x1)-xs.begin();
        int R=lower_bound(xs.begin(),xs.end(),c.x2)-xs.begin()-1;
        // cout<<"LR: "<<L<<" "<<R<<" "<<endl;
        int res=seg.query(L,R);
        int drop=c.y1-res;
        if(drop)++rt;
        // cout<<"drop: "<<drop<<endl;
        c.y1-=drop; c.y2-=drop;
        seg.modify(L,R,c.y2);
    }
    // cout<<"rt: "<<rt<<endl;
    // cout<<"to: "<<endl;
    // for(auto &c:v)cout<<c.x1<<" "<<c.y1<<" "<<c.x2<<" "<<c.y2<<endl;
    return rt;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ts; cin>>ts; while(ts--){
        int n; cin>>n;
        v.clear(); v.resize(n);
        for(auto &c:v)cin>>c.x1>>c.y1>>c.x2>>c.y2;
        int cnt=0;
        while(1){
            int mv=0;
            mv+=meow();
            for(auto &c:v)c.jizz();
            ++cnt;
            if(!mv)break;
        }
        if(cnt&1)for(auto &c:v)c.jizz();
        int xx=0,yy=0;
        for(auto &c:v)xx=max(xx,c.x2),yy=max(yy,c.y2);
        cout<<xx<<" "<<yy<<endl;
    }
}
