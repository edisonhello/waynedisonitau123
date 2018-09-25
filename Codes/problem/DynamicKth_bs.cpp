#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], ans[maxn], tmp[maxn];

struct query { int op, l, r, k, qid; };

struct fenwick {
    int dat[maxn];
    void init() { memset(dat, 0, sizeof(dat)); }
    void add(int p, int v) { for (; p < maxn; p += p & -p) dat[p] += v; }
    int qry(int p, int v = 0) { for (; p; p -= p & -p) v += dat[p]; return v; }
} bit;

void bs(vector<query> &qry, int l, int r) {
    if (l == r) {
        for (int i = 0; i < qry.size(); ++i) {
            if (qry[i].op == 3) ans[qry[i].qid] = l;
        }
        return;
    }
    if (qry.size() == 0) return;
    int m = l + r >> 1;
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 1 && qry[i].r <= m) bit.add(qry[i].l, 1);
        else if (qry[i].op == 2 && qry[i].r <= m) bit.add(qry[i].l, -1);
        else if (qry[i].op == 3) tmp[qry[i].qid] += bit.qry(qry[i].r) - bit.qry(qry[i].l - 1);
    }    
    vector<query> ql, qr;
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 3) {
            if (qry[i].k - tmp[qry[i].qid] > 0) qry[i].k -= tmp[qry[i].qid], qr.push_back(qry[i]);
            else ql.push_back(qry[i]);
            tmp[qry[i].qid] = 0;
            continue;
        }
        if (qry[i].r <= m) ql.push_back(qry[i]);
        else qr.push_back(qry[i]);
    }
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 1 && qry[i].r <= m) bit.add(qry[i].l, -1);
        else if (qry[i].op == 2 && qry[i].r <= m) bit.add(qry[i].l, 1);
    }    
    bs(ql, l, m), bs(qr, m + 1, r);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, q; scanf("%d %d", &n, &q);
        vector<query> qry;
        vector<int> ds;
        bit.init();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i); ds.push_back(a[i]);
            qry.push_back({ 1, i, a[i], -1, -1 });
        }
        int qid = 0;
        for (int i = 0; i < q; ++i) {
            int t; scanf("%d", &t);
            if (t == 1) {
                int l, r, k; scanf("%d %d %d", &l, &r, &k); 
                qry.push_back({ 3, l, r, k, qid }); ++qid;
            }
            if (t == 2) {
                int c, v; scanf("%d %d", &c, &v);
                ds.push_back(v);
                qry.push_back({ 2, c, a[c], -1, -1 });
                qry.push_back({ 1, c, v, -1, -1 });
                a[c] = v;
            }
            if (t == 3) {
                int x, v; scanf("%d %d", &x, &v);
                ans[qid] = -1, ++qid;
            }
        }
        sort(ds.begin(), ds.end()); ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        for (int i = 0; i < qry.size(); ++i) {
            if (qry[i].op == 3) continue;
            qry[i].r = lower_bound(ds.begin(), ds.end(), qry[i].r) - ds.begin();
        }
        bs(qry, 0, ds.size() - 1);
        for (int i = 0; i < qid; ++i) {
            if (ans[i] == -1) puts("7122");
            else assert(ans[i] < ds.size()), printf("%d\n", ds[ans[i]]);
        }
    }
    return 0;
}

