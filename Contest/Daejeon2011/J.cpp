#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 1010;
const int inf = 1e9;
pair<int, int> p[maxn], q[maxn];
pair<int, int> dp[maxn], dq[maxn];
int ds[maxn], sz;

int bit1[maxn];
int bit2[maxn];

inline int gtx() {
    const int N = 4096;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if ((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}

inline bool rit(int &x) {
    char c = 0; bool flag = false;
    while (c = gtx(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
    c == '-' ? (flag = true, x = 0) : (x = c - '0');
    while (c = gtx(), c >= '0' && c <= '9') x = x * 10 + c - '0';
    if (flag) x = -x;
    return true;
}


int query(int p, int *bit) {
    int res = inf;
    for (; p; p -= p & -p)
        res = min(res, bit[p]);
    return res;
}

int add(int p, int v, int *bit) {
    for (; p < sz + 100; p += p & -p)
        bit[p] = min(bit[p], v);
}

int solve(pair<int, int> *p, pair<int, int> *dp, int n, pair<int, int> *q, pair<int, int> *dq, int m) {
    for (int i = 0; i < sz + 100; ++i) {
        bit1[i] = inf;
        bit2[i] = inf;
    }

    int j = 0;
    int res = inf;
    for (int i = 0; i < n; ++i) {
        while (j < m && q[j].first >= p[i].first) {
            add(sz + 50 - dq[j].second, q[j].first + q[j].second, bit1);
            add(dq[j].second, q[j].first - q[j].second, bit2);
            ++j;
        }
        res = min(res, query(sz + 50 - dp[i].second, bit1) - p[i].first - p[i].second);
        res = min(res, query(dp[i].second, bit2) - p[i].first + p[i].second);
    }
    return res;
}

int main() {
    int t; rit(t);
    while (t--) {
        sz = 0;
        int n; rit(n);
        for (int i = 0; i < n; ++i) {
            rit(p[i].first);
            rit(p[i].second);
            // scanf("%d%d", &p[i].first, &p[i].second);
            // ds[sz++] = p[i].first;
            ds[sz++] = p[i].second;
        }
        int m; rit(m);
        for (int i = 0; i < m; ++i) {
            rit(q[i].first);
            rit(q[i].second);
            // scanf("%d%d", &q[i].first, &q[i].second);
            // ds[sz++] = q[i].first;
            ds[sz++] = q[i].second;
        }
        sort(ds, ds + sz);
        sz = unique(ds, ds + sz) - ds;
        // sort(ds.begin(), ds.end());
        // ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        for (int i = 0; i < n; ++i) {
            dp[i].first = p[i].first;
            // dp[i].first = lower_bound(ds, ds + sz, p[i].first) - ds + 1;
            dp[i].second = lower_bound(ds, ds + sz, p[i].second) - ds + 1;
        }
        for (int i = 0; i < m; ++i) {
            dq[i].first = q[i].first;
            // dq[i].first = lower_bound(ds, ds + sz, q[i].first) - ds + 1;
            dq[i].second = lower_bound(ds, ds + sz, q[i].second) - ds + 1;
        }
        sort(p, p + n, greater<pair<int, int>>());
        sort(dp, dp + n, greater<pair<int, int>>());
        sort(q, q + m);
        sort(dq, dq + m);
        printf("%d\n", min(solve(p, dp, n, q, dq, m), solve(q, dq, m, p, dp, n)));
    }
}
