#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int n, h[maxn], lt[maxn], rt[maxn];

long long calc(int l, int r, int k) {
    /* long long res = 0;
    for (int i = 0; i <= l; ++i) {
        for (int j = 0; j <= r; ++j)
            res += i + j + 1 <= k;
    }
    return res; */
    l = min(l, k);
    if (k - l >= r + 1) return (r + 1) * 1ll * (l + 1);
    if (k <= r + 1) return (2 * k - l) * 1ll * (l + 1) / 2;
    return (k - r) * 1ll * (r + 1) + (r + 1 - (k - l)) * 1ll * (r + (k - l)) / 2;
}

long long calc2(int l, int r, int tg) {
    return calc(l, r, tg) - calc(l, r, tg - 1);
}

long long check(long long x) {
    // count how many elements are <= x
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        long long t = x / h[i];
        // printf("x = %lld t = %lld\n", x, min(t, 1ll * n));
        res += calc(i - lt[i], rt[i] - i, min(t, 1ll * n));
    }
    // printf("check x = %lld res = %lld\n", x, res);
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &h[i]);
    for (int i = 0; i < n; ++i) {
        lt[i] = i - 1;
        while (lt[i] >= 0 && h[lt[i]] >= h[i])
            lt[i] = lt[lt[i]];
    }
    for (int i = n - 1; i >= 0; --i) {
        rt[i] = i + 1;
        while (rt[i] < n && h[rt[i]] > h[i])
            rt[i] = rt[rt[i]];
    }
    for (int i = 0; i < n; ++i) ++lt[i], --rt[i];
    long long l, r; scanf("%lld%lld", &l, &r);
    long long al = 0, ar = 0;
    for (int d = 50; d >= 0; --d) {
        if (check(al + (1ll << d) - 1) <= l - 1)
            al += (1ll << d);
    }
    // printf("al = %lld\n", al);
    for (int d = 50; d >= 0; --d) {
        if (check(ar + (1ll << d) - 1) <= r - 1)
            ar += (1ll << d);
    }
    // printf("ar = %lld\n", ar);
    if (al == ar) {
        for (int i = 0; i < r - l + 1; ++i)
            printf("%lld ", al);
        puts("");
        return 0;
    }
    long long cal = check(al);
    vector<long long> ans;
    // printf("cnt al = %lld\n", cal - l + 1);
    for (int i = 0; i < cal - l + 1; ++i)
        ans.push_back(al);
    long long car = check(ar - 1);
    // printf("cnt ar = %lld\n", r - car);
    for (int i = 0; i < r - car; ++i) 
        ans.push_back(ar);
    for (int i = 0; i < n; ++i) {
        long long lb = (al + 1) / h[i], rb = (ar - 1 + h[i] - 1) / h[i];
        while (lb * h[i] < al + 1) ++lb;
        while (rb * h[i] > ar - 1) --rb;
        if (lb > rb) continue;
        // printf("lb = %lld rb = %lld\n", lb, rb);
        while (lb <= min(1ll * n, rb)) {
            long long c = calc2(i - lt[i], rt[i] - i, lb);
            if (c == 0) break;
            // printf("l = %d r = %d t = %lld\n", i - lt[i], rt[i] - i, lb);
            // printf("c = %lld\n", c);
            while (c--) ans.push_back(h[i] * lb);
            ++lb;
        }
    }
    assert((int)ans.size() == r - l + 1);
    sort(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i)
        printf("%lld ", ans[i]);
    puts("");
    return 0;
}
