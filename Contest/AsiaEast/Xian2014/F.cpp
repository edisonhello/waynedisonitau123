#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    constexpr int kMod = 1'000'000'000 + 7;

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    vector<int> fc(1'000'000 + 1, 1), iv(1'000'000 + 1, 1);
    for (int i = 1; i <= 1'000'000; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
        iv[i] = fpow(fc[i], kMod - 2);
    }
    vector<int> inverse(1'000'000 + 1, 1);
    for (int i = 1; i <= 1'000'000; ++i) {
        inverse[i] = fpow(i, kMod - 2);
    }

    for (int tc = 1; tc <= T; ++tc) {
        int N, M, K;
        cin >> N >> M >> K;
        if (K > M) {
            cout << "Case #" << tc << ": " << 0 << "\n";
            continue;
        }

        int res = 0;

        auto Choose = [&](int n, int k) -> int {
            if (n < k || k < 0) return 0;
            return 1LL * fc[n] * iv[k] % kMod * iv[n - k] % kMod;
        };

        for (int k = 1; k <= K; ++k) {
            int ways = 1LL * k * fpow(k - 1, N - 1) % kMod * Choose(K, k) % kMod;
            if ((K - k) & 1) (res += kMod - ways) %= kMod;
            else (res += ways) %= kMod;
        }
        int mult = 1;
        for (int i = 0; i < K; ++i) {
            mult = 1LL * mult * (M - i) % kMod;
            mult = 1LL * mult * inverse[K - i] % kMod;
        }
        res = 1LL * res * mult % kMod;
        cout << "Case #" << tc << ": " << res << "\n";
    }
}

