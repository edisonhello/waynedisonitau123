#include <bits/stdc++.h>
using namespace std;

template <int K>
struct MaxInfo {
    array<pair<int, int>, K> v;

    MaxInfo() {
        for (int i = 0; i < K; ++i) {
            v[i].first = 0;
            v[i].second = -1;
        }
    }

    void Insert(int a, int b) {
        // cout << "Insert a = " << a << " b = " << b << endl;
        for (int i = 0; i < K; ++i) {
            if (v[i].first < a) {
                for (int j = K - 1; j > i; --j) v[j] = v[j - 1];
                v[i] = make_pair(a, b);
                break;
            }
        }
    }

    int Query(vector<int> a, int k) {
        int res = 0;
        // cout << "K = " << K << " k = " << k << " a.size() = " << a.size() << endl;
        // for (int u : a) cout << u << " ";
        // cout << endl;
        for (int i = 0; i < K && k > 0; ++i) {
            // cout << v[i].second << " ";
            if (find(a.begin(), a.end(), v[i].second) == a.end()) {
                res += v[i].first;
                k--;
            }
        }
        // cout << endl;
        assert(k == 0);
        return res;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dep(n);
    vector<int> fa(n);

    auto Dfs = [&](auto self, int x, int p) -> void {
        dep[x] = ~p ? dep[p] + 1 : 0; 
        fa[x] = p;
        for (int u : g[x]) {
            if (u == p) continue;
            self(self, u, x);
        }
    };

    Dfs(Dfs, 0, -1);
    int f = max_element(dep.begin(), dep.end()) - dep.begin();
    Dfs(Dfs, f, -1);
    int z = max_element(dep.begin(), dep.end()) - dep.begin();
    int d = dep[z] / 2;
    for (int i = 0; i < d; ++i) z = fa[z];

    // cerr << "z = " << z << endl;

    auto Check = [&](int r) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        vector<vector<int>> wh(n + 1, vector<int>(k + 1, -1));
        vector<bool> bad(n);
        vector<int> dep(n), to(n);
        
        auto DfsDp = [&](auto self, int x, int p) -> void {
            to[x] = 0;
            MaxInfo<3> mx;
            for (int u : g[x]) {
                if (u == p) continue;
                self(self, u, x);
                to[x] = max(to[x], to[u] + 1);
                mx.Insert(to[u] + 1, u);
            }
            for (int i = 0; i <= k; ++i) dp[x][i] = n + 1;
            for (int u : g[x]) {
                if (u == p) continue;
                if (mx.Query({u}, 2) > r) continue;
                int z = mx.Query({u}, 1);
                for (int i = 0; i <= k; ++i) {
                    if (dp[u][i] + z <= r) {
                        if (max(dp[u][i], z) < dp[x][i]) {
                            dp[x][i] = max(dp[u][i], z);
                            wh[x][i] = wh[u][i];
                        }
                        // dp[x][i] = min(dp[x][i], max(dp[u][i], z));
                    }
                }
            }
            if (mx.Query({}, 2) > r) bad[x] = true;
            for (int i = k; i > 0; --i) {
                wh[x][i] = wh[x][i - 1];
                dp[x][i] = dp[x][i - 1];
            }
            dp[x][0] = n + 1;
            if (mx.Query({}, 2) <= r && to[x] < dp[x][1]) {
                dp[x][1] = to[x];
                wh[x][1] = x;
            }
            // for (int i = 0; i <= k; ++i) {
                // cout << "dp[" << x << "][" << i << "] = " << dp[x][i] << endl;
            // }
            // dp[x][1] = min(dp[x][1], to[x]);
        };

        DfsDp(DfsDp, z, -1);
        MaxInfo<4> mx;
        int bcnt = 0;
        for (int u : g[z]) {
            mx.Insert(to[u] + 1, u);
            bcnt += bad[u];
        }
        int res = -1, x = -1, y = -1;
        if (mx.Query({}, 2) <= r) return make_tuple(0, 0, 0);
        for (int u : g[z]) {
            int v = mx.Query({u}, 2);
            if (v > r) continue;
            if (bcnt > bad[u]) continue;
            // cout << "r = " << r << " u = " << u << " v = " << v << endl;
            for (int i = 1; i <= k; ++i) {
                // cout << "dp[u][" << i << "] = " << dp[u][i] << endl;
                if (dp[u][i] == n + 1) break;
                if (dp[u][i] + mx.Query({u}, 1) <= r) {
                    if (res == -1 || res > i) {
                        res = i;
                        x = wh[u][i];
                        y = z;
                    }
                }
            }
        }
        // cout << "res = " << res << endl;
        for (int u : g[z]) {
            for (int v : g[z]) {
                if (u == v) continue;
                int z = mx.Query({u, v}, 2);
                if (z > r) continue;
                int b = mx.Query({u, v}, 1);
                if (bcnt > (int)bad[u] + (int)bad[v]) continue;
                // cout << "u = " << u << " v = " << v << " z = " << z << " b = " << b << endl;
                for (int i = 1; i <= min(k, to[u] + 1); ++i) {
                    // cout << "i = " << i << " "  << dp[u][i] << endl;
                    for (int j = 1; j <= min(k, to[v] + 1) && j + i <= k; ++j) {
                        // cout << "j = " << j << " "  << dp[v][j] << endl;
                        if (dp[u][i] + dp[v][j] <= r && dp[u][i] + b <= r && dp[v][j] + b <= r) {
                            // cout << "u = " << u << " v = " << v << " i = " << i << " j = " << j << endl;
                            // cout << dp[u][i] << " " << dp[v][j] << endl;
                            if (res == -1 || res > i + j) {
                                res = i + j;
                                x = wh[u][i];
                                y = wh[v][j];
                            }
                        }
                    }
                }
            }
        }
        return make_tuple(res, x, y);
    };

    // Check(1);
    // return 0;

    int res = n;
    for (int d = 20; d >= 0; --d) {
        if (res - (1 << d) < 0) continue;
        if (get<0>(Check(res - (1 << d))) != -1) res -= (1 << d);
    }

    cout << res << "\n";
    auto tp = Check(res);
    cout << get<0>(tp) << "\n";
    if (get<0>(tp) > 0) {
        cout << get<1>(tp) << " " << get<2>(tp) << "\n";
    }
    return 0;
}

