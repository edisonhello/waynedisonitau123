#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 87;
const long long inf = 1e15;
vector<pair<int, int>> g[maxn], r[maxn];
int a[maxn], b[maxn], c[maxn], f1[maxn], f2[maxn], n, m;
long long way1[maxn], way2[maxn];
bool v[maxn], on[maxn];
long long d1[maxn], d2[maxn];

void dijk(vector<pair<int, int>> g[maxn], long long d[maxn], long long way[maxn], int f[maxn], int s) {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.emplace(0, s);
    for (int i = 0; i < maxn; ++i) d[i] = inf;
    d[s] = 0;
    way[s] = 1;
    memset(v, false, sizeof(v));
    while (pq.size()) {
        int x = pq.top().second; pq.pop();
        if (v[x]) continue;
        v[x] = true;
        for (const auto &e : g[x]) {
            int u = e.first, w = c[e.second];
            if (d[x] + w < d[u]) {
                d[u] = d[x] + w;
                way[u] = way[x];
                f[u] = 1;
                pq.emplace(d[u], u);
            } else if (d[x] + w == d[u]) {
                f[u]++;
                way[u] += way[x];
                way[u] %= mod;
            }
        }
    }
}


int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        --a[i], --b[i];
        g[a[i]].emplace_back(b[i], i);
        r[b[i]].emplace_back(a[i], i);
    }
    dijk(g, d1, way1, f1, 0);
    dijk(r, d2, way2, f2, 1);
    long long ss = d1[1];
    for (int i = 0; i < m; ++i) {
        if (d1[a[i]] + c[i] + d2[b[i]] == ss) on[i] = true;
    }
    // for (int i = 0; i < n; ++i) printf("%lld ", way1[i]); puts("");
    // for (int i = 0; i < n; ++i) printf("%lld ", way2[i]); puts("");
    for (int i = 0; i < m; ++i) {
        long long pp = d1[b[i]] + c[i] + d2[a[i]];
        if (pp < ss) {
            puts("HAPPY");
            continue;
        }
        // printf("%lld\n", way1[a[i]] * 1ll * way2[b[i]] % mod);
        if (way1[a[i]] * 1ll * way2[b[i]] % mod != way1[1]) {
            puts("SOSO");
            continue;
        }
        if (!on[i]) {
            puts("SOSO");
            continue;
        }
        if (pp == ss) {
            puts("SOSO");
            continue;
        }
        if (f1[b[i]] == 1) puts("SAD");
        else puts("SOSO");
    }
}
