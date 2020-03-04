#include <bits/stdc++.h>
using namespace std;

struct Solver {
    vector<int> fc;
    int p;

    Solver() = default;
    Solver(int p) : p(p) {
        fc.resize(p);
        fc[0] = 1;
        for (int i = 1; i < p; ++i) fc[i] = 1LL * fc[i - 1] * i % p;
    }

    long long V(long long m) {
        if (m == 0) return 0;
        return m / p + V(m / p);
    }

    int f(long long m) {
        if (m == 0) return 1;
        int res = 1LL * f(m / p) * fc[m % p] % p;
        if ((m / p) % 2 == 1) res = p - res;
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

int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % p;
        a = 1LL * a * a % p;
        n >>= 1;
    }
    return res;
}

int main() {
    long long m, n, d;
    cin >> m >> n >> d;
    vector<pair<int, int>> pd;
    for (int i = 2; i <= d; ++i) {
        if (d % i == 0) {
            int cnt = 0;
            while (d % i == 0) d /= i, cnt++;
            pd.emplace_back(i, cnt);
        }
    }
    long long k = 1e18;
    for (auto it : pd) {
        solver[it.first] = Solver(it.first);
        long long mp = solver[it.first].V(m);
        long long np = solver[it.first].V(n);
        long long mnp = solver[it.first].V(m - n);
        long long t = mp - np - mnp;
        assert(t >= 0);
        vp[it.first] = t;
        k = min(k, t / it.second);
    }
    vector<int> mod;
    vector<int> aa;
    for (auto it : pd) {
        int fm = solver[it.first].f(m);
        int fn = solver[it.first].f(n);
        int fmn = solver[it.first].f(m - n);
        fm = 1LL * fm * fpow(fn, it.first - 2, it.first) % it.first * fpow(fmn, it.first - 2, it.first) % it.first;
        int a = it.second;
        long long b = vp[it.first] - 1LL * k * a;
        // printf("p = %d f = %d a = %d b = %lld\n", it.first, fm, a, b);
        int long mult = 1;
        for (int i = 0; i < it.second; ++i) mult *= it.first;
        if (b >= a) {
            mod.push_back(mult);
            aa.push_back(0);
            continue;
        }
        mod.push_back(mult);
        long long pb = 1;
        for (int i = 0; i < b; ++i) pb *= it.first;
        aa.push_back(1LL * fm * pb);
    }
    printf("%lld\n", CRT(mod, aa));
    // printf("k = %lld\n", k);
    return 0;
}
