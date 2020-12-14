#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> C(K), R(K);
    vector<vector<int>> Circ(N + 1);
    for (int i = 0; i < K; ++i) {
        cin >> C[i] >> R[i];
        assert(R[i] <= 5);
        Circ[C[i] + R[i]].push_back(i);
    }

    constexpr int kP = 1'000'000'000 + 7;
    vector<vector<int>> dp(N + 1, vector<int>(1024));
    dp[0][0] = 1;

    for (int i = 1; i <= N; ++i) {
        for (int s = 0; s < 1024; ++s) {
            if (dp[i - 1][s] == 0) continue;
            bool Bad = false;
            int Has = 0;
            for (int u : Circ[i]) {
                Has |= 1 << R[u];
                if (s >> (2 * R[u] - 1) & 1) {
                    Bad = true;
                    break;
                }
            }
            if (Bad) continue;
            int M = (s << 1) & 1023;
            for (int u : Circ[i]) {
                int Mask = (1 << (2 * R[u])) - 2;
                M |= Mask;
            }
            (dp[i][M] += dp[i - 1][s]) %= kP;
            // cout << "M = " << M << endl;
            vector<int> Ok;
            for (int R = 1; R <= 5; ++R) {
                if (s >> (2 * R - 1) & 1) continue;
                if (i - 2 * R < 0) continue;
                if (Has >> R & 1) continue;
                Ok.push_back(R);
            }
            // cerr << "i = " << i << " s = " << s << " ok: " << endl;
            // for (int u : Ok) cerr << u << " ";
            // cerr << "\n";
            for (int j = 0; j < Ok.size(); ++j) {
                int Mask = (1 << (2 * Ok[j])) - 2;
                (dp[i][M | Mask] += (1LL << j) * dp[i - 1][s] % kP) %= kP;
            }
        }
        // for (int s = 0; s < 1024; ++s) {
            // if (dp[i][s] == 0) continue;
            // cerr << "dp[" << i << "][" << s << "] = " << dp[i][s] << endl;
        // }
    }

    int res = 0;
    for (int i = 0; i < 1024; ++i) (res += dp[N][i]) %= kP;
    cout << res << "\n";
    return 0;
}

