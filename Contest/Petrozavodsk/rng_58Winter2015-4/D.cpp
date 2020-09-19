
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> P(N), Q(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    for (int i = 0; i < N; ++i) cin >> Q[i];

    constexpr int kMod = 1'000'000'000 + 7;
    vector<vector<int>> dp(N + 1, vector<int>(N + 1));
    dp[N][N] = 1;

    vector<int> fc(N + N + 1, 1), iv(N + N + 1, 1);
    for (int i = 1; i <= N + N; ++i) fc[i] = 1LL * fc[i - 1] * i % kMod;

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    iv[N + N] = fpow(fc[N + N], kMod - 2);
    for (int i = N + N - 1; i >= 0; --i) {
        iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;
    }

    auto Bin = [&](int N, int K) {
        return 1LL * fc[N] * iv[K] % kMod * iv[N - K] % kMod;
    };

    auto Catalan = [&](int N) {
        return 1LL * Bin(N + N, N) * fpow(N + 1, kMod - 2) % kMod;
    };

    // for (int i = 0; i <= 20; ++i) cout << Catalan(i) << " ";
    // cout << endl;

    for (int i = N; i >= 0; --i) {
        for (int j = N; j >= 0; --j) {
            if (i == N && j == N) continue;
            if (i < N) {
                (dp[i][j] += dp[i + 1][j]) %= kMod;
            }
            if (j < N) {
                (dp[i][j] += dp[i][j + 1]) %= kMod;
            }
            if (i < N && j < N && P[i] == Q[j]) {
                int x = i, y = j, cnt = 0;
                while (x < N && y < N && P[x] == Q[y]) {
                    (dp[i][j] += kMod - 1LL * Catalan(cnt) * dp[x + 1][y + 1] % kMod) %= kMod;
                    x++;
                    y++;
                    cnt++;
                }
            }
            // cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << endl;
        }
    }
    cout << dp[0][0] << "\n";
}

