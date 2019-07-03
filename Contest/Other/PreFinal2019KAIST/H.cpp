#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define tm hao
using namespace std;
 
const int maxn = 1e5 + 5;
const int maxq = 2e5 + 5;
int n, a[maxn], b[maxn], c[maxn];
int dep[maxn], u[maxq], x[maxq];
int prv[maxn][20], sz[maxn], head[maxn];
int tin[maxn], tout[maxn];
long long ans[maxq];
vector<int> g[maxn], qr;
vector<int> ds;
 
void dfs(int x, int p) {
    static int tk = 0;
    dep[x] = ~p ? dep[p] + 1 : 0;
    tin[x] = tk++;
 
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
 
        dfs(u, x);
    }
    tout[x] = tk;
}
 
struct line {
    int a, b;
    line(int a = 0, int b = 0) : a(a), b(b) {}
    long long operator()(int x) const {
        return a * 1ll * x + b;
    }
};
 
line ln[maxn];
 
int stamp;
int st[maxn * 4], tg[maxn * 4], tm[maxn * 4];
 
void push(int o) {
    if (tm[o] != stamp || tg[o] == -1) return;
    st[o * 2 + 1] = tg[o];
    tg[o * 2 + 1] = tg[o];
    tm[o * 2 + 1] = stamp;
    st[o * 2 + 2] = tg[o];
    tg[o * 2 + 2] = tg[o];
    tm[o * 2 + 2] = stamp;
    tg[o] = -1;
}
 
void modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        st[o] = v;
        tg[o] = v;
        tm[o] = stamp;
        return;
    }
 
    push(o);
 
    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
}
 
int query(int l, int r, int p, int o = 0) {
    if (r - l == 1)
        return st[o];
    
    push(o);
 
    if (p < (l + r) >> 1)
        return query(l, (l + r) >> 1, p, o * 2 + 1);
    else
        return query((l + r) >> 1, r, p, o * 2 + 2);
}
 
void insert_vertex(int v) {
    modify(0, n, tin[v], tout[v], v);
}
 
int find_parent(int v) {
    return query(0, n, tin[v]);
}
 
bool beat(line l1, line l2, line l3) {
    return (l2.b - l3.b) * 1ll * (l2.a - l1.a) >= (l1.b - l2.b) * 1ll * (l3.a - l2.a);
    // return 1.0 * (l1.b - l2.b) / (l2.a - l1.a) <= 1.0 * (l3.b - l2.b) / (l2.a - l3.a);
}
 
 
void dvcq(int l, int r, const vector<int> &v, const vector<int> &qr) {
    if (v.empty() || qr.empty()) return;
    // printf("l = %d r = %d\n", l, r);
    int m = (l + r) >> 1;
    // printf("m = %d\n", m);
    ++stamp;
 
    insert_vertex(1);
    sz[0] = 0;
    sz[1] = 1;
    head[1] = 1;
    prv[1][0] = 0;
    
 
    for (int i = 0; i < (int)v.size(); ++i) {
        int j = v[i];
        if (c[j] >= ds[m]) {
            int k = head[find_parent(j)];
            // printf("j = %d k = %d\n", j, k);
            if (sz[k] >= 1 && ln[k].a == ln[j].a && ln[k].b >= ln[j].b) k = prv[k][0];
            if (sz[k] == 0 || ln[k].a != ln[j].a) {
                for (int d = 19; d >= 0; --d) {
                    if (sz[k] - (1 << d) <= 1) continue;
                    int pk = prv[k][d];
                    line l1 = ln[prv[pk][0]];
                    line l2 = ln[pk];
                    if (beat(l1, l2, ln[j])) k = pk;
                }
                while (sz[k] >= 2) {
                   line l1 = ln[prv[k][0]];
                   line l2 = ln[k];
                   if (l2.a != ln[j].a && beat(l1, l2, ln[j])) k = prv[k][0];
                   else break;
                }
                /* if (sz[k] >= 2) {
                    line l1 = ln[prv[k][0]];
                    line l2 = ln[k];
                    if (beat(l1, l2, ln[j])) 
                        k = prv[k][0];
                } */
            }
            // printf("j = %d k = %d\n", j, k);
            if (sz[k] >= 1 && ln[k].a == ln[j].a && ln[k].b <= ln[j].b) {
                sz[j] = sz[k];
                head[j] = k;
            } else {
                sz[j] = sz[k] + 1;
                head[j] = j;
                prv[j][0] = k;
                for (int p = 1; (1 << p) <= sz[j]; ++p)
                    prv[j][p] = prv[prv[j][p - 1]][p - 1];
                // printf("prv[%d] = %d\n", j, prv[j]);
            }
                insert_vertex(j);
        }
    }
 
 
    for (int i = 0; i < (int)qr.size(); ++i) {
        int j = qr[i];
        if (x[j] > ds[m]) continue;
        // printf("j = %d\n", j);
        int v = head[find_parent(u[j])];
        int g = 0;
        for (int d = 19; d >= 0; --d) {
            if (sz[v] - (1 << d) <= 0) continue;
            if (ln[prv[v][d]](x[j]) > ln[prv[prv[v][d]][0]](x[j]))
                v = prv[v][d];
        }
        // printf("v = %d\n", v);
        // printf("v = %d\n", v);
        /* while (sz[head[v]] >= 2) {
            // printf("123\n");
            line l1 = ln[prv[head[v]]];
            line l2 = ln[head[v]];
            if (l1(x[j]) <= l2(x[j])) head[v] = prv[head[v]];
            else break;
        } */
 
        // printf("%d\n", head[v]);
        // printf("j = %d update = %d\n", j, head[v]);
        ans[j] = min(ans[j], ln[v](x[j]));
        ans[j] = min(ans[j], ln[prv[v][0]](x[j]));
    }
 
    // printf("here\n");
 
    vector<int> lv, rv;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (c[v[i]] >= ds[m])
            rv.push_back(v[i]);
        else
            lv.push_back(v[i]);
    }
 
    vector<int> lq, rq;
    for (int i = 0; i < (int)qr.size(); ++i) {
        if (x[qr[i]] > ds[m])
            rq.push_back(qr[i]);
        else
            lq.push_back(qr[i]);
    }
 
    if (l == r) return;
    // printf("here\n");
    dvcq(l, m, lv, lq);
    dvcq(m + 1, r, rv, rq);
}
 
int main() {
    int q; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    ds = vector<int>(c + 1, c + n + 1);
 
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        // --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    ln[0] = line(1000000000, 1000000000);
    for (int i = 1; i <= n; ++i) ln[i] = line(b[i], a[i]);
 
    dfs(1, -1);
 
    vector<int> qr;
    for (int i = 0; i < q; ++i) {
        scanf("%d%d", &u[i], &x[i]);
        ds.push_back(x[i]);
        ans[i] = a[1] + b[1] * 1ll * x[i];
        qr.push_back(i);
    }
 
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
 
    vector<int> v(n - 1);
    iota(v.begin(), v.end(), 2);
    sort(v.begin(), v.end(), [&](int i, int j) {
        return dep[i] < dep[j];
    });
    sort(qr.begin(), qr.end(), [&](int i, int j) {
        return x[i] < x[j];
    });
 
    dvcq(0, ds.size() - 1, v, qr);
    for (int i = 0; i < q; ++i) printf("%lld\n", ans[i]);
    return 0;
}
