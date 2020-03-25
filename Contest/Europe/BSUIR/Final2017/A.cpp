#include <bits/stdc++.h>
using namespace std;

constexpr int64_t kInf = 2'000'000'000'000'000'000;
constexpr int kMod = 1'000'000'000 + 7;
int64_t ck[500][500];
int pw[500];

int64_t Add(int64_t a, int64_t b) {
    return min(a + b, kInf);
}

int64_t Mult(int64_t a, int64_t b) {
    if (a > kInf / b) return kInf;
    return min(a * b, kInf);
}

int64_t Choose(int64_t a, int b) {
    int64_t res = 1;
    for (int i = 0; i < b; ++i) {
        double db = 1.0 * res * (a - i) / (i + 1);
        if (db > kInf) return kInf;
        int64_t kv = (__int128)res * (a - i) / (i + 1);
        res = min(kInf, kv);
    }
    // cout << "Choose a = " << a << " b = " << b << " res = " << res << endl;
    return res;
}

int fpow(int a, int64_t n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}

int BruteForce(int n, int k) {
    vector<int> v;
    for (int x = 0; x < 30; ++x) {
        for (int y = 0; y < x; ++y) {
            if ((1 << x) > (1 << y)) {
                v.push_back((1 << x) - (1 << y));
            }
        }
    }
    sort(v.begin(), v.end());
    vector<int> w;
    for (int i = v[n - 1]; i < v[n]; ++i) w.push_back(i);
    sort(w.begin(), w.end(), [&](int a, int b) {
            if (__builtin_popcount(a) == __builtin_popcount(b)) {
            return a < b;
            }
            return __builtin_popcount(a) < __builtin_popcount(b);
            });
    if (w.size() < k) return -1;
    return w[k - 1];
}

int Solve(int64_t n, int64_t k) {
    int64_t m = 0;
    for (int d = 40; d >= 0; --d) {
        int64_t g = m + (1LL << d);
        if ((__int128)g * (g + 1) / 2 < n) m = g;
    }
    int64_t h = m * (m + 1) / 2;
    int64_t r = n - h;
    m++;
    if (m == r) {
        if (k == 1) return (fpow(2, m) + kMod - 1) % kMod;
        return -1;
    }
    int64_t z = m - r - 1;
    int64_t cnk = 1, sum = 0;

    int64_t cz = -1, csum = 0;

    // cout << "m = " << m << endl;
    // cout << "z = " << z << endl;

    for (int64_t i = 0; i <= z; ++i) {
        // cout << "cnk = " << cnk << endl;
        sum = Add(sum, cnk);
        if (sum < k) {
            cz = i;
            csum = sum;
        }
        double nxt = cnk * 1.0 * (z - i) / (i + 1);
        if (nxt > k) {
            cnk = kInf;
            sum = kInf;
            break;
        }
        cnk = (__int128)cnk * (z - i) / (i + 1);
    }
    if (k > sum) return -1;
    k -= csum;
    cz++;
    // cout << "cz = " << cz << endl;
    // cout << "k = " << k << endl;
    // cout << "z = " << z << endl;
    k--;
    int ans = 0, f = cz;
    if (f <= 10) {
        int64_t last = z;
        for (int i = 0; i < f; ++i) {
            // cout << "k = " << k << endl;
            // cout << "last = " << last << endl;
            int64_t p = 0;
            for (int d = 60; d >= 0; --d) {
                if (p + (1LL << d) >= last) continue;
                if (Choose(p + (1LL << d), f - i) <= k) p += (1LL << d);
            }
            assert(Choose(p, f - i) <= k);
            (ans += fpow(2, p)) %= kMod;
            k -= Choose(p, f - i);
            last = p;
        }
    } else {
        // cout << "cz = " << cz << endl;
        for (int i = min(499, (int)z - 1); i >= 0; --i) {
            // cout << "i = " << i << " k = " << k << " ck[i][f] = " << ck[i][f] << endl;
            if (f > 0 && ck[i][f] <= k) {
                k -= ck[i][f];
                f--;
                (ans += pw[i]) %= kMod;
            }
        }
    }
    // cout << "ans = " << ans << endl;
    (ans += fpow(2, m)) %= kMod;
    (ans += kMod - fpow(2, z + 1)) %= kMod;
    assert(k == 0);
    return ans;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < 500; ++i) {
        ck[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            ck[i][j] = Add(ck[i - 1][j], ck[i - 1][j - 1]);
        }
    }
    pw[0] = 1;
    for (int i = 1; i < 500; ++i) pw[i] = (pw[i - 1] + pw[i - 1]) % kMod;
    while (t--) {
        int64_t n, k;
        cin >> n >> k;
        cout << Solve(n, k) << "\n";
    }
    // for (int n = 1; n <= 20; ++n) {
    //     for (int k = 1; k <= 20; ++k) {
    //         if (Solve(n, k) != BruteForce(n, k)) {
    //             // cout << "n = " << n << " k = " << k << endl;
    //             cout << Solve(n, k) << endl;
    //             cout << BruteForce(n, k) << endl;
    //             assert(false);
    //             return 0;
    //         }
    //     }
    // }
}

