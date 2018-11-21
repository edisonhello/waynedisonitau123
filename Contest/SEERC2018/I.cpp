#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int deg[maxn], a[maxn];
vector<int> g[maxn];
bool anti[maxn][maxn], us[maxn], st[maxn], ed[maxn];
long long dp[maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    while (m--) {
        int x, y; scanf("%d%d", &x, &y);
        if (x > y) swap(x, y);
        g[y].push_back(x);
        ++deg[x];
        anti[x][y] = true;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (anti[i][j]) continue;
            ++deg[j];
            g[i].push_back(j);
        }
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0) {
            q.push(i);
            a[i] = 1;
        }
    }
    assert((int)q.size() == 1);
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int u : g[x]) {
            a[u] = max(a[u], a[x] + 1);
            if ((--deg[u]) == 0) {
                q.push(u);
            }
        }
    }
    for (int i = 1; i <= n; ++i) us[a[i]] = true;
    for (int i = 1; i <= n; ++i) assert(us[i]);
    st[1] = true;
    for (int i = 2; i <= n; ++i) {
        int small = n + 1;
        for (int j = i - 1; j >= 1; --j) small = min(small, a[j]);
        if (small > a[i]) st[i] = true;
    }
    ed[n] = true;
    for (int i = 1; i < n; ++i) {
        int big = 0;
        for (int j = i + 1; j <= n; ++j) big = max(big, a[j]);
        if (big < a[i]) ed[i] = true;
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (st[i]) {
            dp[i] = 1;
            if (ed[i]) ans += dp[i];
            continue;
        }
        for (int j = i - 1; j >= 1; --j) {
            if (a[i] < a[j]) continue;
            bool ok = true;
            for (int k = j + 1; k < i; ++k) ok &= (a[k] < a[j] || a[k] > a[i]);
            if (ok) dp[i] += dp[j];
        }
        if (ed[i]) ans += dp[i];
    }
    printf("%lld\n", ans);
    return 0;
}
