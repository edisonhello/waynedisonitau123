

#include <bits/stdc++.h>
using namespace std;

template <typename T>
tuple<T, T, T> extgcd(T a, T b) {
    if (!b) return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = extgcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

long long fmul(long long a, long long b, long long p) {
    long long res = 0;
    while (b > 0) {
        if (b & 1) (res += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return res;
}

long long crt(vector<int> mod, vector<int> a) {
    long long mult = 1;
    int n = (int)mod.size();
    long long res = 0;
    for (int i = 0; i < n; ++i) mult *= mod[i];
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j)
            assert(__gcd(mod[i], mod[j]) == 1);
    }
    for (int i = 0; i < n; ++i) {
        long long ni = mult / mod[i];
        long long d, x, y;
        tie(d, x, y) = extgcd(ni, 1ll * mod[i]);
        ((x %= mult) += mult) %= mult;
        res += fmul(ni, fmul(x, a[i], mult), mult);
        res %= mult;
    }
    return res;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        vector<int> v(n), r(n), w;
        for (int i = 0; i < n; ++i) scanf("%d%d", &v[i], &r[i]);
        for (int i = 0; i < n; ++i) w.push_back(v[i] * 210 + 23);
        long long x = crt(w, r);
        for (int i = 0; i < n; ++i) assert(x % w[i] == r[i]);
        long long y = sqrt(x);
        while (y * y > x) --y;
        long long z = x - y * y;
        puts("NUM 210");
        puts("MUL");
        puts("NUM 23");
        puts("ADD");
        puts("DUP");
        puts("DUP");
        printf("NUM %lld\n", z);
        puts("SWP");
        puts("MOD");
        puts("SWP");
        puts("DUP");
        printf("NUM %lld\n", y);
        puts("SWP");
        puts("MOD");
        puts("DUP");
        puts("MUL");
        puts("SWP");
        puts("POP");
        puts("ADD");
        puts("SWP");
        puts("MOD");
        puts("END");
        puts("");
    }
}
