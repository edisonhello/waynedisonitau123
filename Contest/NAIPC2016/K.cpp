#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int p[maxn], sz[maxn], mx[maxn], fa[maxn], dep[maxn];
long long dist[20][maxn];
bool v[maxn];
vector<pair<int, int>> g[maxn];
vector<pair<int, long long>> ln[maxn];
deque<pair<int, long long>> dq[maxn];
vector<int> go;

void dfs2(int x) {
    sz[x] = 1;
    v[x] = true;
    go.push_back(x);
    mx[x] = 0;
    for (const auto &e : g[x]) {
        int u = e.first;
        if (v[u]) continue;
        dfs2(u);
        sz[x] += sz[u];
        mx[x] = max(mx[x], sz[u]);
    }
}

void dfs3(int x, int d, long long f) {
    dist[d][x] = f;
    v[x] = true;
    for (const auto &e : g[x]) {
        int u = e.first, w = e.second;
        if (v[u]) continue;
        dfs3(u, d, f + w);
    }
}

int dfs(int x, int p, int d) {
    dfs2(x);
    int c = -1;
    for (int u : go) {
        if (max(mx[u], (int)go.size() - sz[u]) * 2 <= go.size()) c = u;
        v[u] = false;
    }
    dfs3(c, d, 0);
    for (int u : go) v[u] = false;
    go.clear();
    v[c] = true;
    dep[c] = d;
    fa[c] = p;
    for (const auto &u : g[c]) {
        if (u.first != p && !v[u.first]) {
            dfs(u.first, c, d + 1);
        }
    }
}

long long func(pair<int, long long> x, pair<int, long long> y) {
    return x.first * 1ll * y.first + x.second + y.second;
}

bool check(pair<int, long long> a, pair<int, long long> b, pair<int, long long> c) {
    return 1.0 * (a.second - b.second) / (b.first - a.first) >= 1.0 * (c.second - b.second) / (b.first - c.first);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &p[i]);
    for (int i = 0; i < n - 1; ++i) {
        int x, y, w; scanf("%d%d%d", &x, &y, &w);
        --x, --y;
        g[x].emplace_back(y, w);
        g[y].emplace_back(x, w);
    }
    dfs(0, -1, 0);
    /* for (int i = 0; i < n; ++i) {
        printf("dep = %d\n", dep[i]);
        for (int j = 0; j <= dep[i]; ++j) {
            printf("%lld ", dist[j][i]);
        }
        puts("");
    } */
    for (int i = 0; i < n; ++i) {
        int x = i;
        for (int j = dep[x]; j >= 0; --j) {
            ln[x].emplace_back(p[i], dist[j][i]);
            x = fa[x];
        }
    }
    for (int i = 0; i < n; ++i) {
        sort(ln[i].begin(), ln[i].end(), [&](pair<int, long long> a, pair<int, long long> b) {
            return a.first == b.first ? a.second < b.second : a.first > b.first;
        });
        vector<pair<int, long long>> ins;
        for (int j = 0; j < (int)ln[i].size(); ++j) {
            if (ins.size() == 0 || ins.back().first != ln[i][j].first) ins.push_back(ln[i][j]); 
        }
        for (int j = 0; j < (int)ins.size(); ++j) {
            while (dq[i].size() >= 2 && check(dq[i][dq[i].size() - 2], dq[i].back(), ins[j]))
                dq[i].pop_back();
            dq[i].push_back(ins[j]);
        }
    }
    vector<int> qr;
    for (int i = 0; i < n; ++i) qr.push_back(i);
    sort(qr.begin(), qr.end(), [&](int i, int j) {
        return p[i] < p[j];
    });
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        int x = qr[i];
        long long ans = 1e18;
        for (int j = dep[qr[i]]; j >= 0; j--) {
            while (dq[x].size() >= 2 && func(dq[x][0], make_pair(p[qr[i]], dist[j][qr[i]])) >= func(dq[x][1], make_pair(p[qr[i]], dist[j][qr[i]])))
                dq[x].pop_front();
            ans = min(ans, func(dq[x][0], make_pair(p[qr[i]], dist[j][qr[i]])));
            x = fa[x];
        }
        // printf("x = %d ans = %lld\n", qr[i], ans);
        res += ans;
    }
    printf("%lld\n", res);
    return 0;
}
