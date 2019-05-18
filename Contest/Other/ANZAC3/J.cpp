#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 500;
vector<tuple<int, int, int>> g[maxn];
char s[3];
int dp[maxn][maxn][1 << 7];
bool v[maxn][maxn][1 << 7];

int f(char c) {
    if (c == 'R') return 0;
    if (c == 'O') return 1;
    if (c == 'Y') return 2;
    if (c == 'G') return 3;
    if (c == 'B') return 4;
    if (c == 'I') return 5;
    if (c == 'V') return 6;
    assert(false);
}

template <typename T>
using heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v, d; scanf("%d%d%d%s", &u, &v, &d, s);
        --u, --v;
        int z = f(s[0]);
        g[u].emplace_back(v, d, z);
        g[v].emplace_back(u, d, z);
    }

    heap<pair<int, tuple<int, int, int>>> pq;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < (1 << 7); ++k)
                dp[i][j][k] = 1e9;
        }
    }

    for (int i = 0; i < 1; ++i) {
        pq.emplace(0, make_tuple(i, i, 0));
        dp[i][i][0] = 0;
    }

    while (pq.size()) {
        int x = get<0>(pq.top().second);
        int y = get<1>(pq.top().second);
        int s = get<2>(pq.top().second);
        pq.pop();
        if (v[x][y][s]) continue;
        v[x][y][s] = true;

        // printf("x = %d y = %d s = %d d = %d\n", x, y, s, dp[x][y][s]);

        for (int i = 0; i < (int)g[x].size(); ++i) {
            int u, d, z; tie(u, d, z) = g[x][i];
            if (dp[u][y][s | (1 << z)] > dp[x][y][s] + d) {
                dp[u][y][s | (1 << z)] = dp[x][y][s] + d;
                pq.emplace(dp[u][y][s | (1 << z)], make_tuple(u, y, s | (1 << z)));
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            ans = min(ans, dp[i][i][(1 << 7) - 1]);
    }
    printf("%d\n", ans);
    return 0;
}
