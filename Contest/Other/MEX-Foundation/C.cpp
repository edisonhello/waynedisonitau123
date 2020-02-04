#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;
const int kB = 500;
int fa[kN], val[kN], dep[kN], sz[kN], to[kN], fr[kN], kz[kN], deg[kN], tin[kN], tout[kN];
vector<int> sub[kN];
vector<int> g[kN];
set<pair<int, int>> ch[kN];
vector<pair<int, int>> tch[kN];

void Dfs(int x, int p) {
    fa[x] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    sz[x] = 1;
    to[x] = -1;
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[u] > sz[to[x]]) to[x] = u;
    }
}

void Link(int x, int f) {
    static int tk = 0;
    tin[x] = tk++;
    fr[x] = f;
    if (to[x] != -1) Link(to[x], f);
    for (int u : g[x]) {
        if (u == fa[x] || u == to[x]) continue;
        Link(u, u);
    }
    tout[x] = tk;
}

bool IsAnc(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}

struct SegTree {
    vector<int> st, tg;
    vector<long long> sum;
    int n;

    SegTree() = default;

    SegTree(int n) : n(n) {
        st.resize(n * 4);
        tg.resize(n * 4);
        sum.resize(n * 4);
    }

    void Push(int o, int l, int r) {
        for (int i = 1; i <= 2; ++i) {
            st[o * 2 + i] += tg[o];
            tg[o * 2 + i] += tg[o];
        }
        int m = (l + r) >> 1;
        sum[o * 2 + 1] += 1LL * tg[o] * (m - l);
        sum[o * 2 + 2] += 1LL * tg[o] * (r - m);
        tg[o] = 0;
    }

    void Modify(int l, int r, int ql, int qr, int v, int o = 0) {
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) {
            st[o] += v;
            tg[o] += v;
            sum[o] += 1LL * v * (r - l);
            return;
        }
        Push(o, l, r);
        Modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
        Modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
        st[o] = max(st[o * 2 + 1], st[o * 2 + 2]);
        sum[o] = sum[o * 2 + 1] + sum[o * 2 + 2];
    }

    void Modify(int l, int r, int v) { Modify(0, n, l, r, v); }

    int Query(int l, int r, int p, int o = 0) {
        if (r - l == 1) return st[o];
        Push(o, l, r);
        int m = (l + r) >> 1;
        if (p < m) return Query(l, m, p, o * 2 + 1);
        else return Query(m, r, p, o * 2 + 2);
    }

    long long QuerySum(int l, int r, int ql, int qr, int o = 0) {
        if (l >= qr || ql >= r) return 0LL;
        if (l >= ql && r <= qr) return sum[o];
        int m = (l + r) >> 1;
        Push(o, l, r);
        return QuerySum(l, m, ql, qr, o * 2 + 1) + QuerySum(m, r, ql, qr, o * 2 + 2);
    }

    int Query(int p) { return Query(0, n, p); }
    long long QuerySum(int l, int r) { return QuerySum(0, n, l, r); }

    int FindLast(int l, int r, int p, int o = 0) {
        if (r - l == 1) return l;
        Push(o, l, r);
        int m = (l + r) >> 1;
        if (st[o * 2 + 2] > p) return FindLast(m, r, p, o * 2 + 2);
        else return FindLast(l, m, p, o * 2 + 1);
    }

    int FindLast(int p) { return FindLast(0, n, p); }
};

SegTree st[kN];

int Query(int u) { return st[fr[u]].Query(dep[u] - dep[fr[u]]); }

void Dfs2(int x, int f, int z) {
    tch[x].emplace_back(z, f);
    for (int u : g[x]) {
        if (u == fa[x]) continue;
        Dfs2(u, f, z);
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    Dfs(0, -1);
    Link(0, 0);
    for (int i = 0; i < n; ++i) sub[fr[i]].push_back(i);
    for (int i = 0; i < n; ++i) {
        if (fr[i] == i) {
            sort(sub[i].begin(), sub[i].end(), [&](int u, int v) { return dep[u] < dep[v]; });
            assert(sub[i][0] == i);
            st[i] = SegTree(sub[i].size());
        }
    }
    vector<int> heavy;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > kB) {
            for (int u : g[i]) {
                if (u == fa[i]) continue;
                ch[i].insert(make_pair(0, u));
                Dfs2(u, u, i);
            }
            heavy.push_back(i);
        }
    }
    int q; scanf("%d", &q);
    long long sum = 0;
    int cnt = 0;
    while (q--) {
        static char cd[2];
        int v;
        scanf("%s%d", cd, &v);
        v--;
        if (cd[0] == '+') {
            sum += dep[v];
            cnt += 1;
            for (auto p : tch[v]) {
                int f = p.first, z = p.second;
                ch[f].erase(make_pair(val[z], z));
                val[z] += 2;
                ch[f].insert(make_pair(val[z], z));
            }
            while (v >= 0) {
                int f = fr[v]; 
                st[f].Modify(0, dep[v] - dep[f] + 1, 2);
                v = fa[f];
            }
        } else {
            sum -= dep[v];
            cnt -= 1;
            for (auto p : tch[v]) {
                int f = p.first, z = p.second;
                ch[f].erase(make_pair(val[z], z));
                val[z] -= 2;
                ch[f].insert(make_pair(val[z], z));
            }
            while (v >= 0) {
                int f = fr[v]; 
                st[f].Modify(0, dep[v] - dep[f] + 1, -2);
                v = fa[f];
            }
        }
        int r = 0;
        long long o = 0;
        while (true) {
            int z = -1;
            if (deg[r] > kB) {
                auto it = ch[r].rbegin();
                if (it->first > cnt) z = it->second;
            } else {
                for (int u : g[r]) {
                    if (u == fa[r]) continue;
                    if (Query(u) > cnt) z = u;
                }
            }
            if (z == -1) break;
            if (z == to[r]) {
                int g = st[fr[z]].FindLast(cnt);
                o += st[fr[z]].QuerySum(dep[z] - dep[fr[z]], g + 1);
                r = sub[fr[z]][g];
            } else {
                o += Query(z);
                r = z;
            }
        }
        printf("%lld\n", sum - o + 1LL * cnt * dep[r]);
    }
}

