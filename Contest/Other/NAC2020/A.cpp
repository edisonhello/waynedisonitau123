#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, k;
    cin >> m >> k;
    vector<int> mu(k + 1), dv(k + 1);
    vector<int> pr;
    constexpr int kMod = 998244353;
    mu[1] = 1;
    for (int i = 2; i <= k; ++i) {
        if (!dv[i]) {
            dv[i] = i;
            pr.push_back(i);
            mu[i] = kMod - 1;
        }
        for (int j = 0; i * pr[j] <= k; ++j) {
            dv[i * pr[j]] = pr[j];
            mu[i * pr[j]] = kMod - mu[i];
            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                break;
            }
        }
    }

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    int res = 1;
    for (int t = 1; t <= k; ++t) {
        int d = (fpow(2 * (k / t) + 1, m) + kMod - 1) % kMod;
        res += 1LL * mu[t] * d % kMod;
        if (res >= kMod) res -= kMod;
    }
    cout << res << "\n";
}


