#include <bits/stdc++.h>
using namespace std;
#define int short

const int kN = 2000 + 5;
vector<pair<int, int>> g[kN];
vector<pair<int, int>> ig[kN];
pair<int, int> edg[kN * 2];

vector<pair<int, int>> gglist;
vector<int> gg[kN * 4];
vector<int> igg[kN * 4];

bool vis[kN], vise[kN * 2];
bool v[kN * 4];
vector<int> tp;
int bel[kN * 4];
int oggsz[kN * 4];

void idfs(int now) {
    vis[now] = 1;
    for (auto &p : ig[now]) {
        vise[p.second] = 1;
        if (!vis[p.first]) idfs(p.first);
    }
}

void dfs(int now) {
    vis[now] = 1;
    for (auto &p : g[now]) {
        vise[p.second] = 1;
        if (!vis[p.first]) dfs(p.first);
    }
}

void dfs1(int now) {
    v[now] = 1;
    for (int i : gg[now]) if (!v[i]) dfs1(i);
    tp.push_back(now);
}

void dfs1i(int now, int cc) {
    v[now] = 1;
    bel[now] = cc;
    for (int i : igg[now]) if (!v[i]) dfs1i(i, cc);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n + n; ++i) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v, i);
        ig[v].emplace_back(u, i);
        edg[i] = make_pair(u, v);
    }

    for (int i = 0; i < n + n; ++i) {
        memset(vise, 0, sizeof(vise));
        memset(vis, 0, sizeof(vis));
        idfs(edg[i].first);
        memset(vis, 0, sizeof(vis));
        dfs(edg[i].second);

        for (int j = 0; j < n + n; ++j) if (!vise[j] && i != j) gg[i].push_back(j + n * 2);
    }
    for (int i = 0; i < 4 * n; ++i) oggsz[i] = gg[i].size();
    // for (auto &p : gglist) gg[p.first].push_back(p.second);

    // cout << "gglist: " << endl;
    // for (auto &p : gglist) {
    //     cout << p.first << ' ' << p.second << '\n';
    // }

    auto check = [&] () -> bool {
        for (int i = 0; i < n * 4; ++i) igg[i].clear();
        for (int i = 0; i < n * 4; ++i) {
            for (int j : gg[i]) igg[j].push_back(i);
        }

        tp.clear();
        memset(v, 0, sizeof(v));
        for (int i = 0; i < n * 4; ++i) {
            if (!v[i]) dfs1(i);
        }
        reverse(tp.begin(), tp.end());
        int cc = 0;
        memset(v, 0, sizeof(v));
        for (int i : tp) {
            if (!v[i]) dfs1i(i, ++cc);
        }

        for (int i = 0; i < n * 2; ++i) {
            if (bel[i] == bel[i + n * 2]) return false;
        }
        return true;
    };

    int L = 0, R = n;
    while (L < R) {
        int M = (L + R + 1) >> 1;
        // cout << "checking ans = " << M << endl;
        for (int i = 0; i < 4 * n; ++i) gg[i].resize(oggsz[i]);
        for (int i = 0; i < 2 * M; i += 2) {
            gg[i + n * 2].push_back(i + 1);
            gg[i + 1 + n * 2].push_back(i);
        }
        if (check()) L = M;
        else R = M - 1;
    }

    cout << L << endl;
    return 0;
}

