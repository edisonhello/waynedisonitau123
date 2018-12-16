#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
const long long inf = 1e18 + 1;
int a[maxn], fr[maxn], n, k;
long long s[maxn];

struct result {
    long long m; int v;
    result(): m(0), v(0) {}
    result(long long a, int b): m(a), v(b) {}
    result operator+(const result &r) const { return result(m + r.m, v + r.v); }
    bool operator<(const result &r) const { return m == r.m ? v < r.v : m < r.m; }
    bool operator>(const result &r) const { return m == r.m ? v > r.v : m > r.m; }
} dp[maxn];

struct segment { int i, l, r; };

long long calc(int l, int r) {
    int m = (l + r) >> 1;
    return a[m] * 1ll * (m - l) - (s[m - 1] - s[l - 1]) + (s[r] - s[m]) - a[m] * 1ll * (r - m);
}

result f(int l, int r, long long c) { return dp[l] + result(calc(l + 1, r) + c, 1); }

result check(long long c) {
    dp[0] = { 0, 0 };
    deque<segment> dq; dq.push_back({ 0, 1, n });
    for (int i = 1; i <= n; ++i) {
        dp[i] = f(dq.front().i, i, c);
        while (dq.size() && dq[0].r < i + 1) dq.pop_front();
        dq.front().l = i + 1;
        while (dq.size() && f(i, dq.back().l, c) < f(dq.back().i, dq.back().l, c)) dq.pop_back();
        segment ins = { i, i + 1, n };
        if (dq.size()) {
            int t = dq.back().l, d = 0;
            while ((1 << d) <= dq.back().r - dq.back().l + 1) ++d;
            while (d--) if (t + (1 << d) <= dq.back().r) {
                if (f(i, t + (1 << d), c) > f(dq.back().i, t + (1 << d), c)) t += (1 << d);
            }
            dq.back().r = t; ins.l = t + 1;
        }
        if (ins.l <= n) dq.push_back(ins);

    }
    return dp[n];
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
    int d = 0;
    long long c = s[n];
    while ((1ll << d) <= c) ++d;
    while (d--) if (c - (1ll << d) >= 0) {
        result r = check(c - (1ll << d));
        if (r.v == k) return 0 * printf("%lld\n", r.m - (c - (1ll << d)) * k);
        if (r.v < k) c -= (1ll << d);
    }
    result r = check(c);
    printf("%lld\n", r.m - c * k);
}
