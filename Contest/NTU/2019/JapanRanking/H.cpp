#include <bits/stdc++.h> 
using namespace std;

const int maxn = 1000;
const int inf = 1e6;
char s[maxn][maxn];
vector<int> g[maxn];
bitset<maxn> win[maxn];
bool good[maxn], cycle[maxn];
int d[maxn][maxn], dfn[maxn], low[maxn], bcc[maxn], sz[maxn], bk, tk;
stack<int> stk;

void add_edge(int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
}

void dfs(int x, int p) {
    stk.push(x);
    dfn[x] = low[x] = tk++;
    for (int u : g[x]) {
        if (u == p) continue;
        if (dfn[u] != -1) {
            low[x] = min(low[x], dfn[u]);
        } else {
            dfs(u, x);
            low[x] = min(low[x], low[u]);
        }
    }
    if (low[x] == dfn[x]) {
        while (!stk.empty()) {
            int u = stk.top(); stk.pop();
            bcc[u] = bk; 
            if (u == x) break;
        }
        ++bk;
    }
}

int main() {
    int m, n; scanf("%d%d", &m, &n);
    for (int i = 0; i < n; ++i) scanf("%s", s[i]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '#') continue;
            if (i > 0 && s[i - 1][j] != '#') add_edge(i * m + j, (i - 1) * m + j);
            if (j > 0 && s[i][j - 1] != '#') add_edge(i * m + j, i * m + (j - 1));
        }
    }

    auto bfs = [&](int r, bool z) {
        for (int i = 0; i < n * m; ++i) d[r][i] = inf;
        queue<int> q;
        q.push(r);
        d[r][r] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int u : g[x]) {
                if (d[r][u] == inf) {
                    d[r][u] = d[r][x] + 1;
                    q.push(u);
                }
            }
        }

        if (!z) return;

        vector<int> v(n * m);
        iota(v.begin(), v.end(), 0);
        sort(v.begin(), v.end(), [&](int i, int j) {
            return d[r][i] < d[r][j];
        });

        bitset<maxn> bs;
        for (int i = 0; i < n * m; ++i) bs[i] = 1;
        for (int i = 0, j = 0; i < n * m; i = j) {
            vector<int> w;
            for (j = i; j < n * m && d[r][v[i]] == d[r][v[j]]; ++j) w.push_back(v[j]);
            for (int u : w) bs[u] = 0;
            for (int u : w) win[u] |= bs;
        }
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            bool z = s[i][j] == 'E';
            bfs(i * m + j, z);
        }
    }

    for (int i = 0; i < n * m; ++i) {
        if (win[i].count() == n * m - 1) {
            good[i] = true;
        }
    }
    memset(dfn, -1, sizeof(dfn));
    for (int i = 0; i < n * m; ++i) {
        if (dfn[i] == -1) dfs(i, -1);
    }
    for (int i = 0; i < n * m; ++i) ++sz[bcc[i]];
    for (int i = 0; i < n * m; ++i) {
        if (sz[bcc[i]] > 1) cycle[i] = true;
    }
    bool draw = false, win = false;
    int qp = -1, sp = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == 'Q') qp = i * m + j;
            if (s[i][j] == 'A') sp = i * m + j;
        }
    }
    for (int i = 0; i < n * m; ++i) {
        if (cycle[i]) draw |= d[qp][i] < d[sp][i];
        if (good[i]) win |= d[qp][i] < d[sp][i];
    }
    if (win) puts("Queen can escape.");
    else if (draw) puts("Queen can not escape and Army can not catch Queen.");
    else puts("Army can catch Queen.");
    return 0;
}
