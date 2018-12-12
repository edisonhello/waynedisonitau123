#include<bits/stdc++.h>
using namespace std;

struct data {
    long long mn, mni, pre, sum;
    data():mn(0),mni(-1),pre(0),sum(0){}
    void set(int x,int d) {
        mn = x;
        pre = x;
        sum = d;
    }
    void init(int x){
        mni = x;
        sum = 0;
    }
};
data operator+(const data a,const data b) {
    data r;
    r.pre = a.pre + b.pre;
    r.sum = a.sum + b.sum;
    if (a.mn < a.pre + b.mn) {
        r.mn = a.mn;
        r.mni = a.mni;
    } else {
        r.mn = a.pre + b.mn;
        r.mni = b.mni;
    }
    return r;
}

struct node {
    node *l, *r;
    data v;
    node():l(0),r(0){}
    void pull() {
        v = l->v + r->v;
    }
} *root;

#define mid ((l+r)>>1)
void build(node *now, int l, int r) {
    if (l == r) {
        now->v.init(l);
        return;
    }
    build(now->l = new node(), l, mid);
    build(now->r = new node(), mid + 1, r);
    now->pull();
}

void modify(node *now,int l,int r,int p,int x,int d) {
    if(now==root){
        // printf("modify p = %d, x = %d, d = %d\n", p, x, d);
    }
    if(l==r){
        now->v.set(x,d);
        return;
    }
    if(p<=mid)modify(now->l,l,mid,p,x,d);
    else modify(now->r,mid+1,r,p,x,d);
    now->pull();
}

data query(node *now,int l,int r,int ql,int qr){
    if(ql<=l && r<=qr)return now->v;
    if(qr<=mid)return query(now->l,l,mid,ql,qr);
    if(mid<ql)return query(now->r,mid+1,r,ql,qr);
    return query(now->l,l,mid,ql,qr)+query(now->r,mid+1,r,ql,qr);
}

int ti[300005];
int di[300005];
int tpid[1000006];

int main(){
    set<int> sgts;
    sgts.insert(2000000);
    int cnt = 0;
    build(root = new node(), 0, 1000000);
    int q; scanf("%d\n", &q); while(q--) {
        char c; scanf("%c", &c); 
        auto add = [&](int cnt, int t, int d) -> void{
            tpid[t] = cnt;
            ti[cnt] = t;
            di[cnt] = d;
            auto it = sgts.upper_bound(t);
            int v = d - (*it - t);
            modify(root, 0, 1000000, t, v, d);
            if (it != sgts.begin()) {
                int pt = *prev(it);
                int pi = tpid[pt];
                modify(root, 0, 1000000, pt, di[pi] - (t - pt), di[pi]);
            }
            sgts.insert(t);
        };
        auto rem = [&](int x) -> void{
            int t = ti[x];
            int d = di[x];
            sgts.erase(t);
            auto it = sgts.upper_bound(t);
            // int v = d - (*it - t);
            modify(root, 0, 1000000, t, 0, 0);
            if (it != sgts.begin()) {
                int pt = *prev(it);
                int pi = tpid[pt];
                modify(root, 0, 1000000, pt, di[pi] - (*it - pt), di[pi]);
            }
        };
        ++cnt;
        if (c == '?') {
            int t; scanf("%d\n", &t);
            // printf("? t = %d\n", t);
            auto it = sgts.upper_bound(t);
            // printf("it is %d, t is %d\n", *it, t);
            long long offset = 0;
            // if (tpid[t]) offset = di[tpid[t]];
            if (it == sgts.begin()) puts("0");
            else {
                int pt = *prev(it);
                int pi = tpid[pt];
                // printf("There's prevous at t = %d, pi = %d, ti[pi] = %d\n", pt, pi, ti[pi]);
                // printf("tmp modify: ");
                modify(root, 0, 1000000, ti[pi], di[pi] - (t - ti[pi]), di[pi]);
                data ret = query(root, 0, 1000000, 0, pt - 1);
                int mni = ret.mni;
                // printf("mn = %d, mni = %d\n", ret.mn, mni);
                // if (mni == t) printf("%lld\n", offset);
                printf("%lld\n", max(0ll, query(root, 0, 1000000, mni + 1, t).sum - (t - mni - 1) + offset));
                // printf("reverse tmp: ");
                modify(root, 0, 1000000, ti[pi], di[pi] - (*it - ti[pi]), di[pi]);
            }
        } else if (c == '+') {
            int t, d;
            scanf("%d%d\n", &t, &d);
            // printf("Start add %d %d\n", t, d);
            add(cnt, t, d);
            // printf("After insert\n");
        } else {
            int x;
            scanf("%d\n", &x);
            // printf("Removing x = %d\n", x);
            rem(x);
            // printf("Finish remove\n");
        }
    }
}
