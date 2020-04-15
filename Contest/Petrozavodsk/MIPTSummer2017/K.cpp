#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    int z = k - m;
    n -= z;
    k -= z;
    if (k == 1) {
        cout << n - 1 << endl;
        return 0;
    }

    constexpr int kMod = 1'000'000'000 + 7;
    vector<int> fc(n + 1, 1), iv(n + 1, 1);

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) {
                res = 1LL * res * a % kMod;
            }
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    for (int i = 1; i <= n; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
    }
    iv[n] = fpow(fc[n], kMod - 2);
    for (int i = n - 1; i >= 0; --i) {
        iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;
    }

    auto Choose = [&](int n, int k) {
        if (k < 0 || n < k) return 0LL;
        return 1LL * fc[n] * iv[k] % kMod * iv[n - k] % kMod;
    };

    int res = k - n;
    for (int i = 1; i <= n - 1; ++i) {
        int add = 1LL * (n - i) * Choose(i - 2, k - 2) % kMod;
        (res += 2 * add % kMod) >= kMod ? res -= kMod : 0;
    }
    cout << res << "\n";
}

