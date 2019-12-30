#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 1'000'000'000 + 7;

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int m; scanf("%d", &m);
        int k = 0;
        auto Eval = [&](int k) {
            return 1LL * k * k + 1LL * m * (m + 1) / 2 - 1LL * k * (k + 1) - 1LL * (m - k) * k;
        };
        for (int d = 30; d >= 0; --d) {
            int gk = k + (1 << d);
            if (gk >= m) continue;
            if (Eval(gk) >= 1LL * m * gk) k = gk;
        }
        int v = (1LL * m * (m + 1) / 2 - 1LL * k * (k + 1)) % kMod;
        (v += kMod) %= kMod;
        int p = 1LL * v * fpow((m + m - k - k) % kMod, kMod - 2) % kMod;
        printf("%d\n", p);
    }
}
