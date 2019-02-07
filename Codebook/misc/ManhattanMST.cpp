#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int x[maxn], y[maxn], fa[maxn];
pair<int, int> bit[maxn];
vector<tuple<int, int, int>> ed;

void add_edge(int u, int v) {
    ed.emplace_back(u, v, abs(x[u] - x[v]) + abs(y[u] - y[v]));
}

void solve(int n) {
    init();
    vector<int> v(n), ds;
    for (int i = 0; i < n; ++i) {
        v[i] = i;
        ds.push_back(x[i] - y[i]);
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    sort(v.begin(), v.end(), [&](int i, int j) { return x[i] == x[j] ? y[i] > y[j] : x[i] > x[j]; });
    int j = 0;
    for (int i = 0; i < n; ++i) {
        int p = lower_bound(ds.begin(), ds.end(), x[v[i]] - y[v[i]]) - ds.begin() + 1;
        pair<int, int> q = query(p);
        // query return prefix minimum
        if (~q.second) add_edge(v[i], q.second);
        add(p, make_pair(x[v[i]] + y[v[i]], v[i]));
    }
}

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d %d", &x[i], &y[i]);
    solve(n);
    for (int i = 0; i < n; ++i) swap(x[i], y[i]);
    solve(n);
    for (int i = 0; i < n; ++i) x[i] = -x[i];
    solve(n);
    for (int i = 0; i < n; ++i) swap(x[i], y[i]);
    solve(n);
    sort(ed.begin(), ed.end(), [](const tuple<int, int, int> &a, const tuple<int, int, int> &b) {
        return get<2>(a) < get<2>(b);
    });
    for (int i = 0; i < n; ++i) fa[i] = i;
    long long ans = 0;
    for (int i = 0; i < ed.size(); ++i) {
        int x, y, w; tie(x, y, w) = ed[i];
        if (find(x) == find(y)) continue;
        merge(x, y);
        ans += w;
    }
    printf("%lld\n", ans);
    return 0;
}
