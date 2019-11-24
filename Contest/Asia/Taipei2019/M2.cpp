#include <bits/stdc++.h>
using namespace std;

int fpow(int a, long long n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % p;
        a = 1LL * a * a % p;
        n >>= 1;
    }
    return res;
}

struct Solver {
    vector<int> fc;
    int p, d, pd;

    Solver() = default;
    Solver(int p, int d) : p(p), d(d) {
        pd = 1;
        for (int i = 0; i < d; ++i) pd *= p;
        fc.resize(pd);
        fc[0] = 1;
        for (int i = 1; i < pd; ++i) {
            if (i % p == 0) fc[i] = fc[i - 1];
            else fc[i] = 1LL * fc[i - 1] * i % pd;
        }
    }

    long long V(long long m) {
        if (m == 0) return 0;
        return m / p + V(m / p);
    }

    int f(long long m) {
        if (m == 0) return 1;
        int res = 1LL * f(m / p) * fc[m % pd] % pd;
        res = 1LL * res * fpow(fc[pd - 1], m / pd, pd) % pd;
        return res;
    }
};

const int kN = 17'000'000;
Solver solver[kN];
long long vp[kN];

template <class T>
tuple<T, T, T> ExtGcd(T a, T b) {
    if (!b) return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = ExtGcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

long long CRT(vector<int> mod, vector<int> a) {
    // for (int i : mod) printf("%d ", i); puts("");
    // for (int i : a) printf("%d ", i); puts("");
    long long mult = mod[0];
    int n = mod.size();
    long long res = a[0];
    for (int i = 1; i < n; ++i) {
        long long d, x, y;
        tie(d, x, y) = ExtGcd(mult, 1LL * mod[i]);
        if ((a[i] - res) % d != 0) return -1;
        long long nmult = mult / __gcd(mult, 1LL * mod[i]) * mod[i];
        res += x * ((a[i] - res) / d) % nmult * mult % nmult;
        mult = nmult;
        ((res %= mult) += mult) %= mult;
    }
    return res;
}

int Inv(int a, int d) {
    assert(__gcd(a, d) == 1);
    int t, x, y;
    tie(t, x, y) = ExtGcd(a, d);
    ((x %= d) += d) %= d;
    // cout << "a = " << a << " d = " << d << " x = " << x << endl;
    assert(1LL * a * x % d == 1);
    return x;
}

int main() {
    long long m, n, d;
    cin >> m >> n >> d;
    vector<pair<int, int>> pd;
    int e = d;
    for (int i = 2; i <= d; ++i) {
        if (d % i == 0) {
            int cnt = 0;
            while (d % i == 0) d /= i, cnt++;
            pd.emplace_back(i, cnt);
        }
    }
    long long k = 5e18;
    for (auto it : pd) {
        solver[it.first] = Solver(it.first, it.second);
        long long mp = solver[it.first].V(m);
        long long np = solver[it.first].V(n);
        long long mnp = solver[it.first].V(m - n);
        long long t = mp - np - mnp;
        assert(t >= 0);
        vp[it.first] = t;
        k = min(k, t / it.second);
    }
    // cout << "k = " << k << endl;
    vector<int> mod;
    vector<int> aa;
    for (auto it : pd) {
        int fm = solver[it.first].f(m);
        int fn = solver[it.first].f(n);
        int fmn = solver[it.first].f(m - n);
        int pdd = solver[it.first].pd;
        fm = 1LL * fm * Inv(fn, pdd) % pdd * Inv(fmn, pdd) % pdd;
        int a = it.second;
        long long b = vp[it.first] - 1LL * k * a;
        // fprintf(stderr, "p = %d f = %d a = %d b = %lld\n", it.first, fm, a, b);
        long long mult = 1;
        for (int i = 0; i < it.second; ++i) mult *= it.first;
        if (b >= a) {
            mod.push_back(mult);
            aa.push_back(0);
            continue;
        }
        mod.push_back(mult);
        long long pb = 1;
        for (int i = 0; i < b; ++i) pb *= it.first;
        int pp = 1LL * fm * pb % pdd;
        pp = 1LL * pp * Inv(fpow((e / pdd), k, pdd), pdd) % pdd;
        aa.push_back(pp);
    }
    printf("%lld\n", CRT(mod, aa));
    // printf("k = %lld\n", k);
    return 0;
}
