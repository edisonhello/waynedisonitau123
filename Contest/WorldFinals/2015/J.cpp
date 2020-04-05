#include <bits/stdc++.h>
using namespace std;

constexpr int kMod = 167772161;
constexpr int kRoot = 3;

int main() {
    int n;
    cin >> n;

    vector<int> dv(500000 + 1);
    for (int i = 1; i <= 500000; ++i) {
        for (int j = i; j <= 500000; j += i) dv[j]++;
    }

    constexpr int kN = 1048576;
    vector<int> omega(kN + 1);

    constexpr auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    auto Build = [&]() {
        constexpr int x = fpow(kRoot, (kMod - 1) / kN);
        omega[0] = 1;
        for (int i = 1; i <= kN; ++i) {
            omega[i] = 1LL * omega[i - 1] * x % kMod;
        }
    };

    auto Bitrev = [&](vector<int> &v, int n) {
        int z = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
            if (x > i) swap(v[x], v[i]);
        }
    };

    auto Trans = [&](vector<int> &v, int n) {
        Bitrev(v, n);
        for (int s = 2; s <= n; s <<= 1) {
            int z = s >> 1;
            for (int i = 0; i < n; i += s) {
                for (int k = 0; k < z; ++k) {
                    int x = 1LL * v[i + k + z] * omega[kN / s * k] % kMod;
                    (v[i + k + z] = v[i + k] + kMod - x) >= kMod ? v[i + k + z] -= kMod : 0;
                    (v[i + k] += x) >= kMod ? v[i + k] -= kMod : 0;
                }
            }
        }
    };

    Build();

    dv.resize(kN);

    Trans(dv, kN);
    for (int i = 0; i < kN; ++i) dv[i] = 1LL * dv[i] * dv[i] % kMod;
    Trans(dv, kN);
    for (int i = 1; i < kN / 2; ++i) swap(dv[i], dv[kN - i]);
    constexpr int kInv = fpow(kN, kMod - 2);
    for (int i = 0; i < kN; ++i) dv[i] = 1LL * dv[i] * kInv % kMod;

    while (n--) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        int p = max_element(dv.begin() + l, dv.begin() + r + 1) - dv.begin();
        cout << p << " " << dv[p] << endl;
    }
}

