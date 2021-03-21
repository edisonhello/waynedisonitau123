#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<vector<int>> Q(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) cin >> Q[i][j];
    }
    vector<vector<pair<int, int64_t>>> L(N);

    auto Kill = [&](auto A, auto B, auto C) {
        return __int128(A.second - C.second) * (B.first - A.first) <= __int128(A.second - B.second) * (C.first - A.first);
    };

    for (int i = 0; i < N; ++i) {
        int K;
        cin >> K;
        vector<pair<int, int64_t>> V(K);
        for (int j = 0; j < K; ++j) {
            cin >> V[j].first >> V[j].second;
            V[j].second *= -1;
        }
        sort(V.begin(), V.end(), [&](auto X, auto Y) {
            if (X.first == Y.first) return X.second > Y.second;
            return X.first < Y.first;         
        });
        for (int j = 0; j < K; ++j) {
            if (!L[i].empty() && L[i].back().first == V[j].first && L[i].back().second >= V[j].second) continue;
            while (L[i].size() >= 2 && Kill(L[i][L[i].size() - 2], L[i].back(), V[j])) L[i].pop_back();
            L[i].push_back(V[j]);
        }
    }

    vector<vector<int64_t>> dp(N, vector<int64_t>(N));
    vector<vector<bool>> visited(N, vector<bool>(N));

    constexpr int64_t kInf = 1'000'000'000'000'000'000;

    vector<vector<int>> sum(N, vector<int>(N));
    for (int i = 0; i < N; ++i) sum[i][i] = Q[i][i];
    for (int L = 2; L <= N; ++L) {
        for (int i = 0; i + L <= N; ++i) {
            sum[i][i + L - 1] = Q[i][i + L - 1] + sum[i][i + L - 2] + sum[i + 1][i + L - 1] - sum[i + 1][i + L - 2];
        }
    }

    auto Eval = [&](auto L, int x) -> int64_t {
        return 1LL * L.first * x + L.second;
    };

    auto Query = [&](const auto &L, int x) {
        int p = 0;
        for (int d = 20; d >= 0; --d) {
            if (p + (1 << d) + 1 < L.size()) {
                int64_t a = Eval(L[p + (1 << d)], x);
                int64_t b = Eval(L[p + (1 << d) + 1], x);
                if (b >= a) p += (1 << d);
            }
        }
        int64_t res = Eval(L[p], x);
        if (p + 1 < L.size()) res = max(res, Eval(L[p + 1], x));
        if (p > 0) res = max(res, Eval(L[p - 1], x));
        return res;
    };

    auto Dfs = [&](auto dfs, int l, int r) -> int64_t {
        if (l > r) return 0;
        if (visited[l][r]) return dp[l][r];
        visited[l][r] = true;
        dp[l][r] = -kInf;
        for (int m = l; m <= r; ++m) {
            int64_t v = dfs(dfs, l, m - 1) + dfs(dfs, m + 1, r);
            int coeff = sum[l][r];
            if (m - 1 >= l) coeff -= sum[l][m - 1];
            if (m + 1 <= r) coeff -= sum[m + 1][r];
            int64_t t = Query(L[m], coeff);
            dp[l][r] = max(dp[l][r], v + t);
        }
        return dp[l][r];
    };

    cout << Dfs(Dfs, 0, N - 1) << "\n";
}

