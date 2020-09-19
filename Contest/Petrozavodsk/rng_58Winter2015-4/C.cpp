#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> V;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (A[i] == A[j]) continue;
            V.push_back(A[i] - A[j]);
            V.push_back(A[j] - A[i]);
        }
    }
    sort(V.begin(), V.end());
    V.resize(unique(V.begin(), V.end()) - V.begin());
    int M = 30'000;
    vector<int> dp(M + M + 1, 1'000'000'000);
    dp[M] = 0;
    vector<int> que(1, 0);
    for (int it = 0; it < que.size(); ++it) {
        int x = que[it];
        for (int u : V) {
            if (x + u >= -M && x + u <= M) {
                if (dp[x + u + M] == 1'000'000'000) {
                    dp[x + u + M] = dp[x + M] + 1;
                    que.push_back(x + u);
                }
            }
        }
    }
    // dp[M] = 0;
    // for (int i = 0; i < V.size(); ++i) {
    //     if (V[i] > 0) {
    //         for (int j = -M; j + V[i] <= M; ++j) {
    //             dp[j + V[i] + M] = min(dp[j + V[i] + M], dp[j + M] + 1);
    //         }
    //     } else {
    //         for (int j = M; j + V[i] >= -M; --j) {
    //             dp[j + V[i] + M] = min(dp[j + V[i] + M], dp[j + M] + 1);
    //         }
    //     }
    // }
    int Q;
    cin >> Q;
    while (Q--) {
        int s, t;
        cin >> s >> t;
        int res = 1'000'000'000;
        if ((s - t) % 2 == 0) {
            res = min(res, dp[(s - t) / 2 + M] * 2);
        }
        for (int i = 0; i < N; ++i) {
            int d = 2 * A[i] - s;
            if ((d - t) % 2 == 0) {
                res = min(res, dp[(d - t) / 2 + M] * 2 + 1);
            }
        }
        if (res == 1'000'000'000) res = -1;
        cout << res << "\n";
    }
    return 0;
}

