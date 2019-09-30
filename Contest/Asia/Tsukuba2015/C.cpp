#include <bits/stdc++.h>
using namespace std;

const int maxn = 50;
const int inf = 1e9 + 7;
vector<int> g[maxn];
vector<int> adj[maxn][3];
int mask[maxn], dp[maxn][3], dist[maxn];
bool v[maxn], inq[maxn];

int main() {
    int n, m, a[3]; scanf("%d%d", &n, &m);
    for (int i = 0; i < 3; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        vector<int> q = {i};
        for (int j = 1; j <= 100; ++j) {
            memset(v, false, sizeof(v));
            vector<int> nq;
            for (int x : q) {
                for (int u : g[x]) {
                    if (!v[u]) {
                        v[u] = true;
                        nq.push_back(u);
                    }
                }
            }
            for (int k = 0; k < 3; ++k) {
                if (a[k] != j) continue;
                for (int u : nq) adj[u][k].push_back(i);
            }
            q.swap(nq);
        }
    }

    queue<int> q;
    q.push(n - 1);

    for (int i = 0; i < n; ++i) {
        dp[i][0] = inf;
        dp[i][1] = inf;
        dp[i][2] = inf;
        dist[i] = inf;
    }

    dist[n - 1] = 0;
    inq[n - 1] = true;

    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < 3; ++i) {
            for (int u : adj[x][i]) {
                dp[u][i] = min(dp[u][i], dist[x] + 1);
                mask[u] |= (1 << i);
                if (mask[u] == 7 && !inq[u]) {
                    inq[u] = true;
                    dist[u] = max(dp[u][0], max(dp[u][1], dp[u][2]));
                    q.push(u);
                }
            }
        }
    }
    if (!inq[0]) puts("IMPOSSIBLE");
    else printf("%d\n", dist[0]);
}

