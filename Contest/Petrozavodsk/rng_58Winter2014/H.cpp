#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Centroid {
    vector<vector<int64_t>> Dist;
    vector<int> Parent, Depth;
    vector<int64_t> Sub, Sub2;
    vector<int> Sz, Sz2;

    Centroid(vector<vector<pair<int, int>>> g) {
        int N = g.size();
        vector<bool> Vis(N);
        vector<int> sz(N), mx(N);
        vector<int> Path;
        Dist.resize(N);
        Parent.resize(N);
        Depth.resize(N);

        auto DfsSz = [&](auto dfs, int x) -> void {
            Vis[x] = true;
            sz[x] = 1;
            mx[x] = 0;
            for (auto [u, w] : g[x]) {
                if (Vis[u]) continue;
                dfs(dfs, u);
                sz[x] += sz[u];
                mx[x] = max(mx[x], sz[u]);
            }
            Path.push_back(x);
        };

        auto DfsDist = [&](auto dfs, int x, int64_t D = 0) -> void {
            Dist[x].push_back(D);
            Vis[x] = true;
            for (auto [u, w] : g[x]) {
                if (Vis[u]) continue;
                dfs(dfs, u, D + w);
            }
        };

        auto Dfs = [&](auto dfs, int x, int D = 0, int p = -1) -> void {
            Path.clear();
            DfsSz(DfsSz, x);
            int M = Path.size();
            int C = -1;
            for (int u : Path) {
                if (max(M - sz[u], mx[u]) * 2 <= M) C = u;
                Vis[u] = false;
            }
            DfsDist(DfsDist, C);
            for (int u : Path) Vis[u] = false;
            Parent[C] = p;
            Vis[C] = true;
            Depth[C] = D;
            for (auto [u, w] : g[C]) {
                if (Vis[u]) continue;
                dfs(dfs, u, D + 1, C);
            }
        };

        Dfs(Dfs, 0);
        Sub.resize(N);
        Sub2.resize(N);
        Sz.resize(N);
        Sz2.resize(N);

#if 0
        cout << "Parent: ";
        for (int i = 0; i < N; ++i) cout << Parent[i] << " "; cout << endl;
        cout << "Depth: ";
        for (int i = 0; i < N; ++i) cout << Depth[i] << " "; cout << endl;
#endif
    }

    void Mark(int v) {
        int x = v, z = -1;
        for (int i = Depth[v]; i >= 0; --i) {
            Sub[x] += Dist[v][i];
            Sz[x]++;
            if (z != -1) {
                Sub2[z] += Dist[v][i];
                Sz2[z]++;
            }
            z = x;
            x = Parent[x];
        }
    }

    int64_t Query(int v) {
        int64_t res = 0;
        int x = v, z = -1;
        for (int i = Depth[v]; i >= 0; --i) {
            res += Sub[x] + 1LL * Sz[x] * Dist[v][i];
            if (z != -1) res -= Sub2[z] + 1LL * Sz2[z] * Dist[v][i];
            z = x;
            x = Parent[x];
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> g(N);
    for (int i = 1; i < N; ++i) {
        int p, w;
        cin >> p >> w;
        p--;
        g[p].emplace_back(i, w);
        g[i].emplace_back(p, w);
    }

    Centroid C(g);
    
    vector<vector<int>> Jump(N, vector<int>(20, -1));
    vector<int> Depth(N);
    vector<int> tin(N), tout(N);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        static int T = 0;
        tin[x] = T++;
        Jump[x][0] = p;
        for (int i = 1; (1 << i) <= Depth[x]; ++i) Jump[x][i] = Jump[Jump[x][i - 1]][i - 1];
        for (auto [u, w] : g[x]) {
            if (u == p) continue;
            Depth[u] = Depth[x] + 1;
            dfs(dfs, u, x);
        } 
        tout[x] = T;
    };

    Dfs(Dfs, 0);
    cout << "0\n";
    int Cent = 0;
    C.Mark(0);

    vector<int> Fenw(N + 1);

    auto Update = [&](int p, int v) {
        for (int i = p + 1; i <= N; i += i & -i) Fenw[i] += v;
    };

    auto Query = [&](int p) {
        int res = 0;
        for (int i = p; i > 0; i -= i & -i) res += Fenw[i];
        return res;
    };

    auto QueryRange = [&](int L, int R) {
        return Query(R) - Query(L);
    };

    auto GetLCA = [&](int x, int y) {
        if (Depth[x] > Depth[y]) swap(x, y);
        for (int i = 0; i < 20; ++i) {
            if ((Depth[y] - Depth[x]) >> i & 1) y = Jump[y][i];
        }
        if (x == y) return x;
        for (int i = 19; i >= 0; --i) {
            if (Jump[x][i] != Jump[y][i]) {
                x = Jump[x][i];
                y = Jump[y][i];
            }
        }
        return Jump[x][0];
    };

    auto GetJump = [&](int x, int D) {
        for (int i = 0; i < 20; ++i) {
            if (D >> i & 1) x = Jump[x][i];
        }
        return x;
    };

    auto GetKth = [&](int x, int y, int z, int D) {
        // x -> y, LCA = z
        assert(D <= Depth[x] + Depth[y] - 2 * Depth[z]);
        if (D <= Depth[x] - Depth[z]) return GetJump(x, D);
        return GetJump(y, Depth[y] - Depth[z] - (D - (Depth[x] - Depth[z])));
    };

    int64_t Ans = 0;
    for (int K = 1; K < N; ++K) {
        int L = GetLCA(Cent, K);
        int D = Depth[K] + Depth[Cent] - 2 * Depth[L];
        Update(tin[K], 1);
        C.Mark(K);
        if (Cent != K) {
            int G = 0;
            for (int bit = 19; bit >= 0; --bit) {
                if (G + (1 << bit) + 1 > D) continue;
                int x = GetKth(Cent, K, L, G + (1 << bit));
                int y = GetKth(Cent, K, L, G + (1 << bit) + 1);
                if (Jump[x][0] == y) {
                    int Before = QueryRange(tin[x], tout[x]);
                    int After = K + 1 - Before;
                    if (K + 1 - Before >= Before && After >= K + 1 - After) G += (1 << bit);
                } else {
                    assert(Jump[y][0] == x);
                    int Before = K + 1 - QueryRange(tin[y], tout[y]);
                    int After = K + 1 - Before;
                    if (K + 1 - Before >= Before && After >= K + 1 - After) G += (1 << bit);
                }
            }
            int x = GetKth(Cent, K, L, G);
            int y = GetKth(Cent, K, L, G + 1);
            int64_t A = C.Query(x);
            int64_t B = C.Query(y);
            if (A > B) {
                swap(x, y);
                swap(A, B);
            }
            Cent = x;
            Ans = A;
        }
#if 0
        cout << "Query(x) = " << C.Query(x) << endl;
        cout << "Query(y) = " << C.Query(y) << endl;
#endif 
        cout << Ans << "\n";
    }
    return 0;
}

