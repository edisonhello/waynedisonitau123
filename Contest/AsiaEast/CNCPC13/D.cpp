#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> sz(N), to(N), dep(N), fa(N, -1);
    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        sz[x] = 1;
        to[x] = -1; 
        fa[x] = p;
        for (int u : g[x]) {
            if (u == p) continue;
            dep[u] = dep[x] + 1;
            dfs(dfs, u, x);
            sz[x] += sz[u];
            if (to[x] == -1 || sz[u] > sz[to[x]]) to[x] = u;
        }
    };

    vector<int> Order, Head(N), Rev(N);
    auto Link = [&](auto dfs, int x, int t, int p = -1) -> void {
        Rev[x] = Order.size();
        Order.push_back(x);
        Head[x] = t;
        if (to[x] != -1) dfs(dfs, to[x], t, x);
        for (int u : g[x]) {
            if (u == p || u == to[x]) continue;
            dfs(dfs, u, u, x);
        }
    };

    Dfs(Dfs, 0);
    Link(Link, 0, 0);

    vector<int64_t> w(N);
    while (M--) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v, k;
            cin >> u >> v >> k;
            u--;
            v--;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) w[p--] += k;
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) w[p++] += k;
        }
        if (t == 2) {
            int u, v, k;
            cin >> u >> v >> k;
            u--;
            v--;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) w[p--] ^= k;
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) w[p++] ^= k;
        }
        if (t == 3) {
            int u, v, k;
            cin >> u >> v >> k;
            u--;
            v--;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) {
                    if (w[p] >= k) w[p] -= k;
                    p--;
                }
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) {
                if (w[p] >= k) w[p] -= k;
                p++;
            }
        }
        if (t == 4) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            int64_t sum = 0;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) sum += w[p--];
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) sum += w[p++];
            cout << sum << "\n";
        }
        if (t == 5) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            int64_t sum = 0;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) sum ^= w[p--];
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) sum ^= w[p++];
            cout << sum << "\n";
        }
        if (t == 6) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            int64_t Max = 0, Min = 1'000'000'000'000'000'000;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) {
                    Max = max(Max, w[p]);
                    Min = min(Min, w[p]);
                    p--;
                }
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) {
                Max = max(Max, w[p]);
                Min = min(Min, w[p]);
                p++;
            }
            cout << Max - Min << "\n";
        }
        if (t == 7) {
            int u, v, k;
            cin >> u >> v >> k;
            u--;
            v--;
            int64_t Res = 1'000'000'000'000'000'000;
            int fu = Head[u], fv = Head[v];
            while (fu != fv) {
                if (dep[fu] < dep[fv]) {
                    swap(fu, fv);
                    swap(u, v);
                }
                int p = Rev[u], q = Rev[fu];
                while (p >= q) {
                    if (w[p] >= k) Res = min(Res, w[p] - k);
                    else Res = min(Res, k - w[p]);
                    p--;
                }
                u = fa[fu];
                fu = Head[u];
            }
            int p = min(Rev[u], Rev[v]), q = max(Rev[u], Rev[v]);
            while (p <= q) {
                if (w[p] >= k) Res = min(Res, w[p] - k);
                else Res = min(Res, k - w[p]);
                p++;
            }
            cout << Res << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) Solve();
}

