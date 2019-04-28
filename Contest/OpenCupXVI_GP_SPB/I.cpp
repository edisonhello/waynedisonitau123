#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
int c[maxn], f[maxn];
vector<pair<int, int>> g[2 * maxn];
long long d[2 * maxn];
bool v[2 * maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &f[i]);

    for (int i = 0; i < n; ++i) {
        g[i * 2].emplace_back(i * 2 + 1, c[i] - f[i]);
        g[i * 2 + 1].emplace_back(i * 2, c[i] - f[i]);
        if (i + 1 < n) {
            if (f[i + 1] <= f[i] && c[i + 1] > f[i])
                g[i * 2].emplace_back((i + 1) * 2, 0);
            if (c[i + 1] >= c[i] && f[i + 1] < c[i])
                g[i * 2 + 1].emplace_back((i + 1) * 2 + 1, 0);
        }
    }

    for (int i = 0; i < 2 * n; ++i)
        d[i] = inf;

    d[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.emplace(0, 0);

    while (!pq.empty()) {
        int x = pq.top().second; pq.pop();
        if (v[x]) continue;

        v[x] = true;
        for (int i = 0; i < (int)g[x].size(); ++i) {
            int u = g[x][i].first, w = g[x][i].second;
            if (d[u] > d[x] + w) {
                d[u] = d[x] + w;
                pq.emplace(d[u], u);
            }
        }
    }

    long long ans = d[2 * (n - 1)];
    if (ans == inf)
        printf("-1\n");
    else
        printf("%lld\n", ans);
    return 0; 
}
