#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> A(N), B(N), C(N);
    for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
    int S = 0, T = 1;
    int W, D;
    cin >> W >> D;
    vector<vector<int>> Ds(N);
    vector<vector<vector<int>>> adj(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int Dist = abs(A[i] - A[j]) + abs(B[i] - B[j]);
            if (Dist < W) Ds[i].push_back(Dist);
        }
        Ds[i].push_back(W);
        sort(Ds[i].begin(), Ds[i].end());
        Ds[i].resize(unique(Ds[i].begin(), Ds[i].end()) - Ds[i].begin());
    }
    for (int i = 0; i < N; ++i) {
        adj[i].resize(Ds[i].size());
        for (int j = 0; j < N; ++j) {
            int Dist = abs(A[i] - A[j]) + abs(B[i] - B[j]);
            if (Dist <= W) {
                int k = lower_bound(Ds[i].begin(), Ds[i].end(), Dist) - Ds[i].begin();
                assert(Ds[i][k] == Dist);
                adj[i][k].push_back(j);
            }
        }
    }
    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<vector<int64_t>> dp(N);
    for (int i = 0; i < N; ++i) dp[i].assign(Ds[i].size(), kInf);
    for (int i = 0; i < Ds[S].size(); ++i) dp[S][i] = 1LL * Ds[S][i] * C[S];
    int64_t res = kInf;
    for (int i = 0; i < D; ++i) {
        vector<int64_t> cost(N, kInf);
        vector<vector<pair<int, int64_t>>> trans(N);
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < Ds[j].size(); ++k) {
                if (dp[j][k] == kInf) continue;
                if (Ds[j][k] == W) {
                    for (int r = 0; r < N; ++r) {
                        int Dist = abs(A[j] - A[r]) + abs(B[j] - B[r]);
                        if (Dist <= W) {
                            trans[r].emplace_back(W - Dist, dp[j][k]);
                        }
                    }
                } else {
                    for (int u : adj[j][k]) cost[u] = min(cost[u], dp[j][k]);
                }
            }
        }
        res = min(res, cost[T]);
        for (auto [u, w] : trans[T]) res = min(res, w);
        vector<vector<int64_t>> next(N);
        for (int j = 0; j < N; ++j) {
            next[j].assign(Ds[j].size(), kInf);
            sort(trans[j].begin(), trans[j].end());
            int64_t pf = kInf;
            for (int k = 0, ptr = 0; k < Ds[j].size(); ++k) {
                next[j][k] = cost[j] + 1LL * C[j] * Ds[j][k];
                while (ptr < trans[j].size() && trans[j][ptr].first <= Ds[j][k]) {
                    pf = min<int64_t>(pf, trans[j][ptr].second - 1LL * C[j] * trans[j][ptr].first);
                    ptr++;
                }
                next[j][k] = min<int64_t>(next[j][k], pf + 1LL * C[j] * Ds[j][k]);
            }
        }
        dp = next;
    }
    if (res == kInf) res = -1;
    cout << res << "\n";
    return 0;
}

