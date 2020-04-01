#include <bits/stdc++.h>
using namespace std;
int64_t fmul(int64_t a, int64_t b, int64_t p) {
    int64_t res = 0;
    while (b > 0) {
        if (b & 1) (res += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return res;
}

int64_t f(int64_t x, int64_t n, int64_t p) {
    return (fmul(x, x, n) + p) % n;
}

map<int64_t, int> fc;

const vector<int64_t> kP = {2, 325, 9375, 28178, 450775, 9780504, 1795265022 };


int64_t fpow(int64_t a, int64_t n, int64_t p) {
    int64_t res = 1;
    while (n > 0) {
        if (n & 1) res = fmul(res, a, p);
        a = fmul(a, a, p);
        n >>= 1;
    }
    return res;
}

bool Check(int64_t a, int64_t u, int64_t n, int t) {
    a = fpow(a, u, n);
    if (a == 0) return true;
    if (a == 1 || a == n - 1) return true;
    for (int i = 0; i < t; ++i) {
        a = fmul(a, a, n);
        if (a == 1) return false;
        if (a == n - 1) return true;
    }
    return false;
}

bool IsPrime(int64_t n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    int64_t u = n - 1;
    int t = 0;
    for (; !(u & 1); u >>= 1, ++t);
    for (long long i : kP) {
        if (!Check(i, u, n, t)) return false;
    }
    return true;
}

void PollardRho(int64_t n) {
    if (n == 1) return;
    if (IsPrime(n)) {
        fc[n]++;
        return;
    }
    if (n % 2 == 0) {
        fc[2]++;
        PollardRho(n / 2);
        return;
    }
    int64_t x = 2, y = 2, d = 1, p = 1;
    while (true) {
        if (d != n && d != 1) {
            PollardRho(d);
            PollardRho(n / d);
            return;
        }
        if (d == n) ++p;
        x = f(x, n, p);
        y = f(f(y, n, p), n, p);
        d = __gcd(abs(x - y), n);
    }
}


int main() {
    int64_t m;
    cin >> m;
    PollardRho(m);
    vector<pair<int64_t, int>> pf;
    for (auto it : fc) {
        pf.emplace_back(it.first, it.second);
    }

    constexpr int kMod = 998244353;
    int res = 0;

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    auto Dfs = [&](auto self, int i, int64_t x, vector<pair<int64_t, int>> kf) {
        if (i == pf.size()) {
            int cnt = 1, gc = 0;
            int64_t pd = 1;
            for (int j = 0; j < kf.size(); ++j) {
                cnt *= kf[j].second + 1;
                if ((pf[j].second - kf[j].second) & 1) gc++;
            }
            int ad = x == 1 ? 1 : (gc & 1) ? kMod - fpow(2, gc) : fpow(2, gc);
            res += 1LL * ad * (fpow(2, cnt) - 1) % kMod;
            res %= kMod;
            return;
        } 
        kf.push_back(pf[i]);
        for (int j = 0; j <= min(2, pf[i].second); ++j) {
            self(self, i + 1, x, kf);
            x = x * pf[i].first;
            kf.back().second--;
        }
    };

    Dfs(Dfs, 0, 1, vector<pair<int64_t, int>>());
    // sort(fc.begin(), fc.end());
    // int k = fc.size();
    // map<int64_t, int> cnt; 
    // map<int64_t, int> rt; 
    // set<int64_t> st;
    // for (int i = 0; i < k; ++i) cout << fc[i] << " ";
    // cout << endl;
    // for (int s = 0; s < (1 << k); ++s) {
    //     // cout << "s = " << s << endl;
    //     int64_t dv = 1;
    //     for (int i = 0; i < k; ++i) {
    //         if (s >> i & 1) dv *= fc[i];
    //     }
    //     // cout << "dv = " << dv << endl;
    //     if (cnt.find(dv) == cnt.end()) {
    //         map<int64_t, int> cp;
    //         for (int i = 0; i < k; ++i) {
    //             if (s >> i & 1) cp[fc[i]]++;
    //         }
    //         int res = 1;
    //         int rk = 0;
    //         for (auto it : cp) {
    //             res *= it.second + 1;
    //             if (it.second >= 3) st.insert(dv);
    //             if (it.second & 1) rk++;
    //         }
    //         cnt[dv] = res;
    //         rt[dv] = rk;
    //     }
    // }
    cout << res << "\n";
}
