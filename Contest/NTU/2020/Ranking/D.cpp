#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<pair<int, int>>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> sz(N), mx(N), path;
    vector<bool> used(N);

    auto DfsSz = [&](auto dfs, int x) -> void {
        path.push_back(x);
        sz[x] = 1;
        mx[x] = 0;
        used[x] = true;
        for (auto [u, w] : g[x]) {
            if (used[u]) continue;
            dfs(dfs, u);
            sz[x] += sz[u];
            mx[x] = max(mx[x], sz[u]);
        }
    };

    vector<vector<int64_t>> dist(N);
    vector<int> depth(N), fa(N);

    auto DfsDist = [&](auto dfs, int x, int64_t sum = 0) -> void {
        used[x] = true;
        dist[x].push_back(sum);
        for (auto [u, w] : g[x]) {
            if (used[u]) continue;
            dfs(dfs, u, sum + w);
        }
    };

    auto Dfs = [&](auto dfs, int x, int dep = 0, int p = -1) -> void {
        path.clear();
        DfsSz(DfsSz, x);

        int M = path.size(), cent = -1;
        for (int u : path) {
            if (max(M - sz[u], mx[u]) * 2 <= M) cent = u;
            used[u] = false;
        }
        assert(cent != -1);
        DfsDist(DfsDist, cent);
        for (int u : path) used[u] = false;
        depth[cent] = dep;
        fa[cent] = p;
        used[cent] = true;
        for (auto [u, w] : g[cent]) {
            if (used[u]) continue;
            dfs(dfs, u, dep + 1, cent);
        }
    };

    Dfs(Dfs, 0);
    cerr << static_cast<double>(clock()) / CLOCKS_PER_SEC << endl;

    vector<int64_t> sub(N), sub2(N);
    vector<int> subs(N), subs2(N);

    // for (int i = 0; i < N; ++i) {
    //     for (int x = i, j = depth[i]; j >= 0; --x, x = fa[x]) {
    //         sub[x] += dist[x][j];
    //     }
    // }

    int Q;
    cin >> Q;
    vector<int> L(Q), R(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> L[i] >> R[i];
        L[i]--;
        R[i]--;
    }
    vector<int> order(Q);
    iota(order.begin(), order.end(), 0);
    const int B = 100;
    sort(order.begin(), order.end(), [&](int i, int j) {
        if (L[i] / B == L[j] / B) return R[i] < R[j];
        return L[i] / B < L[j] / B;
    });

    int64_t X = 0;

    auto Query = [&](int v) {
        int64_t res = 0;
        int z = -1;
        int x = v;
        for (int i = depth[v]; i >= 0; --i) {
            res += dist[x][i] * subs[v] + sub[v];
            if (z != -1) res -= dist[x][i] * subs2[z] + sub2[z];
            z = v;
            v = fa[v];
        }
        return res;
    };

    auto Add = [&](int v) {
        int x = v;
        X += Query(v);
        for (int i = depth[v]; i >= 0; --i) {
            sub[v] += dist[x][i];
            subs[v]++;
            if (i > 0) {
                sub2[v] += dist[x][i - 1];
                subs2[v]++;
            }
            v = fa[v];
        }
    };

    auto Sub = [&](int v) {
        X -= Query(v);
        int x = v;
        for (int i = depth[v]; i >= 0; --i) {
            sub[v] -= dist[x][i];
            subs[v]--;
            if (i > 0) {
                sub2[v] -= dist[x][i - 1];
                subs2[v]--;
            }
            v = fa[v];
        }
    };

    vector<int64_t> res(Q);
    for (int i = 0, tl = 0, tr = -1; i < Q; ++i) {
        while (tr < R[order[i]]) Add(++tr);
        while (tr > R[order[i]]) Sub(tr--);
        while (tl > L[order[i]]) Add(--tl);
        while (tl < L[order[i]]) Sub(tl++);
        res[order[i]] = X;
    }
    for (int i = 0; i < Q; ++i) cout << res[i] * 2 << "\n";
    return 0;
}
