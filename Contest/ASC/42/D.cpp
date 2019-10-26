#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

vector<int> g[maxn];
int dep[maxn], p[20][maxn];
int nt, in[maxn], out[maxn];

void dfs(int now, int pa) {
    in[now] = ++nt;
    p[0][now] = pa;
    for (int i = 1; i < 20; ++i) p[i][now] = p[i - 1][p[i - 1][now]];
    for (int i : g[now]) if (i != pa) {
        dep[i] = dep[now] + 1;
        dfs(i, now);
    }
    out[now] = nt;
}

int get_lca(int pa, int pb) {
    if (pa == pb) return pa;
    if (dep[pa] > dep[pb]) swap(pa, pb);
    for (int i = 19; i >= 0; --i) if ((dep[pb] - dep[pa]) & (1 << i)) {
        pb = p[i][pb];
    }
    if (pa == pb) return pa;
    for (int i = 19; i >= 0; --i) if (p[i][pa] != p[i][pb]) {
        pa = p[i][pa];
        pb = p[i][pb];
    }
    return p[0][pa];
}

int is_anc(int pa, int ch) {
    return in[pa] <= in[ch] && out[ch] <= out[pa];
}

int solve(int root, int u, int v) {
    return get_lca(root, u) ^ get_lca(u, v) ^ get_lca(root, v);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while (cin >> n) {
        if (n == 0) break;
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        nt = 0;
        dfs(1, 0);

        int nowroot = 1;

        int q; cin >> q; while (q--) {
            char ch; cin >> ch;
            if (ch == '!') {
                cin >> nowroot;
            } else {
                int u, v; cin >> u >> v;
                cout << solve(nowroot, u, v) << '\n';
            }
        }
        for (int i = 1; i <= n; ++i) g[i].clear();
    }
}
