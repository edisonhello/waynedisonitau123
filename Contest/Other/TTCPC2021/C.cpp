#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<int> u(M), v(M), c(M);
    vector<vector<int>> cc(M);
    for (int i = 0; i < M; ++i) {
        cin >> u[i] >> v[i] >> c[i];
        u[i]--;
        v[i]--;
        c[i]--;
        cc[c[i]].push_back(i);
    }
    vector<bool> used(M), color(M);
    bitset<30000> y1, y2;
    vector<int> dist(M), fa(M);
    vector<int> root(N);

    vector<vector<int>> g(N);
    vector<bool> vis(N);
    vector<int> pa(N, -1), dep(N);

    for (int it = 0; it < N; ++it) {
        for (int i = 0; i < N; ++i) g[i].clear();
        fill(vis.begin(), vis.end(), false);
        for (int i = 0; i < M; ++i) {
            if (!used[i]) continue;
            g[u[i]].push_back(i);
            g[v[i]].push_back(i);
        }

        y1.reset();
        y2.reset();

        auto Dfs = [&](auto dfs, int x, int r, int p = -1) -> void {
            vis[x] = true;
            pa[x] = p;
            root[x] = r;
            for (int e : g[x]) {
                int y = u[e] ^ v[e] ^ x;
                if (vis[y]) continue;
                dep[y] = dep[x] + 1;
                dfs(dfs, y, r, e);
            }
        };

        for (int i = 0; i < N; ++i) {
            if (vis[i]) continue;
            dep[i] = 0;
            Dfs(Dfs, i, i);
        }

        fill(dist.begin(), dist.end(), -1);
        vector<int> que;
        bool found = false;
        for (int i = 0; i < M; ++i) {
            if (used[i]) continue;
            if (!color[c[i]]) {
                y1[i] = true;
                fa[i] = -1;
                dist[i] = 0;
                que.push_back(i);
            }
            if (root[u[i]] != root[v[i]]) y2[i] = true;
            if (y1[i] && y2[i]) {
                used[i] = true;
                found = true;
                color[c[i]] = true;
                break;
            }
        }
        if (found) continue;
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            if (y2[x]) {
                while (x != -1) {
                    used[x] = !used[x];
                    color[c[x]] = !color[c[x]];
                    x = fa[x];
                }
                found = true;
                break;
            }
            if (used[x]) {
                for (int u : cc[c[x]]) {
                    if (!used[u] && dist[u] == -1) {
                        dist[u] = dist[x] + 1;
                        fa[u] = x;
                        que.push_back(u);
                    }
                }
            } else {
                int a = u[x], b = v[x];
                while (a != b) {
                    if (dep[a] < dep[b]) swap(a, b);
                    if (dist[pa[a]] == -1) {
                        dist[pa[a]] = dist[x] + 1;
                        fa[pa[a]] = x;
                        que.push_back(pa[a]);
                    }
                    a = u[pa[a]] ^ v[pa[a]] ^ a;
                }
            }
        }
        if (!found) break;
    }

    int res = count(used.begin(), used.end(), true);

    vector<int> uf(M);
    iota(uf.begin(), uf.end(), 0);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
        uf[Find(x)] = Find(y);
    };

    for (int i = 0; i < M; ++i) {
        if (used[i]) Merge(u[i], v[i]);
    }
    for (int i = 0; i < M; ++i) {
        if (Find(u[i]) != Find(v[i])) {
            used[i] = true;
            Merge(u[i], v[i]);
        }
    }
    vector<int> ans;
    for (int i = 0; i < M; ++i) if (used[i]) ans.push_back(i);
    cout << res << "\n";
    assert(ans.size() == N - 1);
    for (int i = 0; i < ans.size(); ++i) cout << ans[i] + 1 << " \n"[i + 1 == ans.size()];

}
