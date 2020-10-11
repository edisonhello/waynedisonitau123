#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        vector<vector<int>> g(N);
        vector<int> ed(M), from(M), to(M);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            ed[i] = u ^ v;
            from[i] = u;
            to[i] = v;
            g[u].push_back(i);
            g[v].push_back(i);
        }

        vector<bool> vis(N);
        vector<int> dfn(N, -1), low(N);
        int stamp = 0, C = 0;
        vector<int> stk;
        vector<int> id(N);

        auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
            dfn[x] = low[x] = stamp++;
            stk.push_back(x);
            for (int e : g[x]) {
                int u = (from[e] == x ? to[e] : from[e]);
                if (e == p) continue;
                if (dfn[u] == -1) {
                    dfs(dfs, u, e);
                    low[x] = min(low[x], low[u]);
                } else {
                    low[x] = min(low[x], dfn[u]);
                }
            }
            if (low[x] == dfn[x]) {
                while (true) {
                    int u = stk.back();
                    stk.pop_back();
                    id[u] = C;
                    if (u == x) break;
                }
                C++;
            }
        };

        for (int i = 0; i < N; ++i) {
            if (dfn[i] == -1) {
                stamp = 0;
                Dfs(Dfs, i);
            }
        }

        vector<vector<pair<int, int>>> T(C);
        vector<vector<int>> R(N);
        for (int i = 0; i < N; ++i) {
            for (int e : g[i]) {
                int u = ed[e] ^ i;
                if (id[u] != id[i]) {
                    T[id[i]].emplace_back(id[u], e);
                } else {
                    R[i].push_back(e);
                }
            }
        }

        vector<bool> V(N);
        vector<int> res(M, -2);

        auto DfsCC = [&](auto dfs, int x) -> void {
            // cout << "x = " << x << endl;
            V[x] = true;
            for (int e : R[x]) {
                int u = ed[e] ^ x;
                if (V[u]) {
                    if (res[e] == -2) {
                        if (from[e] == x) res[e] = -1;
                        else res[e] = 1;
                    }
                } else {
                    if (res[e] == -2) {
                        if (from[e] == x) res[e] = -1;
                        else res[e] = 1;
                    }
                    dfs(dfs, u);
                }
            }
        };

        // for (int i = 0; i < N; ++i) {
        //     if (!V[i]) DfsCC(DfsCC, i);
        // }

        // cout << "id: ";
        // for (int i = 0; i < N; ++i) {
        //     cout << id[i] << " ";
        // }
        // cout << "\n";
        for (int i = 0; i < C; ++i) {
            sort(T[i].begin(), T[i].end());
            T[i].resize(unique(T[i].begin(), T[i].end()) - T[i].begin());
        }

        // cout << "here" << endl;

        vector<int> depth(C, -1);
        vector<int> fa(C, -1), fe(C, -1);

        auto DfsTree = [&](auto dfs, int x, int p = -1) -> void {
            // cout << "DfsTree x = " << x << endl;
            for (int i = 0; i < T[x].size(); ++i) {
                int u = T[x][i].first;
                int e = T[x][i].second;
                if (u == p) continue;
                depth[u] = depth[x] + 1;
                fa[u] = x;
                fe[u] = e;
                dfs(dfs, u, x);
            }
        };

        for (int i = 0; i < C; ++i) {
            if (depth[i] == -1) {
                depth[i] = 0;
                DfsTree(DfsTree, i);
            }
        }

        // cout << "fa: ";
        // for (int i = 0; i < C; ++i) cout << fa[i] << " ";
        // cout << endl;

        // return 0;

        for (int i = 0; i < K; ++i) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            x = id[x];
            y = id[y];
            if (x == y) continue;
            while (x != y) {
                if (depth[x] >= depth[y]) {
                    if (id[from[fe[x]]] == x) res[fe[x]] = -1;
                    else res[fe[x]] = 1;
                    x = fa[x];
                } else {
                    if (id[from[fe[y]]] == y) res[fe[y]] = 1;
                    else res[fe[y]] = -1;
                    y = fa[y];
                }
            }
        }
        for (int i = 0; i < M; ++i) {
            if (res[i] == -1) cout << "R";
            else if (res[i] == -2) cout << "0";
            else cout << "L";
        }
        cout << "\n";
    }
}
