#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    vector<int> uf, sz, hist;
    vector<pair<int *, int>> ops;
    int nedge;

    DisjointSet(int n) : uf(n), sz(n), nedge(0) {
        iota(uf.begin(), uf.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }

    void Clear() {
        iota(uf.begin(), uf.end(), 0);
        fill(sz.begin(), sz.end(), 1);
        nedge = 0;
        ops.clear();
        hist.clear();
    }

    int Find(int x) {
        if (x == uf[x]) return x;
        return Find(uf[x]);
    }

    void Assign(int *p, int v) {
        ops.emplace_back(p, *p);
        *p = v;
    }

    void Merge(int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        Assign(&nedge, nedge + 1);
        Assign(&sz[y], sz[x] + sz[y]);
        Assign(&uf[x], y);
    }

    void Checkpoint() { hist.push_back(ops.size()); }

    void Unroll() {
        int h = hist.back();
        hist.pop_back();
        while (ops.size() > h) {
            *ops.back().first = ops.back().second;
            ops.pop_back();
        }
    }

    bool IsConnected(int V) const { return nedge == V - 1; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];
    vector<pair<int, int>> ans;
    int V = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) V += grid[i][j] == '.';
    }

    vector<vector<pair<int, int>>> E(M * 4);
    DisjointSet djs(N * M);
    auto Solve = [&](int delta) {
        // cerr << "grid: " << endl;
        // for (int i = 0; i < N; ++i) cerr << grid[i] << "\n";
        for (int i = 0; i < M * 4; ++i) E[i].clear();
        djs.Clear();

        auto AddEdge = [&](int ql, int qr, pair<int, int> e) {
            // cout << "AddEdge ql = " << ql << " qr = " << qr << " e = (" << e.first << ", " << e.second << ")\n";
            auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
                if (l >= qr || ql >= r) return;
                if (l >= ql && r <= qr) {
                    E[o].push_back(e);
                    return;
                }
                int m = (l + r) >> 1;
                dfs(dfs, l, m, o * 2 + 1);
                dfs(dfs, m, r, o * 2 + 2);
            };

            return dfs(dfs, 0, M);
        };

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == '#') continue;
                if (i != delta && grid[(i + N - 1) % N][j] == '.') {
                    djs.Merge(((i + N - 1) % N) * M + j, i * M + j);
                }
                if (grid[i][(j + M - 1) % M] == '.') {
                    pair<int, int> e = {i * M + (j + M - 1) % M, i * M + j};
                    AddEdge(0, j, e);
                    AddEdge(j + 1, M, e);
                }
            }
        }

        vector<int> res;

        auto Traverse = [&]() {
            auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
                djs.Checkpoint();
                for (auto e : E[o]) djs.Merge(e.first, e.second);
                if (r - l == 1) {
                    if (djs.IsConnected(V)) {
                        // cerr << "l = " << l << " djs: " << djs.nvertex << " " << djs.nedge << "\n";
                        res.push_back(l);
                    }
                } else {
                    int m = (l + r) >> 1;
                    dfs(dfs, l, m, o * 2 + 1);
                    dfs(dfs, m, r, o * 2 + 2);
                }
                djs.Unroll();
            };

            return dfs(dfs, 0, M);
        };

        Traverse();
        return res;
    };

    for (int i = 0; i < N; ++i) {
        auto res = Solve(i);
        for (int p : res) ans.emplace_back(i, p);
    }
    cout << ans.size() << "\n";
    for (auto p : ans) cout << p.first << " " << p.second << "\n";
}

