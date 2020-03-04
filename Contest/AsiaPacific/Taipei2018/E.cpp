#include <bits/stdc++.h>
using namespace std;

#define int long long
const int maxn = 500 + 5;
const int inf = 1e15;
int w[maxn][maxn], lx[maxn], ly[maxn], n;
int match[maxn], slack[maxn];
bool vx[maxn], vy[maxn];

bool dfs(int x) {
    vx[x] = true;
    for (int i = 0; i < n; ++i) {
        if (vy[i]) continue;
        if (lx[x] + ly[i] > w[x][i]) {
            slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
            continue;
        }
        vy[i] = true;
        if (match[i] == -1 || dfs(match[i])) {
            match[i] = x;
            return true;
        }
    }
    return false;
}

int solve() {
    fill_n(match, n, -1);
    fill_n(lx, n, -inf);
    fill_n(ly, n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) lx[i] = max(lx[i], w[i][j]);
    }
    for (int i = 0; i < n; ++i) {
        fill_n(slack, n, inf);
        while (true) {
            fill_n(vx, n, false);
            fill_n(vy, n, false);
            if (dfs(i)) break;
            int dlt = inf;
            for (int j = 0; j < n; ++j) if (!vy[j]) dlt = min(dlt, slack[j]);
            for (int j = 0; j < n; ++j) {
                if (vx[j]) lx[j] -= dlt;
                if (vy[j]) ly[j] += dlt;
                else slack[j] -= dlt;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) res += w[match[i]][i];
    return res;
}

int x[maxn], y[maxn], z[maxn];

int32_t main() {
    int t; scanf("%lld", &t);
    while (t--) {
        scanf("%lld", &n);
        for (int i = 0; i < 2 * n; ++i) scanf("%lld%lld%lld", &x[i], &y[i], &z[i]);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int c = (x[i] - x[j + n]) * (x[i] - x[j + n]) + 
                        (y[i] - y[j + n]) * (y[i] - y[j + n]) + 
                        (z[i] - z[j + n]) * (z[i] - z[j + n]);
                w[i][j] = -c;
            }
        }
        printf("%lld\n", -solve());
    }
}
