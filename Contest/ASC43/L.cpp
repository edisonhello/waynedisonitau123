#include <bits/stdc++.h>
using namespace std;


struct tree {
    vector<int> lc, rc, lf, del;
    int n, gd, sz;
    tree() {}
    tree(int n, vector<int> lc, vector<int> rc, vector<int> lf): n(n), lc(lc), rc(rc), lf(lf) {}
    void init() {
        scanf("%d", &n);
        if (n == 0) exit(0);
        lc = vector<int>(n, -1);
        rc = vector<int>(n, -1);
        lf = vector<int>(n,  0);
        del = vector<int>(n, 0);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &lc[i], &rc[i]);
            --lc[i], --rc[i];
            if (lc[i] < 0 && rc[i] < 0) lf[i] = 1;
        }
        *this = normalize(n, lc, rc, del);
    }
    void dfs(int x, vector<int> &del, vector<int> &tf) {
        // printf("x = %d\n", x);
        if (~rc[x]) dfs(rc[x], del, tf);
        if (~lc[x]) dfs(lc[x], del, tf);
        if (gd > 0 && ~rc[x] && ~lc[x]) {
            if (tf[rc[x]] && tf[lc[x]]) {
                tf[x] = 1;
                del[lc[x]] = 1;
                del[rc[x]] = 1;
                --gd;
            }
        }
    }
    vector<int> tr;
    void dfs2(int x, vector<int> &rev, const vector<int> &del) {
        rev[x] = sz++;
        tr.push_back(x);
        if (~lc[x] && !del[lc[x]]) dfs2(lc[x], rev, del);
        if (~rc[x] && !del[rc[x]]) dfs2(rc[x], rev, del);
    }
    tree normalize(int n, const vector<int> &lc, const vector<int> &rc, const vector<int> &del) {
        vector<int> v;
        for (int i = 0; i < n; ++i) {
            if (!del[i]) {
                v.push_back(i);
            }
        }
        vector<int> rev(n, -1);
        sz = 0;
        assert(v.size() && v[0] == 0);
        tr.clear();
        dfs2(0, rev, del);
        vector<int> tlc(sz, -1), trc(sz, -1), tlf(sz, 0);
        for (int i = 0; i < sz; ++i) {
            int x = tr[i];
            // printf("x = %d lc = %d rc = %d\n", x, lc[x], rc[x]);
            if (~lc[x]) tlc[i] = rev[lc[x]];
            if (~rc[x]) trc[i] = rev[rc[x]];
            if (tlc[i] == -1 && trc[i] == -1) tlf[i] = 1;
            // printf("i = %d tlc = %d trc = %d\n", i, tlc[i], trc[i]);
        }
        return tree(sz, tlc, trc, tlf);
    }
    tree get(int d) {
        // printf("n = %d d = %d\n", n, d);
        vector<int> del(n);
        assert((int)lf.size() == n);
        vector<int> tf(lf.begin(), lf.end());
        assert((int)tf.size() == n);
        gd = d;
        // puts("get?");
        dfs(0, del, tf);
        // puts("get!");
        return normalize(n, lc, rc, del);
    }
    bool operator==(const tree &t) const {
        return n == t.n && lc == t.lc && rc == t.rc;
    }
    void output() const {
        printf("%d\n", n);
        for (int i = 0; i < n; ++i) printf("%d %d\n", lc[i] + 1, rc[i] + 1);
    }
};

int main() {
#ifdef ONLINE_JUDGE
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
#endif
    while (true) {
        tree t1, t2;
        t1.init();
        t2.init();
        if (t1.n > t2.n) t1 = t1.get((t1.n - t2.n) / 2);
        else t2 = t2.get((t2.n - t1.n) / 2);
        if (t1 == t2) {
            t1.output();
            continue;
        }
        int ans = 0;
        for (int i = 20; i >= 0; --i) {
            assert(t1.n == t2.n);
            if (t1.n - 1 < 2 * (ans + (1 << i))) continue;
            tree f1 = t1.get(ans + (1 << i));
            tree f2 = t2.get(ans + (1 << i));
            if (f1 == f2) continue;
            ans += (1 << i);
        }
        ans++;
        t1 = t1.get(ans);
        t1.output();
    }
}
