#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 60 * 300000 + 10;
vector<int> trie[kN];
vector<int64_t> nd[kN];
int sz[kN];
int dep[kN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int64_t x;
    cin >> x;
    vector<int64_t> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    constexpr int kMod = 998244353;

    if (x == 0) {
        int res = 1;
        for (int i = 0; i < n; ++i) res = (res + res) % kMod;
        res = (res + kMod - 1) % kMod;
        cout << res << "\n";
        return 0;
    }

    int hbit = -1;
    for (int d = 59; d >= 0; --d) {
        if (x >> d & 1) {
            hbit = d;
            break;
        }
    }

    // vector<vector<int>> trie(1, {-1, -1});
    // vector<vector<int64_t>> nd(1);
    // vector<int> sz(1, 0);
    // vector<int> dep(1, 59);
    dep[0] = 59;
    trie[0] = {-1, -1};

    int ptr = 1;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        sz[0]++;
        for (int d = 59; d >= 0; --d) {
            int bit = (a[i] >> d & 1);
            if (trie[x][bit] == -1) {
                trie[x][bit] = ptr;
                trie[ptr] = {-1, -1};
                dep[ptr] = dep[x] - 1;
                ptr++;
            }
            x = trie[x][bit];
            if (d == hbit) {
                nd[x].push_back(a[i]);
            }
            sz[x]++;
        }
    }

    function<void(int)> Dfs = [&](int x) {
        for (int v = 0; v < 2; ++v) {
            if (trie[x][v] != -1) {
                Dfs(trie[x][v]);
                sz[x] += sz[trie[x][v]];
            }
        }
    };


    // cout << "hi" << endl;
    // Dfs(0);
    // cout << "hi" << endl;
    // for (int i = 0; i < ptr; ++i) cout << sz[i] << " ";
    // cout << endl;
    // for (int i = 0; i < ptr; ++i) cout << trie[i][0] << " " << trie[i][1] << endl;
    // for (int i = 0; i < ptr; ++i) cout << dep[i] << " ";
    // cout << endl;

    vector<int> dp(ptr, -1);

    for (int i = 0; i < ptr; ++i) {
        if (dep[i] != hbit) continue;
        if (trie[i][0] == -1 && trie[i][1] == -1) {
            dp[i] = 1;
        } else if (trie[i][0] == -1) {
            dp[i] = sz[trie[i][1]] + 1;
        } else if (trie[i][1] == -1) {
            dp[i] = sz[trie[i][0]] + 1;
        } else {
            dp[i] = sz[trie[i][0]] + sz[trie[i][1]] + 1;

            auto Query = [&](auto self, int64_t v, int64_t w, int x, int d) {
                // cout << "Query v = " << v << " w = " << w << " x = " << x << " d = " << d << endl;
                if (d < 0) return sz[x];
                if (w >> d & 1) {
                    if (v >> d & 1) {
                        if (trie[x][0] == -1) return 0;
                        return self(self, v, w, trie[x][0], d - 1);
                    } else {
                        if (trie[x][1] == -1) return 0;
                        return self(self, v, w, trie[x][1], d - 1);
                    }
                } else {
                    if (v >> d & 1) {
                        int res = (trie[x][0] != -1 ? sz[trie[x][0]] : 0);
                        if (trie[x][1] != -1) {
                            res += self(self, v, w, trie[x][1], d - 1);
                        }
                        return res;
                    } else {
                        int res = (trie[x][1] != -1 ? sz[trie[x][1]] : 0);
                        if (trie[x][0] != -1) {
                            res += self(self, v, w, trie[x][0], d - 1);
                        }
                        return res;
                    }
                }
            };


            // cout << "nd = ";
            // for (int64_t v : nd[trie[i][1]]) {
            //     cout << v << " ";
            // }
            // cout << endl;

            for (int64_t u : nd[trie[i][0]]) {
                int res = Query(Query, u, x ^ (1LL << hbit), trie[i][1], hbit - 1);
                (dp[i] += res) >= kMod ? dp[i] -= kMod : 0;
                // cout << "Query " << u << " : " << res << endl;
                if (dp[i] >= kMod) dp[i] -= kMod;
            }
            // for (int64_t u : nd[trie[i][0]]) {
            //     for (int64_t v : nd[trie[i][1]]) {
            //         if ((u ^ v) >= x) {
            //             dp[i]++;
            //         }
            //     }
            // }
        }
    }

    // for (int i = 0; i < ptr; ++i) cout << dp[i] << " ";
    // cout << endl;
    // cout << "hi" << endl;

    function<void(int)> Dfs2 = [&](int x) {
        if (dp[x] != -1) return;
        int left = 1, right = 1;
        if (trie[x][0] != -1) {
            Dfs2(trie[x][0]);
            left = dp[trie[x][0]];
        }
        if (trie[x][1] != -1) {
            Dfs2(trie[x][1]);
            right = dp[trie[x][1]];
        }
        dp[x] = 1LL * left * right % kMod;
    };

    Dfs2(0);
    int res = (dp[0] + kMod - 1) % kMod;
    cout << res << "\n";
    return 0;
}

