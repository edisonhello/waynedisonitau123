#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
vector<pair<int, int>> g[maxn];
bool hm[maxn], ml[maxn];
bool dp[maxn][maxn], v[maxn][maxn];

int main() {
    int n, w, c, h, m;
    scanf("%d%d%d%d%d", &n, &w, &c, &h, &m);
    for (int i = 0; i < h; ++i) {
        int x; scanf("%d", &x);
        hm[x] = true;
    }
    for (int i = 0; i < m; ++i) {
        int x; scanf("%d", &x);
        ml[x] = true;
    }
    for (int i = 0; i < w; ++i) {
        int x, y, d; scanf("%d%d%d", &x, &d, &y);
        g[x].emplace_back(y, d);
    }
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        if (!hm[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (!hm[j]) {
                dp[i][j] = true;
                q.emplace(i, j);
                v[i][j] = true;
            }
        }
    }
    while (q.size()) {
        int x, y; tie(x, y) = q.front(); q.pop();
        for (int i = 0; i < (int)g[x].size(); ++i) {
            for (int j = 0; j < (int)g[y].size(); ++j) {
                if (g[x][i].second != g[y][j].second) continue;
                int a = g[x][i].first, b = g[y][j].first;
                if (v[a][b]) continue;
                v[a][b] = true;
                dp[a][b] = true;
                q.emplace(a, b);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!ml[i]) continue;
        for (int j = 0; j < n; ++j) {
            if (!ml[j]) continue;
            if (dp[i][j]) {
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}
