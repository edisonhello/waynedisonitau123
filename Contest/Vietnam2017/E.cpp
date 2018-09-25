#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int inf = 1e9;
vector<pair<int, int>> g[maxn];
int w[maxn][maxn], n, m, k, t;
int lx[maxn], ly[maxn];
int match[maxn];
bool vx[maxn], vy[maxn];

bool dfs(int x) {
    vx[x] = true;
    for (int i = 0; i < t; ++i) {
        if (lx[x] + ly[i] == w[x][i] && !vy[i]) {
            vy[i] = true;
            if (match[i] == -1 || dfs(match[i])) {
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}

void relable() {
    int dlt = inf;
    for (int i = 0; i < t; ++i) if (vx[i]) {
        for (int j = 0; j < t; ++j)  if (!vy[j]) dlt = min(dlt, lx[i] + ly[j] - w[i][j]);
    }
    for (int i = 0; i < t; ++i) if (vx[i]) lx[i] -= dlt;
    for (int i = 0; i < t; ++i) if (vy[i]) ly[i] += dlt;
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    t = max(n, m);
    for (int i = 0; i < t; ++i) w[i][i] = 0;
    for (int i = 0; i < k; ++i) {
        int x, y, p; scanf("%d %d %d", &x, &y, &p);
        --x, --y;
        w[x][y] = p;
    }
    fill(lx, lx + maxn, -inf);
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < t; ++j) lx[i] = max(lx[i], w[i][j]);
    }
    memset(match, -1, sizeof(match));
    for (int i = 0; i < n; ++i) {
        while (true) {
            for (int j = 0; j < n; ++j) vx[j] = false;
            for (int j = 0; j < m; ++j) vy[j] = false;
            if (dfs(i)) break;
            relable();
        }
    }
    long long res = 0;
    vector<pair<int, int>> v;
    for (int i = 0; i < m; ++i) if (match[i] != -1) res += w[match[i]][i], v.emplace_back(match[i], i);
    printf("%lld\n", res);
    printf("%d\n", (int)v.size());
    for (int i = 0; i < v.size(); ++i) printf("%d %d\n", v[i].first + 1, v[i].second + 1);
}
