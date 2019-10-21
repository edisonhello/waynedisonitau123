#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
vector<pair<int, int>> g[kN];
vector<int> bg[kN];
int dfn[kN], low[kN], bcc[kN], uf[kN], fz[kN], tk, sz;
bool ins[kN], cut[kN];
stack<int> stk;

int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
}

void Merge(int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (fz[x] > fz[y]) swap(x, y);
    uf[x] = y;
    fz[y] += fz[x];
}

void Dfs(int x, int p) {
    dfn[x] = low[x] = tk++;
    int ch = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, e = g[x][i].second;
        if (u == p) continue;
        if (!ins[e]) {
            stk.push(e);
            ins[e] = true;
        }
        if (~dfn[u]) {
            low[x] = min(low[x], dfn[u]);
            continue;
        }
        ch += 1;
        Dfs(u, x);
        low[x] = min(low[x], low[u]);
        if (low[u] >= dfn[x]) {
            cut[x] = true;
            while (true) {
                int z = stk.top(); stk.pop();
                bcc[z] = sz;
                if (z == e) break;
            }
            sz++;
        }
    }
    if (ch == 1 && p == -1) cut[x] = false;
}

int main() {
    int n, tc = 0; 
    while (scanf("%d", &n) != EOF) {
        if (!n) break;
        vector<int> ds;
        vector<pair<int, int>> ed;
        for (int i = 0; i < n; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            ds.push_back(u);
            ds.push_back(v);
            ed.emplace_back(u, v);
            ins[i] = false;
        }

        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

        for (int i = 0; i < n; ++i) {
            int u = lower_bound(ds.begin(), ds.end(), ed[i].first) - ds.begin();
            int v = lower_bound(ds.begin(), ds.end(), ed[i].second) - ds.begin();
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
        int m = n;
        n = (int)ds.size();
        for (int i = 0; i < n; ++i) {
            sort(g[i].begin(), g[i].end());
            g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
            cut[i] = false;
        }
        sz = tk = 0;
        for (int i = 0; i < n; ++i) {
            dfn[i] = -1;
            uf[i] = i;
            fz[i] = 1;
        }
        Dfs(0, -1);
        int ans1 = 0;
        long long ans2 = 1;
        if (sz == 1) {
            ans1 = 2;
            ans2 = 1LL * n * (n - 1) / 2;
        } else {
            for (int i = 0; i < n; ++i) {
                if (cut[i]) continue;
                for (int j = 0; j < (int)g[i].size(); ++j) {
                    int u = g[i][j].first;
                    if (cut[u]) continue;
                    Merge(i, u);
                }
            }        
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < (int)g[i].size(); ++j) {
                    int u = g[i][j].first;
                    if (Find(i) == Find(u)) continue;
                    bg[Find(u)].push_back(Find(i));
                    bg[Find(i)].push_back(Find(u));
                }
            }
            for (int i = 0; i < n; ++i) {
                sort(bg[i].begin(), bg[i].end());
                bg[i].resize(unique(bg[i].begin(), bg[i].end()) - bg[i].begin());
            }
            for (int i = 0; i < n; ++i) {
                if (bg[i].size() == 1) {
                    assert(!cut[i]);
                    ans2 *= fz[i];
                    ans1 += 1;
                }
            }
        }
        printf("Case %d: %d %lld\n", ++tc, ans1, ans2);
        for (int i = 0; i < n; ++i) g[i].clear(), bg[i].clear();
    }
    return 0;
}
