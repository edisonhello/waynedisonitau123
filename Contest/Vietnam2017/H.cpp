#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int fa[maxn], indeg[maxn], dp[maxn];
vector<int> g[maxn];

void init() {
    for (int i = 0; i < maxn; ++i) 
        fa[i] = i;
}

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

void add_edge(int x, int y) {
    g[x].push_back(y);
    ++indeg[y];
}

int main() {
    init();
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<int>> h(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) scanf("%d", &h[i][j]);
    }
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> v;
        for (int j = 0; j < m; ++j) v.emplace_back(h[i][j], j);
        sort(v.begin(), v.end());
        for (int j = 0; j < m; ) {
            int k = j;
            while (k < m && v[k].first == v[j].first) {
                merge(i * m + v[k].second, i * m + v[j].second);
                ++k;
            }
            j = k;
        }
    }
    for (int i = 0; i < m; ++i) {
        vector<pair<int, int>> v;
        for (int j = 0; j < n; ++j) v.emplace_back(h[j][i], j);
        sort(v.begin(), v.end());
        for (int j = 0; j < n; ) {
            int k = j;
            while (k < n && v[k].first == v[j].first) {
                merge(v[k].second * m + i, v[j].second * m + i);
                ++k;
            }
            j = k;
        }
    }
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> v;
        for (int j = 0; j < m; ++j) v.emplace_back(h[i][j], j);
        sort(v.begin(), v.end());
        for (int j = 0; j < m - 1; ++j) {
            if (v[j].first < v[j + 1].first) add_edge(find(i * m + v[j].second), find(i * m + v[j + 1].second));
        }
    }
    for (int i = 0; i < m; ++i) {
        vector<pair<int, int>> v;
        for (int j = 0; j < n; ++j) v.emplace_back(h[j][i], j);
        sort(v.begin(), v.end());
        for (int j = 0; j < n - 1; ++j) {
            if (v[j].first < v[j + 1].first) add_edge(find(v[j].second * m + i), find(v[j + 1].second * m + i));
        }
    }
    queue<int> q;
    for (int i = 0; i < n * m; ++i) {
        if (indeg[i] == 0) {
            dp[i] = 1;
            q.push(i);
        }
    }
    while (q.size()) {
        int x = q.front(); q.pop();
        for (int u : g[x]) {
            dp[u] = max(dp[u], dp[x] + 1);
            --indeg[u];
            if (indeg[u] == 0) {
                q.push(u);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n * m; ++i) ans = max(ans,  dp[i]);
    printf("%d\n", ans);
}


