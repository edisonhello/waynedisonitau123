#include <bits/stdc++.h>
using namespace std;

#define int long long
const int maxn = 3e5 + 5;
pair<int, int> p[maxn];
int n;

pair<int, int> inter(int l, int r, int a, int b) {
    return make_pair(max(a, l), min(r, b));
}

bool check(int x) {
    int l = 0, r = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        int tl = p[i].second - x, tr = p[i].second + x;
        int xl, xr; tie(xl, xr) = inter(l, r, tl, tr);
        // printf("i = %d l = %d r = %d\n", i, l, r);
        if (xl > xr) {
            if (tr < l) return false;
            else ++cnt, l = tl, r = tr;
        } else {
            l = xl;
            r = xr;
        }
    }
    // printf("check x = %lld cnt = %lld\n", x, cnt);
    return cnt <= 2;
}

int32_t main() {
    scanf("%lld", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld%lld", &p[i].first, &p[i].second);
        p[i].second *= 2;
    }
    sort(p, p + n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        if (p[i].first == 0 && p[i].second != 0) mx = max(mx, p[i].second);
    }
    int d = 31, ans = 2e9 + 2;
    while (d--) {
        int x = ans - (1 << d);
        if (x < mx) continue;
        if (check(x)) ans = x;
    }
    printf("%lld\n", ans / 2);
    if (ans & 1) puts(".5");
    else puts(".0");
    return 0;
}
