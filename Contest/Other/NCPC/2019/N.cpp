#include <bits/stdc++.h>
using namespace std;

const int maxn = 15;
int adj[maxn], dp[1 << maxn], tr[1 << maxn], gr[maxn];
bool ok[1 << maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        memset(adj, 0, sizeof(adj));
        int n, m; scanf("%d%d", &n, &m);
        vector<pair<int, int>> ed;
        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            adj[u] |= (1 << v);
            adj[v] |= (1 << u);
            ed.emplace_back(u, v);
        }
        memset(ok, false, sizeof(ok));
        for (int s = 0; s < (1 << n); ++s) {
            ok[s] = true;
            for (int i = 0; i < n; ++i) {
                if ((s >> i & 1) == 0) continue;
                ok[s] &= ((adj[i] & s) == 0);
            }
        }
        dp[0] = 0;
        for (int s = 1; s < (1 << n); ++s) {
            int sub = s;
            dp[s] = 1e9;
            while (sub > 0) {
                if (ok[sub]) {
                    if (dp[s ^ sub] + 1 < dp[s]) {
                        dp[s] = dp[s ^ sub] + 1;
                        tr[s] = sub;
                    }
                }
                sub = (sub - 1) & s;
            }
        }
        int s = (1 << n) - 1, z = 0;
        while (s > 0) {
            for (int i = 0; i < n; ++i) {
                if (tr[s] >> i & 1)
                    gr[i] = z;
            }
            z++;
            s ^= tr[s];
        }
        printf("%d\n", dp[(1 << n) - 1] - 1);
        for (int i = 0; i < m; ++i) {
            printf("%d ", (gr[ed[i].first] < gr[ed[i].second]));
        }
        puts("");
    }
}
