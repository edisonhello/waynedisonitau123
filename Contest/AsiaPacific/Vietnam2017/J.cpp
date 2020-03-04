#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 8e18;
vector<int> g[maxn];
int sz[maxn], n, m, all;
long long d[maxn], d2[maxn];
long long e[maxn], e2[maxn];
long long ans[maxn];

void dfs(int x, int p) {
    sz[x] = 1;
    long long pd = 0, pd2 = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        d[x] += d[u] + sz[u];
        d2[x] += d2[u] + 2 * d[u] + sz[u];
        ans[x] += ans[u];
        pd2 += d2[u];
        pd += d[u];
    }
    long long res = 0;
    for (int u : g[x]) {
        if (u == p) continue;
        /* long long fd = d[x] - d[u];
        long long fd2 = pd2 - d2[u];
        int fsz = sz[x] - sz[u] - 1;
        res += (d2[u] + 4 * d[u] + 4ll * sz[u]) * fsz + fd2 * sz[u] + 4 * fd * sz[u];
        res += 2 * d[u] * fd; */
        long long fd = d[x] - d[u] - sz[u];
        long long fd2 = d2[x] - (d2[u] + 2 * d[u] + sz[u]);
        int fsz = sz[x] - sz[u] - 1; 
        res += (d2[u] + 2 * d[u] + sz[u])  * fsz + 2 * (d[u] + sz[u]) * fd + fd2 * sz[u];
        // printf("u = %d, fd = %lld, fd2 = %lld, fsz = %d, res = %lld\n", u, fd, fd2, fsz, res);
    }
    ans[x] += res / 2;
    ans[x] += d2[x];
    // printf("d[%d] = %lld, d2[%d] = %lld, ans[%d] = %lld\n", x, d[x], x, d2[x], x, ans[x]);
}

void dfs2(int x, int p, int psz, long long pd, long long pd2) {
    e[x] = d[x]; e2[x] = d2[x];
    e[x] += pd + psz;
    e2[x] += pd2 + 2ll * pd + psz;
    for (int u : g[x]) {
        if (u == p) continue;
        int fsz = all - sz[u];
        long long fd = e[x] - d[u] - sz[u];
        long long fd2 = e2[x] - (d2[u] + 2ll * d[u] + sz[u]);
        dfs2(u, x, fsz, fd, fd2);
    }
}

bool check(int i, int j, int k) {
    long long ai = 2 * e[i];
    long long aj = 2 * e[j];
    long long ak = 2 * e[k];
    long long bi = n * 1ll * (e2[i] + 2 * e[i]);
    long long bj = n * 1ll * (e2[j] + 2 * e[j]);
    long long bk = n * 1ll * (e2[k] + 2 * e[k]);
    return 1.0 * (bj - bi) / (ai - aj) >= 1.0 * (bk - bj) / (aj - ak);
}

bool no(int i, int j) {
    long long ai = 2 * e[i];
    long long aj = 2 * e[j];
    long long bi = n * 1ll * (e2[i] + 2 * e[i]);
    long long bj = n * 1ll * (e2[j] + 2 * e[j]);
    if (ai != aj) return false;
    if (bi <= bj) return true;
    return false;
}

long long calc(int i, int j) {
    long long ai = 2 * e[i];
    long long bi = n * 1ll * (e2[i] + 2 * e[i]);
    return ai * e[j] + bi;
}

int dddd[maxn];

void ddd(int x, int p, int d) {
    dddd[x] = d;
    for (int u : g[x]) {
        if (u == p) continue;
        ddd(u, x, d + 1);
    }
}

int dist(int x, int y) {
    ddd(x, -1, 0);
    return dddd[y];
}

long long brute(int l, int r) {
    long long res = 0;
    for (int i = l; i < r; ++i) {
        for (int j = i + 1; j < r; ++j) res += dist(i, j) * dist(i, j);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    scanf("%d", &m);
    for (int i = 0; i < m - 1; ++i) {
        int x, y; scanf("%d %d", &x, &y);
        --x, --y;
        x += n, y += n;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1); all = n, dfs2(0, -1, 0, 0, 0);
    dfs(n, -1); all = m, dfs2(n, -1, 0, 0, 0);
    // printf("ans[0] = %lld, ans[n] = %lld\n", ans[0], ans[n]);
    // printf("brute = %lld, brute = %lld\n", brute(0, n), brute(n, n + m));
    long long fin = ans[0] + ans[n];
    // for (int i = 0; i < n; ++i) printf("e[%d] = %lld, e2[%d] = %lld\n", i, e[i], i, e2[i]);
    // for (int i = n; i < n + m; ++i) printf("e[%d] = %lld, e2[%d] = %lld\n", i, e[i], i, e2[i]);
    long long res = inf;
    vector<int> x(n);
    iota(x.begin(), x.end(), 0);
    sort(x.begin(), x.end(), [&](int i, int j) { return e[i] < e[j]; });
    vector<int> y(m);
    iota(y.begin(), y.end(), n);
    sort(y.begin(), y.end(), [&](int i, int j) { return e[i] > e[j]; });
    deque<int> dq;
    for (int i = 0; i < m; ++i) {
        int z = y[i];
        if (dq.size() && no(dq.back(), z)) continue;
        while (dq.size() >= 2 && check(dq[dq.size() - 2], dq[dq.size() - 1], z)) dq.pop_back();
        dq.push_back(z);
    }
    for (int i = 0; i < n; ++i) {
        int z = x[i];
        while (dq.size() >= 2 && calc(dq[1], z) <= calc(dq[0], z)) dq.pop_front();
        res = min(res, calc(dq[0], z) + m * 1ll * e2[z] + m * 2ll * e[z]);
    }
    printf("%lld\n", res + fin + n * 1ll * m);
    return 0;
}
