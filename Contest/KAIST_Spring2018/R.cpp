

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int maxc = 10001;
int n, f[maxn], c[maxn], l[maxn], v[maxn], pos[maxn];
long long dp[maxn];

struct line_t {
    int a; long long b;
    line_t() {}
    line_t(int a, long long b): a(a), b(b) {}
    long long operator()(int x) const {
        return a * 1ll * x + b;
    }
};

struct node {
    node *lc, *rc;
    line_t ln;
    node() {
        ln = line_t(-maxn, -1e15);
        lc = nullptr;
        rc = nullptr;
    }
    void modify(int, int, line_t);
    long long query(int l, int r, int x) {
        long long res = ln(x);
        if (r - l == 1) return res;
        if (x * 2 < (l + r)) {
            if (lc) res = max(res, lc->query(l, (l + r) >> 1, x));
        } else {
            if (rc) res = max(res, rc->query((l + r) >> 1, r, x)); 
        }
        return res;
    }
} pool[4000000];
int ptr;

void node::modify(int l, int r, line_t tl) {
    bool lcp = ln(l) < tl(l);
    bool mcp = ln((l + r) >> 1) < tl((l + r) >> 1);
    if (mcp) swap(ln, tl);
    if (r - l == 1) return;
    if (lcp != mcp) {
        if (!lc) lc = &pool[ptr++];
        lc->modify(l, (l + r) >> 1, tl);
    } else {
        if (!rc) rc = &pool[ptr++];
        rc->modify((l + r) >> 1, r, tl);
    }
}

node *fw[maxn];

void add(int p, int a, long long b) {
    for (int i = p + 1; i <= n; i += i & -i)
        fw[i]->modify(0, maxc, line_t(a, b));
}

long long query(int p, int x) {
    long long res = -1e18;
    for (int i = p + 1; i > 0; i -= i & -i)
        res = max(res, fw[i]->query(0, maxc, x));
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &f[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &l[i]);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) v[i] = i;
    sort(v, v + n, [&](int i, int j) {
        return f[i + 1] + i + 1 > f[j + 1] + j + 1;
    });
    for (int i = 0; i < n; ++i) pos[v[i]] = i;
    for (int i = 0; i <= n; ++i) fw[i] = &pool[ptr++];
    add(pos[0], f[1] + 1, 0);
    for (int i = 1; i <= n; ++i) {
        dp[i] = -1e15;
        int p = -1;
        for (int d = 17; d >= 0; --d) {
            int y = p + (1 << d);
            if (y >= n) continue;
            if (f[v[y] + 1] + v[y] + 1 >= l[i] + i)
                p += (1 << d);
        }
        if (p >= 0) dp[i] = query(p, c[i]) - i * 1ll * c[i];
        if (i + 1 <= n && dp[i] >= 0) add(pos[i], f[i + 1] + i + 1, dp[i]);
    }
    if (dp[n] >= 0) printf("%lld\n", dp[n]);
    else puts("Impossible");
}
