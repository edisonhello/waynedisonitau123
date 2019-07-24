#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e6 + 5;
int x[maxn], y[maxn], fa[maxn];
long long area[maxn];
vector<int> g[maxn];
long double ang[maxn];

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (area[v] == -1) swap(u, v);
    if (area[u] != -1 && area[v] != -1) {
        area[u] += area[v];
    }
    fa[v] = u;
}

map<pair<int, int>, int> mp;

bool has(int a, int b) {
    return mp.find(make_pair(a, b)) != mp.end();
}

int gid(int a, int b) {
    if (mp.find(make_pair(a, b)) != mp.end()) return mp[make_pair(a, b)];
    int s = mp.size();
    mp[make_pair(a, b)] = s;
    return s;
}

long long cross(int o, int a, int b) {
    return (x[a] - x[o]) * 1ll * (y[b] - y[o]) - (x[b] - x[o]) * 1ll * (y[a] - y[o]);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);

    int q; scanf("%d", &q);
    vector<tuple<int, int, int>> query;

    for (int i = 0; i < maxn; ++i) fa[i] = i;

    for (int i = 0; i < q; ++i) {
        int t, a, b; scanf("%d%d%d", &t, &a, &b);
        query.emplace_back(t, a, b);
        if (t == 1) add_edge(a, b);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)g[i].size(); ++j) {
            int u = g[i][j];
            ang[u] = atan2(y[u] - y[i], x[u] - x[i]);
        }
        sort(g[i].begin(), g[i].end(), [&](int a, int b) {
                return ang[a] < ang[b];
                }); 

        // int sign = cross(i, g[i][0], g[i][1]) > 0;
        for (int j = 0; j < (int)g[i].size(); ++j) {
            int a = g[i][j], b = g[i][(j + 1) % (int)g[i].size()];
            // if ((cross(i, a, b) > 0) != sign) continue;
            // if (cross(i, a, b) < 0) swap(a, b);
            if (cross(i, a, b) <= 0) continue;
            if (i > a || i > b) continue;
            // printf("i = %d a = %d b = %d\n", i, a, b);
            int p = gid(i, a);
            int q = gid(a, b);
            int r = gid(b, i);
            assert(fa[p] == p);
            assert(fa[q] == q);
            assert(fa[r] == r);
            fa[p] = fa[q] = r;
            area[r] = cross(i, a, b);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)g[i].size(); ++j) {
            int u = g[i][j];
            if (!has(i, u)) {
                int p = gid(i, u);
                area[p] = -1;
            }
            if (!has(u, i)) {
                int p = gid(u, i);
                area[p] = -1;
            }
        }
    }

    vector<long long> ans;

    for (int i = q - 1; i >= 0; --i) {
        int t, a, b; tie(t, a, b) = query[i];
        if (t == 0) {
            int x = gid(a, b);
            ans.push_back(area[find(x)]);
        } else {
            int x = gid(a, b);
            int y = gid(b, a);
            merge(x, y);
        }
    }

    while (ans.size() > 0) {
        printf("%lld\n", ans.back());
        ans.pop_back();
    }
    return 0;
}
