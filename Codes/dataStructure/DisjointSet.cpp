struct DisjointSet {
    int p[maxn], sz[maxn], n, cc;
    vector<pair<int*, int>> his;
    vector<int> sh;
    void init(int _n) {
        n = _n; cc = n;
        for (int i = 0; i < n; ++i) sz[i] = 1, p[i] = i;
        sh.clear(); his.clear();
    }
    void assign(int *k, int v) {
        his.emplace_back(k, *k);
        *k = v;
    }
    void save() {
        sh.push_back((int)his.size());
    }
    void undo() {
        int last = sh.back(); sh.pop_back();
        while (his.size() != last) {
            int *k, v;
            tie(k, v) = his.back(); his.pop_back();
            *k = v;
        }
    }
    int find(int x) {
        if (x == p[x]) return x;
        return find(p[x]);
    }
    void merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        assign(&sz[y], sz[x] + sz[y]);
        assign(&p[x], y);
        assign(&cc, cc - 1);
    }
} dsu;
