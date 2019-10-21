#include <bits/stdc++.h>
using namespace std;
 
const int kInf = 1'000'000'000 + 1;
 
namespace lichao {
 
struct Line {
    int a;
    long long b;
    Line() : a(0), b(0) {}
    Line(int a, long long b) : a(a), b(b) {}
 
    long long operator()(int x) const {
        return 1LL * a * x + b;
    }
};
 
const int kC = 30'000'000;
Line st[kC];
int sz, lc[kC], rc[kC];
 
void Init() { sz = 0; }
 
int gnode() {
    st[sz] = Line(-1e9, -1e18);
    lc[sz] = rc[sz] = -1;
    return sz++;
}
 
void Modify(int l, int r, Line tl, int o) {
    int m = (l + r) >> 1;
    bool lcp = st[o](l) < tl(l);
    bool mcp = st[o](m) < tl(m);
    if (mcp) swap(st[o], tl);
    if (r - l == 1) return;
    if (lcp != mcp) {
        if (lc[o] == -1) lc[o] = gnode();
        Modify(l, m, tl, lc[o]);
    } else {
        if (rc[o] == -1) rc[o] = gnode();
        Modify(m, r, tl, rc[o]);
    }
}
 
long long Query(int l, int r, int x, int o) {
    long long res = st[o](x);
    if (r - l == 1) return res;
    int m = (l + r) >> 1;
    if (x < m && lc[o] != -1) res = max(res, Query(l, m, x, lc[o]));
    if (x >= m && rc[o] != -1) res = max(res, Query(m, r, x, rc[o]));
    return res;
}
 
}
 
struct Machine {
    int d, r, p, g;
 
    Machine() = default;
    Machine(int d, int r, int p, int g) : d(d), r(r), p(p), g(g) {}
 
    bool operator<(const Machine &rhs) const {
        return d < rhs.d;
    }
};
 
const int kN = 1e5 + 5;
Machine a[kN];
long long dp[kN];
 
int main() {
    int n, c, d, tc = 0;
    while (scanf("%d%d%d", &n, &c, &d) != EOF) {
        if (!n && !c && !d) break;
        for (int i = 1; i <= n; ++i) {
            int d, p, r, g;
            scanf("%d%d%d%d", &d, &p, &r, &g);
            a[i] = Machine(d, r, p, g);
        }
        sort(a + 1, a + n + 1);
        a[n + 1] = Machine(d + 1, 0, 0, 0);
        dp[0] = c;
        lichao::Init();
        int root = lichao::gnode();
        lichao::Modify(0, kInf, lichao::Line(0, c), root);
        for (int i = 1; i <= n + 1; ++i) {
            dp[i] = lichao::Query(0, kInf, a[i].d, root);
            if (dp[i] >= a[i].p) {
                lichao::Line line(a[i].g, dp[i] - 1LL * a[i].d * a[i].g - a[i].g + a[i].r - a[i].p);
                lichao::Modify(0, kInf, line, root);
            }
            // printf("machine d = %d p = %d r = %d g = %d\n", a[i].d, a[i].p, a[i].r, a[i].g);
            // for (int j = 0; j < i; ++j) {
            //     if (dp[j] < a[j].p) continue;
            //     dp[i] = max(dp[i], dp[j] + 1LL * (a[i].d - a[j].d - 1) * a[j].g + a[j].r - a[j].p);
            // }
        }
        printf("Case %d: %lld\n", ++tc, dp[n + 1]);
    }
}
