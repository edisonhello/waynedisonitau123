#pragma GCC optimize("no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

struct command{
    int c,x1,y1,x2,y2;
} cs[100005];
vector<int> xs,ys;

struct {
    struct bit {
        vector<int> b;
        vector<int> ds;
        void addy(int y) {ds.push_back(y);}
        void done() {
            sort(ds.begin(), ds.end());
            ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
            b.resize(ds.size() + 1, 0);
        }
        void add(int p, int v) {
            p = upper_bound(ds.begin(), ds.end(), p) - ds.begin();
            // cout<<"bit add in pos "<<p <<" with value "<<v<<endl;
            for (int i = p; i < b.size(); i += i & -i)
                b[i] += v;
        }
        int query(int p) {
            p = upper_bound(ds.begin(), ds.end(), p) - ds.begin();
            int v = 0;
            for (int i = p; i; i -= i & -i)
                v += b[i];
            // cout<<"query "<<p<<" get " <<v<<endl;
            return v;
        }
    };
    struct node{
        node *l,*r;
        bit bb;
        node():l(0),r(0){}
    } *root,pool[300000 * 4];
    node *gnode(){
        static int ptr=-1;
        return &pool[++ptr];
    }

    void dfs(node *now){
        now->bb.done();
        if(now->l)dfs(now->l),dfs(now->r);
    }
#define mid ((l+r)>>1)
    void build(node *now,int l,int r){
        if(l==r)return;
        build(now->l=gnode(),l,mid);
        build(now->r=gnode(),mid+1,r);
    }
    void modify1(node *now,int l,int r,int x,int y,int v){
        now->bb.addy(y);
        if(l==r)return;
        if(x<=mid)modify1(now->l,l,mid,x,y,v);
        else modify1(now->r,mid+1,r,x,y,v);
    }
    void modify2(node *now,int l,int r,int x,int y,int v){
        now->bb.add(y, v);
        if(l==r)return;
        if(x<=mid)modify2(now->l,l,mid,x,y,v);
        else modify2(now->r,mid+1,r,x,y,v);
    }
    int query(node *now,int l,int r,int ql,int qr,int y){
        if(qr<l || r<ql)return 0;
        if(ql<=l&&r<=qr){
            // cout<<"start query bit at range "<<l<<" "<<r<<" with query "<<ql <<" to "<<qr<<", y limit "<<y<<endl;
            return now->bb.query(y);
        }
        return query(now->l,l,mid,ql,qr,y)+query(now->r,mid+1,r,ql,qr,y);
    }
#undef mid
    void build(){
        build(root=gnode(),0,xs.size()-1);
    }
    int find(int x,int y){
        // cout<<"find "<<x<<" "<<y<<endl;
        int res = query(root,0,xs.size()-1,0,x,y);
        // cout<<"res: "<<res<<endl;
        return res;
    }
    void add1(int x,int y,int v){
        // cout<<"add "<<x<<" "<<y<<" "<<v<<endl;
        modify1(root,0,xs.size()-1,x,y,v);
    }
    void add2(int x,int y,int v){
        // cout<<"add "<<x<<" "<<y<<" "<<v<<endl;
        modify2(root,0,xs.size()-1,x,y,v);
    }
    void dfs(){
        dfs(root);
    }
} point,rec;

int gtx(){
    const int N=4096;
    static char b[N], *p=b, *e=b;
    if(p==e){
        e=b+fread(b,1,N,stdin);
        p=b;
    }
    return *p++;
}
void rit(int &x){
    char c;
    while(c=gtx(), c<'0' || c>'9');
    x=c-'0';
    while(c=gtx(), c>='0' && c<='9')x=x*10+(c&15);
}

int main() {
    int q; rit(q);
    srand(time(0)+clock());
    // int q=100000;
    for(int i=0;i<q;++i){
        int c; rit(c);
        // int c=2;
        if (c == 1) {
            int x, y; rit(x); rit(y);
            cs[i]={c,x,y,0,0};
            xs.push_back(x);
        } else {
            int x1,y1,x2,y2; rit(x1); rit(y1); rit(x2); rit(y2);
            // int x1=rand()%1000000000+1,y1=rand()%1000000000+1,x2=rand()%1000000000+1,y2=rand()%1000000000+1;
            cs[i]={c,x1,y1,x2,y2};
            xs.push_back(x1);
            xs.push_back(x2);
            xs.push_back(x2+1);
        }
    }
    sort(xs.begin(),xs.end());
    xs.resize(unique(xs.begin(),xs.end())-xs.begin());

    point.build();
    rec.build();

    long long ans=0;
    for(int i=0;i<q;++i){
        int c=cs[i].c;
        if(c==1){
            int &x=cs[i].x1,y=cs[i].y1;
            x=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
            // ans+=rec.find(x,y);
            point.add1(x,y,1);
        } else{
            int &x1=cs[i].x1,y1=cs[i].y1,&x2=cs[i].x2,y2=cs[i].y2;
            x1=lower_bound(xs.begin(),xs.end(),x1)-xs.begin();
            x2=lower_bound(xs.begin(),xs.end(),x2)-xs.begin();
            // ans+=point.find(x2,y2)-point.find(x1-1,y2)-point.find(x2,y1-1)+point.find(x1-1,y1-1);
            rec.add1(x1,y1,1);
            rec.add1(x2+1,y1,-1);
            rec.add1(x1,y2+1,-1);
            rec.add1(x2+1,y2+1,1);
        }
        // printf("%lld\n",ans);
    }
    point.dfs();
    rec.dfs();
    for(int i=0;i<q;++i){
        int c=cs[i].c;
        if(c==1){
            int &x=cs[i].x1,y=cs[i].y1;
            ans+=rec.find(x,y);
            point.add2(x,y,1);
        } else{
            int &x1=cs[i].x1,y1=cs[i].y1,&x2=cs[i].x2,y2=cs[i].y2;
            ans+=point.find(x2,y2)-point.find(x1-1,y2)-point.find(x2,y1-1)+point.find(x1-1,y1-1);
            rec.add2(x1,y1,1);
            rec.add2(x2+1,y1,-1);
            rec.add2(x1,y2+1,-1);
            rec.add2(x2+1,y2+1,1);
        }
        printf("%lld\n",ans);
    }
}
