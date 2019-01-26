#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<pair<int, long long>> g[maxn];
int dp2[2][maxn];

struct result {
    long long m;
    int v;
    result(): m(0), v(0) {}
    result(long long m, int v): m(m), v(v) {}
    result operator+(const result &r) const {
        return result(m + r.m, v + r.v);
    }
    result operator-(const result &r) const {
        return result(m - r.m, v - r.v);
    }
    bool operator<(const result &r) const {
        return m == r.m ? v < r.v : m < r.m;
    }
    bool operator>(const result &r) const {
        return m == r.m ? v < r.v : m > r.m;
    }
};

result dp[2][maxn];

void dfs(int x, int p, long long c) {
    dp[0][x] = result(0, 0);
    dp[1][x] = result(-1e18, 0);
    result sum = result(0, 0);
    for (auto [u, d] : g[x]) {
        if (u == p) continue;
        dfs(u, x, c);
        dp[0][x] = dp[0][x] + max(dp[1][u], dp[0][u]);
    }
    for (auto [u, d] : g[x]) {
        if (u == p) continue;
        result cur = dp[0][x] + dp[0][u] - max(dp[1][u], dp[0][u]) + result(d - c, 1);
        dp[1][x] = max(dp[1][x], cur);
    }
}

void dfs2(int x, int p) {
    dp2[0][x] = 0;
    dp2[1][x] = -1e9;
    for (auto [u, d] : g[x]) {
        if (u == p) continue;
        dfs2(u, x);
        dp2[0][x] += max(dp2[1][u], dp2[0][u]);
    }
    for (auto [u, d] : g[x]) {
        if (u == p) continue;
        int cur = dp2[0][x] + dp2[0][u] - max(dp2[1][u], dp2[0][u]) + 1;
        dp2[1][x] = max(dp2[1][x], cur);
    }
}

bool invalid(int k) {
    dfs2(0, -1);
    return max(dp2[0][0], dp2[1][0]) < k;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    const long long offset = 2000001 * 1ll * n;
    for (int i = 0; i < n - 1; ++i) {
        int x, y, c; scanf("%d%d%d", &x, &y, &c);
        long long cc = c + offset;
        --x, --y;
        g[x].emplace_back(y, cc);
        g[y].emplace_back(x, cc);
    }
    if (invalid(k)) {
        puts("Impossible");
        return 0;
    }
    long long c = 0;
    /* for (int i = 0; i <= 15; ++i) {
        dfs(0, -1, i);
        result r = max(dp[0][0], dp[1][0]);
        printf("%d ", r.v);
    } */
    for (int d = 60; d >= 0; --d) {
        long long x = c + (1ll << d);
        dfs(0, -1, x);
        result r = max(dp[0][0], dp[1][0]);
        if (r.v == k) {
            printf("%lld\n", r.m + x * k - k * offset);
            return 0;
        }
        if (r.v > k) c = x;
    }
    dfs(0, -1, c);
    result r = max(dp[0][0], dp[1][0]);
    printf("%lld\n", r.m + k * c - k * offset);
    return 0;
}
