struct result {
    long long m; int v;
    result(): m(0), v(0) {}
    result(long long a, int b): m(a), v(b) {}
    result operator+(const result &r) const { return result(m + r.m, v + r.v); }
    bool operator<(const result &r) const { return m == r.m ? v < r.v : m < r.m; }
    bool operator>(const result &r) const { return m == r.m ? v > r.v : m > r.m; }
} dp[maxn];

result check(int p);

long long alien() {
    long long c = inf;
    for (int d = 60; d >= 0; --d) {
        if (c - (1ll << d) < 0) continue;
        result r = check(c - (1ll << d));
        if (r.v == k) return r.m - (c - (1ll << d)) * k;
        if (r.v < k) c -= (1ll << d);
    }
    result r = check(c);
    return r.m - c * k;
}
