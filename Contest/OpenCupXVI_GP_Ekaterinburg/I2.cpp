#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int n, k, c;
int cost[maxn][maxn], load[maxn][maxn], sum[maxn];
long long dp[maxn];

namespace km {
    long long w[maxn][maxn], lx[maxn], ly[maxn], slack[maxn];
    int match[maxn];
    bool vx[maxn], vy[maxn];

    bool dfs(int x, int n) {
        vx[x] = true;
        for (int i = 0; i < n; ++i) {
            if (vy[i]) continue;

            if (lx[x] + ly[i] > w[x][i]) {
                slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
                continue;
            }

            vy[i] = true;
            if (match[i] == -1 || dfs(match[i], n)) {
                match[i] = x;
                return true;
            }
        }
        return false;
    }

    long long solve(int n) {
        fill_n(match, n, -1);
        fill_n(lx, n, -1e15);
        fill_n(ly, n, 0);

        /* printf("--------------\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                printf("%d ", w[i][j]);
            puts("");
        } */

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                lx[i] = max(lx[i], w[i][j]);
        }
        for (int i = 0; i < n; ++i) {
            fill_n(slack, n, 1e15);
            while (true) {
                fill_n(vx, n, false);
                fill_n(vy, n, false);
                if (dfs(i, n)) break;

                long long dlt = 1e15;
                for (int j = 0; j < n; ++j) {
                    if (!vy[j])
                        dlt = min(dlt, slack[j]);
                }
                for (int j = 0; j < n; ++j) {
                    if (vx[j])
                        lx[j] -= dlt;
                    if (vy[j])
                        ly[j] += dlt;
                    else
                        slack[j] -= dlt;
                }
            }
        }
        long long res = 0;
        for (int i = 0; i < n; ++i) res += w[match[i]][i];
        return res;
    }
}

long long solve(int l, int r) {
    for (int i = 0; i < k; ++i) {
        sum[i] = 0;
        for (int j = l; j <= r; ++j)
            sum[i] += load[j][i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (cost[i][j] == -1 && sum[j] > 0)
                km::w[i][j] = -1e15;
            else
                km::w[i][j] = -sum[j] * 1ll * cost[i][j];
        }
        for (int j = k; j < n; ++j)
            km::w[i][j] = 0;
    }
    long long res = -km::solve(n);
    // printf("res = %lld\n", res);
    return res;
}

int main() {
    scanf("%d%d%d", &n, &k, &c);
    memset(cost, -1, sizeof(cost));

    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        --u, --v;
        cost[u][v] = w;
    }

    int q; scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        for (int j = 0; j < k; ++j)
            scanf("%d", &load[i][j]);
    }

    dp[0] = 0;
    for (int i = 1; i <= q; ++i) {
        dp[i] = 1e15;
        for (int j = 0; j < i; ++j)
            dp[i] = min(dp[i], dp[j] + solve(j + 1, i) + c);
    }
    printf("%lld\n", dp[q]);
    return 0;
}
