#pragma GCC optimize("O3")
// #pragma GCC target("sse,sse2,sse3,sse4,sse4.2,avx,popcnt,abm,mmx,tune=native")
#include <bits/stdc++.h>
using namespace std;

#define double float

const int maxn = 2000 + 5;
const int maxk = 50;
int n, m, k, vr, vf; 
int x[maxn], y[maxn], f[maxk][maxn], v[maxn];
double d[maxk][maxn], dt[maxn][maxn];

double dist(int i, int j) {
    return hypot(x[i] - x[j], y[i] - y[j]);
}

void dijk(int s, int z, int p) {
    for (int i = 0; i < n; ++i) {
        d[z][i] = 1e15;
        f[z][i] = -1; 
        v[i] = 0;
    }
    d[z][s] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.emplace(0, s);

    while (pq.size()) {
        int x = pq.top().second; pq.pop();
        if (x == p) return;
        if (v[x]) continue;
        v[x] = 1;

        for (int i = 0; i < n; ++i) {
            if (i == x) continue;
            if (d[z][i] > d[z][x] + dt[x][i] && d[z][x] + dt[x][i] <= dt[s][p] + 1e-9) {
                f[z][i] = x;
                d[z][i] = d[z][x] + dt[x][i];
                pq.emplace(d[z][i], i);
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &k, &vr, &vf);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = dist(i, j);
            dt[i][j] = dt[j][i] = d / vf;
            // g[i].emplace_back(j, d / vf);
            // g[j].emplace_back(i, d / vf);
        }
    }

    while (m--) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        double d = dist(u, v);
        dt[u][v] = dt[v][u] = d / vr;
        // g[u].emplace_back(v, d / vr);
        // g[v].emplace_back(u, d / vr);
    }

    vector<int> spec = {0};
    for (int i = 0; i < k; ++i) {
        int v; scanf("%d", &v);
        spec.push_back(v - 1);
    }
    spec.push_back(n - 1);

    for (int i = 0; i < (int)spec.size() - 1; ++i) 
        dijk(spec[i], i, spec[i + 1]);

    double ans = 0.0;
    vector<int> w = {0};
    for (int i = 0; i + 1 < (int)spec.size(); ++i) {
        ans += d[i][spec[i + 1]];
    }

    printf("%.20f\n", ans);
    printf("1 ");
    for (int i = 0; i + 1 < (int)spec.size(); ++i) {
        vector<int> v;
        int x = spec[i + 1];
        while (x >= 0) {
            v.push_back(x);
            x = f[i][x];
        }

        v.pop_back();
        while (v.size() > 0) {
            printf("%d ", v.back() + 1);
            v.pop_back();
        }
    }
    puts("");
        
}
