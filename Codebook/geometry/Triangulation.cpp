namespace triangulation {
    static const int maxn = 1e5 + 5;
    vector<point> p;
    set<int> g[maxn];
    int o[maxn];
    set<int> s;
    void add_edge(int x, int y) {
        s.insert(x), s.insert(y);
        g[x].insert(y);
        g[y].insert(x);
    }
    bool inside(point a, point b, point c, point p) {
        if (((b - a) ^ (c - a)) < 0) swap(b, c);
        function<long long(int)> sqr = [](int x) { return x * 1ll * x; };
        long long k11 = a.x - p.x, k12 = a.y - p.y, k13 = sqr(a.x) - sqr(p.x) + sqr(a.y) - sqr(p.y);
        long long k21 = b.x - p.x, k22 = b.y - p.y, k23 = sqr(b.x) - sqr(p.x) + sqr(b.y) - sqr(p.y);
        long long k31 = c.x - p.x, k32 = c.y - p.y, k33 = sqr(c.x) - sqr(p.x) + sqr(c.y) - sqr(p.y);
        long long det = k11 * (k22 * k33 - k23 * k32) - k12 * (k21 * k33 - k23 * k31) + k13 * (k21 * k32 - k22 * k31);
        return det > 0;
    }
    bool intersect(const point &a, const point &b, const point &c, const point &d) {
        return ((b - a) ^ (c - a)) * ((b - a) ^ (d - a)) < 0 &&
               ((d - c) ^ (a - c)) * ((d - c) ^ (b - c)) < 0;
    }
    void dfs(int l, int r) {
        if (r - l <= 3) {
            for (int i = l; i < r; ++i) {
                for (int j = i + 1; j < r; ++j) add_edge(i, j);
            }
            return;
        }
        int m = (l + r) >> 1;
        dfs(l, m), dfs(m, r);
        int pl = l, pr = r - 1;
        while (true) {
            int z = -1;
            for (int u : g[pl]) {
                long long c = ((p[pl] - p[pr]) ^ (p[u] - p[pr]));
                if (c > 0 || c == 0 && abs(p[u] - p[pr]) < abs(p[pl] - p[pr])) {
                    z = u;
                    break;
                }
            }
            if (z != -1) {
                pl = z;
                continue;
            }
            for (int u : g[pr]) {
                long long c = ((p[pr] - p[pl]) ^ (p[u] - p[pl]));
                if (c < 0 || c == 0 && abs(p[u] - p[pl]) < abs(p[pr] - p[pl])) {
                    z = u;
                    break;
                }
            }
            if (z != -1) {
                pr = z;
                continue;
            }
            break;
        }
        add_edge(pl, pr);
        while (true) {
            int z = -1;
            bool b = false;
            for (int u : g[pl]) {
                long long c = ((p[pl] - p[pr]) ^ (p[u] - p[pr]));
                if (c < 0 && (z == -1 || inside(p[pl], p[pr], p[z], p[u]))) z = u;
            }
            for (int u : g[pr]) {
                long long c = ((p[pr] - p[pl]) ^ (p[u] - p[pl]));
                if (c > 0 && (z == -1 || inside(p[pl], p[pr], p[z], p[u]))) z = u, b = true;
            }
            if (z == -1) break;
            int x = pl, y = pr;
            if (b) swap(x, y);
            for (auto it = g[x].begin(); it != g[x].end(); ) {
                int u = *it;
                if (intersect(p[x], p[u], p[y], p[z])) {
                    it = g[x].erase(it);
                    g[u].erase(x);
                } else {
                    ++it;
                }
            }
            if (b) add_edge(pl, z), pr = z;
            else add_edge(pr, z), pl = z;
        }
    } 
    vector<vector<int>> solve(vector<point> v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n; ++i) o[i] = i;
        sort(o, o + n, [&](int i, int j) { return v[i] < v[j]; });
        p.resize(n);
        for (int i = 0; i < n; ++i) p[i] = v[o[i]];
        dfs(0, n);
        vector<vector<int>> res(n);
        for (int i = 0; i < n; ++i) {
            for (int j : g[i]) res[o[i]].push_back(o[j]);
        }
        return res;
    }
}
