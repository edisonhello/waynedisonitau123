#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 1000;
int A[kN][kN];
int64_t dp[kN][kN], best[kN][kN];
deque<int> UpQue[kN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M, K, U;
    while (cin >> N >> M >> K >> U) {
        constexpr int64_t kInf = 1'000'000'000'000'000;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) cin >> A[i][j];
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                dp[i][j] = -kInf;
                best[i][j] = -kInf;
            }
        }
        for (int i = 0; i < M; ++i) UpQue[i].clear();
        dp[0][0] = A[0][0];
        for (int i = 0; i < N; ++i) {
            deque<int> Que;
            for (int j = 0; j < M; ++j) {
                while (!Que.empty() && j - Que[0] > K) Que.pop_front();
                if (A[i][j] > 0) {
                    if (i > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j] + A[i][j]);
                    if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j - 1] + A[i][j]);
                    if (i > 0 && j > 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + A[i][j]);
                    while (!UpQue[j].empty() && i - UpQue[j][0] > K) UpQue[j].pop_front();
                    if (!UpQue[j].empty() && best[UpQue[j][0]][j] >= U) {
                        dp[i][j] = max(dp[i][j], best[UpQue[j][0]][j] - U + A[i][j]);
                    }
                    if (!Que.empty() && dp[i][Que[0]] >= U) {
                        dp[i][j] = max(dp[i][j], dp[i][Que[0]] - U + A[i][j]);
                    }
                }
                while (!Que.empty() && dp[i][j] >= dp[i][Que.back()]) Que.pop_back();
                Que.push_back(j);
                best[i][j] = dp[i][Que[0]];
                // cerr << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
            }
            for (int j = 0; j < M; ++j) {
                while (!UpQue[j].empty() && i - UpQue[j][0] > K) UpQue[j].pop_front();
                while (!UpQue[j].empty() && best[i][j] >= best[UpQue[j].back()][j]) UpQue[j].pop_back();
                UpQue[j].push_back(i);
            }
        }
        if (dp[N - 1][M - 1] <= 0) dp[N - 1][M - 1] = -1;
        cout << dp[N - 1][M - 1] << "\n";
    }
    return 0;
}

