#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5;
const int inf = 1e9;
int w[maxn][maxn], ds[maxn][maxn], c[maxn], d[maxn];
int lx[maxn], ly[maxn], match[maxn];
bool vx[maxn], vy[maxn];

bool dfs(int x, int n) {
    vx[x] = true;
    for (int i = 0; i < n; ++i) {
        if (lx[x] + ly[i] == w[x][i] && !vy[i]) {
            vy[i] = true;
            if (match[i] == -1 || dfs(match[i], n)) {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

void relabel(int n) {
    int dlt = 1000000000;
    for (int i = 0; i < n; ++i) if (vx[i]) {
        for (int j = 0; j < n; ++j) if (!vy[j]) dlt = min(dlt, lx[i] + ly[j] - w[i][j]);
    }
    for (int i = 0; i < n; ++i) if (vx[i]) lx[i] -= dlt;
    for (int i = 0; i < n; ++i) if (vy[i]) ly[i] += dlt;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) ds[i][j] = inf;
            ds[i][i] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            ds[x][y] = ds[y][x] = 1;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) ds[i][j] = min(ds[i][j], ds[i][k] + ds[k][j]);
            }
        }
        for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &d[i]);
        vector<int> x, y;
        for (int i = 0; i < n; ++i) {
            if (c[i] == 1) x.push_back(i);
            if (d[i] == 1) y.push_back(i);
        }
        n = (int)x.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) w[i][j] = -ds[x[i]][y[j]];
        }
        for (int i = 0; i < n; ++i) {
            lx[i] = -1000000000;
            for (int j = 0; j < n; ++j) lx[i] = max(lx[i], w[i][j]);
        }
        for (int i = 0; i < n; ++i) ly[i] = 0;
        for (int i = 0; i < n; ++i) match[i] = -1;
        for (int i = 0; i < n; ++i) {
            while (true) {
                for (int j = 0; j < n; ++j) vx[j] = vy[j] = false;
                if (dfs(i, n)) break;
                relabel(n);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) ans -= w[match[i]][i];
        printf("%d\n", ans);
    }
}
