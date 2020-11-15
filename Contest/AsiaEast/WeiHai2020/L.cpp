#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> div(30000 + 1);
    vector<int> prime;
    for (int i = 2; i <= 30000; ++i) {
        if (!div[i]) {
            div[i] = i;
            prime.push_back(i);
        }
        for (int j = 0; i * prime[j] <= 30000; ++j) {
            div[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
    vector<vector<int>> Power(30000 + 1);
    for (int v = 2; v <= 30000; ++v) {
        if (div[v] == v) {
            int x = v;
            while (x <= 30000) {
                Power[v].push_back(x);
                x *= v;
            }
        }
    }
    vector<double> dp(30000 + 1, -1E9);
    vector<double> next(30000 + 1, -1E9);
    dp[0] = 0;
    for (int v = 2; v <= 30000; ++v) {
        if (Power[v].empty()) continue;
        copy(dp.begin(), dp.end(), next.begin());
        for (int i = 0; i < Power[v].size(); ++i) {
            int u = Power[v][i];
            double L = log(u);
            for (int j = 0; j <= 30000; ++j) {
                if (j + u <= 30000) next[j + u] = max(next[j + u], dp[j] + L);
            }
        }
        dp.swap(next);
    }
    for (int v = 1; v <= 30000; ++v) dp[v] = max(dp[v], dp[v - 1]);
    int T;
    cin >> T;
    while (T--) {
        int b;
        cin >> b;
        cout << fixed << setprecision(20) << dp[b] << "\n";
    }
}

