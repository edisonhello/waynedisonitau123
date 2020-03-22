#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 200;

struct MaxClique {
    vector<int> deg;
    vector<pair<int, int>> ed;
    vector<bitset<kN>> adj;
    bitset<kN> ans;
    int n;

    MaxClique(int n) : n(n), deg(n, 0), adj(n) {}

    void AddEdge(int u, int v) {
        deg[u]++;
        deg[v]++;
        ed.emplace_back(u, v);
    }

    vector<int> operator()() {
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int u, int v) { return deg[u] < deg[v]; });
        vector<int> id(n);
        for (int i = 0; i < n; ++i) id[ord[i]] = i;
        for (auto e : ed) {
            int u = id[e.first];
            int v = id[e.second];
            adj[u].set(v);
            adj[v].set(u);
        }
        bitset<kN> r, p;
        for (int i = 0; i < n; ++i) p.set(i);
        Dfs(r, p);
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (ans[i]) res.push_back(ord[i]);
        }
        return res;
    }

    void Dfs(bitset<kN> r, bitset<kN> p) {
        if (p.count() == 0) {
            if (r.count() > ans.count()) ans = r;
            return;
        }
        if (clock() > 1.90 * CLOCKS_PER_SEC) return;
        if ((r | p).count() <= ans.count()) return;
        int x = p._Find_first();
        bitset<kN> c = p & ~adj[x];
        for (int i = c._Find_first(); i < kN; i = c._Find_next(i)) {
            r.set(i);
            Dfs(r, p & adj[i]);
            r.reset(i);
            p.reset(i);
        }
    }
};

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    MaxClique mc(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int64_t dist = 1LL * (x[i] - x[j]) * (x[i] - x[j]) + 1LL * (y[i] - y[j]) * (y[i] - y[j]);
            if (dist <= 1LL * d * d) mc.AddEdge(i, j);
        }
    }
    auto res = mc();
    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] + 1 << " ";
    }
    cout << "\n";
}

