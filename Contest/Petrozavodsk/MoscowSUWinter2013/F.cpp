#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
const int maxc = 1e7;
const int inf = 3e6;
int a[maxn], lc[maxc], rc[maxc];
int s[maxn];

struct line {
    int a;
    long long b;
    line() = default;
    line(int a, long long b) : a(a), b(b) {}
    long long operator()(int x) const { 
        return a * 1ll * x + b; 
    }
};

line st[maxc];

int gnode() {
    static int sz = 0;
    st[sz] = line(-1e9, -1e18);
    lc[sz] = rc[sz] = -1;
    return sz++;
}

void add(int l, int r, line tl, int o) {
    int m = (l + r) / 2;
    bool lcp = st[o](l) < tl(l);
    bool mcp = st[o](m) < tl(m);
    if (mcp) swap(st[o], tl);
    if (r - l == 1) return;
    if (lcp != mcp) {
        if (lc[o] == -1) lc[o] = gnode();
        add(l, m, tl, lc[o]);
    } else {
        if (rc[o] == -1) rc[o] = gnode();
        add(m, r, tl, rc[o]);
    }
}

long long query(int l, int r, int x, int o) {
    if (r - l == 1) return st[o](x);
    int m = (l + r) >> 1;
    long long res = st[o](x);
    if (x < m && lc[o] != -1) res = max(res, query(l, m, x, lc[o]));
    else if (x >= m && rc[o] != -1) res = max(res, query(m, r, x, rc[o]));
    return res;
}

int lt[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    lt[0] = gnode();
    add(-inf, inf, line(0, 0), lt[0]);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        lt[i] = gnode();
        add(-inf, inf, line(0, 0), lt[i]);
        for (int j = 1; j < i; ++j) {
            long long d = s[i] * 1ll * s[j] - s[j] * 1ll * s[j] + query(-inf, inf, s[i], lt[j]);
            /* for (int k = 0; k < j; ++k) {
               dp[i][j] = max(dp[i][j], dp[j][k] + (s[i] - s[j]) * (s[j] - s[k]));
               } */
            // dp[i][j] = s[i] * s[i] + s[j] * s[j] + query(-inf, inf, s[i], lt[j]);
            // printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
            add(-inf, inf, line(-s[j], d + s[i] * 1ll * s[j]), lt[i]);
            if (i == n) ans = max(ans, d);
        }
    }
    printf("%lld\n", ans);
}
