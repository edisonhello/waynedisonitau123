#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    map<int, int> A;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        A[x]++;
    }
    constexpr int kMod = 1'000'000'000 + 9;
    vector<int> fc(2 * N + 1, 1), iv(2 * N + 1, 1);

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    for (int i = 1; i <= N + N; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
        iv[i] = fpow(fc[i], kMod - 2);
    }

    auto Choose = [&](int n, int k) {
        if (k > n || n < 0) return 0LL;
        return 1LL * fc[n] * iv[k] % kMod * iv[n - k] % kMod;
    };

    vector<int> C;
    for (auto it : A) C.push_back(it.second);
    vector<int> dp(C[0] + 1);
    dp[0] = 1;
    int sum = C[0];

    auto H = [&](int k, int n) { 
        if (k == 0) return int(n == 0);
        return static_cast<int>(Choose(n + k - 1, k - 1));
    };


    // vector<vector<int>> prec(N + 1, vector<int>(N + 1));
    // vector<vector<int>> qrec(N + 1, vector<int>(N + 1));
    // for (int i = 0; i <= N; ++i) {
    //     for (int j = 0; j <= N; ++j) {
    //         prec[i][j] = H(i, j);
    //         if (j > 0) {
    //             (prec[i][j] += prec[i][j - 1]) >= kMod ? prec[i][j] -= kMod : 0;
    //         }
    //     }
    // }
    // for (int i = 0; i <= N; ++i) {
    //     for (int j = 0; j <= N; ++j) {
    //         qrec[i][j] = H(j, i);
    //         if (j > 0) {
    //             (qrec[i][j] += qrec[i][j - 1]) >= kMod ? qrec[i][j] -= kMod : 0;
    //         }
    //     }
    // }

    for (int i = 1; i < C.size(); ++i) {
        vector<int> ndp(sum + C[i] + 1);
        for (int j = 0; j < sum; ++j) {
            // ndp[j] += 1LL * dp[j] * prec[sum - j - 1][C[i]] % kMod;
            // if (ndp[j] >= kMod) ndp[j] -= kMod;
            for (int x = 0; x <= C[i]; ++x) {
                int ways = H(sum, x);
                int nways = H(sum - j - 1, x);
                int tways = (ways + kMod - nways) % kMod;
                (ndp[j] += 1LL * dp[j] * nways % kMod) >= kMod ? ndp[j] -= kMod : 0;
                (ndp[sum + x] += 1LL * dp[j] * tways % kMod) >= kMod ? ndp[sum + x] -= kMod : 0;
            }
        }
        for (int x = 0; x <= C[i]; ++x) {
            int ways = H(sum, x);
            (ndp[sum + x] += 1LL * dp[sum] * ways % kMod) >= kMod ? ndp[sum + x] -= kMod : 0;
        }
        sum += C[i];
        // for (int j = 0; j < ndp.size(); ++j) {
        //     cout << "dp[" << i << "][" << j << "] = " << ndp[j] << endl;
        // }
        dp = ndp;
    }
    cout << dp.back() << "\n";
}

