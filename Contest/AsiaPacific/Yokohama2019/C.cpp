#include <bits/stdc++.h>
using namespace std;

const int kN = 2e5 + 5;
const int kL = 1e9 + 5;
const long long kInf = 1e15 + 5;
int c[kN], l[kN], r[kN];
long long dp[kN];

struct Line {
    mutable int64_t a, b, p;
    bool operator<(const Line &rhs) const { return a < rhs.a; }
    bool operator<(int64_t x) const { return p < x; }
};

struct ConvexHull : multiset<Line, less<>> {
    int64_t Div(int64_t a, int64_t b) {
        return a / b - ((a^ b) < 0 && a % b);
    }
    bool Isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = kInf;
            return false;
        }
        if (x->a == y->a) {
            x->p = x->b > y->b ? kInf : -kInf;
        } else {
            x->p = Div(y->b - x->b, x->a - y->a);
        }
        return x->p >= y->p;
    }
    void Insert(int64_t a, int64_t b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (Isect(y, z)) z = erase(z);
        if (x != begin() && Isect(--x, y)) Isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p == y->p) Isect(x, erase(y));
    }
    int64_t Query(int64_t x) {
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
};

const int kC = 20'000'000;
ConvexHull nd[kC];
int lc[kC], rc[kC], rt[4], sz;

int gnode() {
    lc[sz] = -1;
    rc[sz] = -1;
    return sz++;
}

void Modify(int l, int r, int p, long long a, long long b, int o) {
    nd[o].Insert(a, b);
    if (r - l == 1) return;
    int m = (l + r) >> 1;
    if (p < m) {
        if (lc[o] == -1) lc[o] = gnode();
        Modify(l, m, p, a, b, lc[o]);
    } else {
        if (rc[o] == -1) rc[o] = gnode();
        Modify(m, r, p, a, b, rc[o]);
    }
}

long long Query(int l, int r, int ql, int qr, long long x, int o) {
    if (o == -1) return -kInf;
    if (l >= qr || ql >= r) return 0;
    if (l >= ql && r <= qr) return nd[o].Query(x);
    int m = (l + r) >> 1;
    return max(Query(l, m, ql, qr, x, lc[o]), Query(m, r, ql, qr, x, rc[o]));
}

// multiset<

int main() {
    int n, m, x, y; scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &c[i], &l[i], &r[i]);

    vector<tuple<int, int, int>> seg;
    for (int i = 1; i <= m; ++i) seg.emplace_back(l[i], r[i], c[i]);
    sort(seg.begin(), seg.end(), [&](auto a, auto b) { return get<1>(a) < get<1>(b); });

    for (int i = 0; i < m; ++i) {
        l[i + 1] = get<0>(seg[i]);
        r[i + 1] = get<1>(seg[i]);
        c[i + 1] = get<2>(seg[i]);
    }

    for (int i = 1; i <= 3; ++i) rt[i] = gnode();

    dp[0] = 0;
    long long ans = 0;
    for (int i = 1; i <= m; ++i) {
        dp[i] = -kInf;
        for (int j = 1; j <= 3; ++j) {
            if (j == i) continue;
            dp[i] = max(dp[i], Query(0, kL, l[i], kL, 
        }
        dp[i] = Query();
        for (int j = 0; j < i; ++j) {
            if (r[j] >= l[i]) {
                long long cur = dp[j];
                if (j != 0 && c[j] != c[i]) cur -= 1LL * (x + x + y) * (r[j] - l[i] + 1);
                else cur -= 1LL * x * (r[j] - l[i] + 1);
                dp[i] = max(dp[i], cur);
            } else {
                dp[i] = max(dp[i], dp[j]);
            }
        }
        dp[i] += 1LL * x * (r[i] - l[i] + 1);
        ans = max(ans, dp[i]);
    }
    // for (int _ = 1; _ <= m; ++_) {
    //     int i = od[_ - 1];
    //     for (int j = 0; j <= m; ++j) {
    //         if (r[j] >= r[i]) continue;
    //         printf("j = %d\n", j);
    //         if (r[j] > l[i]) {
    //             printf("case1\n");
    //             long long cur = dp[j] + 1LL * x * (r[i] - l[i] + 1);
    //             if (c[j] != c[i]) cur -= 1LL * (x + y) * (r[j] - l[i] + 1);
    //             dp[i] = max(dp[i], cur);
    //         } else {
    //             printf("case2\n");
    //             dp[i] = max(dp[i], dp[j] + 1LL * x * (r[i] - l[i] + 1));
    //         }
    //     }
    //     ans = max(ans, dp[i]);
    //     printf("dp[%d] = %lld\n", i, dp[i]);
    // }
    printf("%lld\n", ans);
    return 0;
}
