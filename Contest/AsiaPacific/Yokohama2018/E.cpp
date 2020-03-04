#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int adj[maxn][maxn], deg[maxn], fa[maxn], sz[maxn];
vector<int> pz[maxn];
int add[maxn][maxn];
bool vs[maxn];
vector<int> g[maxn];
vector<pair<int, int>> path;

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    fa[find(x)] = find(y);
}

namespace matching {
    int fa[maxn], pre[maxn], match[maxn], s[maxn], v[maxn];
    vector<int> g[maxn];
    queue<int> q;

    void init(int n) {
        for (int i = 0; i <= n; ++i) match[i] = pre[i] = n;
        for (int i = 0; i < n; ++i) g[i].clear();
    }

    int find(int u) {
        if (u == fa[u]) return u;
        return fa[u] = find(fa[u]);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int lca(int x, int y, int n) {
        static int tk = 0;
        tk++;
        x = find(x), y = find(y);
        for (; ; swap(x, y)) {
            if (x != n) {
                if (v[x] == tk) return x;
                v[x] = tk;
                x = find(pre[match[x]]);
            }
        }
    }

    void blossom(int x, int y, int l) {
        while (find(x) != l) {
            pre[x] = y;
            y = match[x];
            if (s[y] == 1) {
                q.push(y);
                s[y] = 0;
            }
            if (fa[x] == x) fa[x] = l;
            if (fa[y] == y) fa[y] = l;
            x = pre[y];
        }
    }

    bool bfs(int r, int n) {
        for (int i = 0; i <= n; ++i) {
            fa[i] = i;
            s[i] = -1;
        }
        while (!q.empty()) q.pop();
        q.push(r);
        s[r] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int u : g[x]) {
                if (s[u] == -1) {
                    pre[u] = x;
                    s[u] = 1;
                    if (match[u] == n) {
                        for (int a = u, b = x, last; b != n; a = last, b = pre[a]) {
                            last = match[b];
                            match[b] = a;
                            match[a] = b;
                        }
                        return true;
                    }
                    q.push(match[u]);
                    s[match[u]] = 0;
                } else if (!s[u] && find(u) != find(x)) {
                    int l = lca(u, x, n);
                    blossom(x, u, l);
                    blossom(u, x, l);
                }
            }
        }
        return false;
    }

    int solve(int n) {
        int res = 0;
        for (int x = 0; x < n; ++x) {
            if (match[x] == n) res += bfs(x, n);
        }
        return res;
    }
}

vector<pair<int, int>> pp;

void dfs(int x, int z) {
    vs[x] = true;
    // printf("x = %d z = %d\n", x, z);
    if (x == z) {
        path = pp;
        return;
    }
    for (int u : g[x]) {
        if (!vs[u]) {
            pp.emplace_back(x, u);
            dfs(u, z);
            pp.pop_back();
        }
    }
}

void Print(vector<pair<int, int>> ed) {
    printf("%d\n", (int)ed.size());
    for (auto e : ed) {
        if (e.first > e.second) swap(e.first, e.second);
        printf("%d %d\n", e.first + 1, e.second + 1);
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        adj[u][v] = adj[v][u] = 1;
        ++deg[u], ++deg[v];
        merge(u, v);
    }

    {
        for (int i = 0; i < n; ++i) ++sz[find(i)];
        vector<int> vsz;
        for (int i = 0; i < n; ++i) {
            if (find(i) == i) vsz.push_back(sz[i]);
        }
        sort(vsz.begin(), vsz.end());
        if (n % 2 == 0 && vsz.size() == 2 && vsz[0] == 1 && vsz[1] == n - 1) {
            if (m == (n - 1) * (n - 2) / 2) {
                puts("-1");
                return 0;
            }
        }
    }

    vector<int> odd;
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) odd.push_back(i);
    }

    if (odd.size() & 1) {
        puts("-1");
        return 0;
    }

    matching::init(n);
    for (int i = 0; i < n; ++i) fa[i] = i;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (!adj[i][j]) {
                merge(i, j);
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    for (int i = 0; i < (int)odd.size(); ++i) {
        for (int j = i + 1; j < (int)odd.size(); ++j) {
            int u = odd[i], v = odd[j];
            if (find(u) == find(v)) {
                // printf("add_edge %d %d\n", u, v);
                matching::add_edge(u, v);
            }
        }
    }

    int match = matching::solve(n);
    if (match * 2 != (int)odd.size()) {
        puts("-1");
        return 0;
    }

    for (int i = 0; i < (int)odd.size(); ++i) {
        int u = odd[i];
        int v = matching::match[u];
        // printf("u = %d v = %d\n", u, v);
        if (u < v) {
            memset(vs, false, sizeof(vs));
            pp.clear();
            dfs(u, v);
            for (auto e : path) {
                // printf("e = \n");
                // printf("e.first = %d e.second = %d\n", e.first, e.second);
                add[e.first][e.second] ^= 1;
                add[e.second][e.first] ^= 1;
            }
        }
    }

    for (int i = 0; i < n; ++i) fa[i] = i, sz[i] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (add[i][j]) {
                assert(!adj[i][j]);
                merge(i, j);
            } else if (adj[i][j]) {
                merge(i, j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (add[i][j]) ++sz[find(i)];
        }
    }

    vector<int> root;
    for (int i = 0; i < n; ++i) {
        if (find(i) == i) root.push_back(i);
    }
    if (root.size() >= 3) {
        vector<pair<int, int>> ed;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) if (add[i][j]) ed.emplace_back(i, j);
        }
        int k = (int)root.size();
        for (int i = 0; i < k; ++i) {
            int u = root[i];
            int v = root[(i + 1) % k];
            if (u > v) swap(u, v);
            ed.emplace_back(u, v);
        }
        Print(ed);
        return 0;
    }
    if (root.size() == 1) {
        vector<pair<int, int>> ed;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) if (add[i][j]) ed.emplace_back(i, j);
        }
        Print(ed);
        return 0;
    }
    for (int i = 0; i < n; ++i) pz[find(i)].push_back(i);
    int x = root[0], y = root[1];
    if (pz[x].size() >= 2 && pz[y].size() >= 2) {
        vector<pair<int, int>> ed;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) if (add[i][j]) ed.emplace_back(i, j);
        }
        ed.emplace_back(pz[x][0], pz[y][0]);
        ed.emplace_back(pz[x][1], pz[y][0]);
        ed.emplace_back(pz[x][0], pz[y][1]);
        ed.emplace_back(pz[x][1], pz[y][1]);
        Print(ed);
    }
    if (pz[x].size() > pz[y].size()) swap(x, y);
    vector<pair<int, int>> gd, bd;
    for (int i = 0; i < (int)pz[y].size(); ++i) {
        for (int j = i + 1; j < (int)pz[y].size(); ++j) {
            int u = pz[y][i], v = pz[y][j];
            if (!adj[u][v] && !add[u][v]) gd.emplace_back(u, v);
            if (add[u][v]) assert(!adj[u][v]), bd.emplace_back(u, v);
        }
    }
    vector<pair<int, int>> ed;
    if (!gd.empty()) {
        ed.emplace_back(pz[x][0], gd[0].first); 
        ed.emplace_back(pz[x][0], gd[0].second); 
        ed.emplace_back(gd[0].first, gd[0].second);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (add[i][j]) ed.emplace_back(i, j);
            }
        }
    } else {
        assert(!bd.empty());
        int u = bd[0].first, v = bd[0].second;
        ed.emplace_back(pz[x][0], u);
        ed.emplace_back(pz[x][0], v);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (add[i][j] && minmax(u, v) != minmax(i, j)) ed.emplace_back(i, j);
            }
        }
    }
    Print(ed);
    return 0;
}
