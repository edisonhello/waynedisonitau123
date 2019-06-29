namespace matching {
int fa[maxn], match[maxn], aux[maxn], orig[maxn], v[maxn], tk;
vector<int> g[maxn];
queue<int> q;
void init() {
    for (int i = 0; i < maxn; ++i) {
        g[i].clear();
        match[i] = -1;
        fa[i] = -1;
        aux[i] = 0;
    }
    tk = 0;
}
void add_edge(int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
}
void augment(int x, int y) {
    int a = y, b = -1;
    do {
        a = fa[y], b = match[a];
        match[y] = a, match[a] = y;
        y = b;
    } while (x != a);
}
int lca(int x, int y) {
    ++tk;
    while (true) {
        if (~x) {
            if (aux[x] == tk) return x;
            aux[x] = tk;
            x = orig[fa[match[x]]];
        }
        swap(x, y);
    }
}
void blossom(int x, int y, int a) {
    while (orig[x] != a) {
        fa[x] = y, y = match[x];
        if (v[y] == 1) q.push(y), v[y] = 0;
        orig[x] = orig[y] = a;
        x = fa[y];
    }
}
bool bfs(int s) {
    for (int i = 0; i < maxn; ++i) {
        v[i] = -1;
        orig[i] = i;
    }
    q = queue<int>();
    q.push(s);
    v[s] = 0;
    while (q.size()) {
        int x = q.front(); q.pop();
        for (const int &u : g[x]) {
            if (v[u] == -1) {
                fa[u] = x, v[u] = 1;
                if (!~match[u]) return augment(s, u), true;
                q.push(match[u]);
                v[match[u]] = 0;
            } else if (v[u] == 0 && orig[x] != orig[u]) {
                int a = lca(orig[x], orig[u]);
                blossom(u, x, a);
                blossom(x, u, a);
            }
        }
    }
    return false;
}
int solve(int n) {
    int ans = 0;
    vector<int> z(n);
    iota(z.begin(), z.end(), 0);
    random_shuffle(z.begin(), z.end());
    for (int x : z) if (!~match[x]) {
        for (int y : g[x]) if (!~match[y]) {
            match[y] = x;
            match[x] = y;
            ++ans;
            break;
        }
    }
    for (int i = 0; i < n; ++i) if (!~match[i] && bfs(i)) ++ans;
    return ans;
}}
