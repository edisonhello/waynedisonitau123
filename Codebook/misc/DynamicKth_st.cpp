// segtree: persistant segment tree which supports range sum query

void init(int n) {
    segtree::sz = 0;
    bit[0] = segtree::build(0, ds.size());
    for (int i = 1; i <= n; ++i) bit[i] = bit[0];
}

void add(int p, int n, int x, int v) {
    for (; p <= n; p += p & -p)
        bit[p] = segtree::modify(0, ds.size(), x, v, bit[p]);
}

vector<int> query(int p) {
    vector<int> z;
    for (; p; p -= p & -p) 
        z.push_back(bit[p]);
    return z;
}

int dfs(int l, int r, vector<int> lz, vector<int> rz, int k) {
    if (r - l == 1) return l;
    int ls = 0, rs = 0;
    for (int i = 0; i < lz.size(); ++i) ls += segtree::st[segtree::lc[lz[i]]];
    for (int i = 0; i < rz.size(); ++i) rs += segtree::st[segtree::lc[rz[i]]];
    if (rs - ls >= k) {
        for (int i = 0; i < lz.size(); ++i) lz[i] = segtree::lc[lz[i]];
        for (int i = 0; i < rz.size(); ++i) rz[i] = segtree::lc[rz[i]];
        return dfs(l, (l + r) / 2, lz, rz, k);
    } else {
        for (int i = 0; i < lz.size(); ++i) lz[i] = segtree::rc[lz[i]];
        for (int i = 0; i < rz.size(); ++i) rz[i] = segtree::rc[rz[i]];
        return dfs((l + r) / 2, r, lz, rz, k - (rs - ls));
    }
}

void solve() {
    init(n);
    for (int i = 1; i <= n; ++i) add(i, n, a[i], 1);
    for (int i = 0; i < q; ++i) {
        if (qr[i][0] == 1) {
            vector<int> lz = query(qr[i][1] - 1);
            vector<int> rz = query(qr[i][2]);
            int ans = dfs(0, ds.size(), lz, rz, qr[i][3]);
            printf("%d\n", ds[ans]);
        } else {
            add(qr[i][1], n, a[qr[i][1]], -1);
            add(qr[i][1], n, qr[i][2], 1);
            a[qr[i][1]] = qr[i][2];
        }
    }
}
