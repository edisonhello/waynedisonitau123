#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const long long inf = 1e15;
vector<pair<int, int>> g[maxn];
long long d[maxn][maxn];
bool v[maxn];
int k, u[maxn], s[maxn], t[maxn];
long long dp[maxn], cost[maxn][maxn], st[maxn][maxn];
long long wait[maxn][maxn];

template <typename t>
using heap = priority_queue<t, vector<t>, greater<t>>;

void dijk(int s) {
    for (int i = 0; i < maxn; ++i) d[s][i] = inf;
    d[s][s] = 0;
    memset(v, false, sizeof(v));
    heap<pair<long long, int>> pq;
    pq.emplace(0, s);
    while (pq.size()) {
        int x = pq.top().second; pq.pop();
        if (v[x]) continue;
        v[x] = true;
        for (const auto &e : g[x]) {
            int u = e.first, w = e.second;
            if (d[s][u] > d[s][x] + w) {
                d[s][u] = d[s][x] + w;
                pq.emplace(d[s][u], u);
            }
        }
    }
}

bool check(long long x) {
    for (int i = 0; i < maxn; ++i) dp[i] = inf;
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) st[i][j] = inf;
    }
    for (int i = 1; i <= k; ++i) {
        int last = 0;
        for (int j = i; j <= k; ++j) {
            wait[i][j] = wait[i][j - 1] + d[last][u[j]];
            st[i][j] = min(st[i][j - 1], s[j] + x - wait[i][j]);
            last = u[j];
        }
    }
    dp[0] = 0;
    // printf("st[3][3] = %lld\n", st[3][3]);
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < i; ++j) {
            long long p = max(dp[j] + d[0][u[j]], 1ll * t[i]);
            long long tg = st[j + 1][i];
            if (p > tg) continue;
            dp[i] = min(dp[i], p + cost[j + 1][i]);
        }
        // printf("dp[%d] = %lld\n", i, dp[i]);
    }
    return dp[k] != inf;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x, y, d; scanf("%d%d%d", &x, &y, &d);
        --x, --y;
        g[x].emplace_back(y, d);
        g[y].emplace_back(x, d);
    }
    for (int i = 0; i < n; ++i) dijk(i);
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) scanf("%d%d%d", &s[i], &u[i], &t[i]), --u[i];
    for (int i = 1; i <= k; ++i) {
        int last = 0;
        for (int j = i; j <= k; ++j) 
            cost[i][j] = cost[i][j - 1] + d[last][u[j]],
            last = u[j];
    }
    // check(6);
    int d = 61;
    long long ans = inf;
    while (d--) {
        long long t = ans - (1ll << d);
        if (t < 0) continue;
        if (check(t)) ans = t;
    }
    printf("%lld\n", ans);
    return 0;
}
