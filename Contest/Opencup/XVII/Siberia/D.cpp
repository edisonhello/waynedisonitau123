#include <bits/stdc++.h>
using namespace std;

struct Tree {
    vector<double> tree, tag;
    int n;

    Tree(int n) : n(n), tree(n * 4), tag(n * 4) {}

    void Modify(int ql, int qr, double v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                tree[o] += v;
                tag[o] += v;
                return;
            }
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        _(_, 0, n);
    }

    void Update(int p, double v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r - l == 1) {
                tree[o] = min(tree[o], v);
                return;
            }
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            if (p < m) self(self, l, m, o * 2 + 1);
            else self(self, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };
        _(_, 0, n);
    }

    double Query(int ql, int qr) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return 1E18;
            if (l >= ql && r <= qr) return tree[o];
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            return min(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
        };
        return _(_, 0, n);
    }
};

int main() {
    int A, B;
    cin >> A >> B;
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector<int64_t> cost(n);
    vector<int> ds(b.begin(), b.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) {
        cost[i] = min(0LL + a[i] + b[i] + B, 0LL + A - a[i] + A - b[i] + B);
    }
    vector<double> link(n);
    for (int i = 0; i < n; ++i) {
        link[i] = hypot(B, abs(a[i] - b[i]));
    }
    for (int i = 0; i < n; ++i) {
        b[i] = lower_bound(ds.begin(), ds.end(),  b[i]) - ds.begin() + 1;
    }
    b.push_back(0);

    Tree dp1(n + 1), dp2(n + 1);
    dp1.Modify(1, n + 1, 1E18);
    dp2.Modify(1, n + 1, 1E18);
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] < a[j]; });



    for (int i = 0; i < n; ++i) {
        double x = dp2.Query(0, b[ord[i]]);
        double y = dp1.Query(0, b[ord[i]]);
#if 0
        cout << "i = " << ord[i] << endl;
        cout << "x = " << x << " y = " << y << endl;
        cout << "x' = " << x + link[ord[i]] << " y' = " << y + cost[ord[i]] << endl;
#endif 
        if (i == 0 || b[ord[i]] > b[ord[i - 1]]) {
            dp1.Modify(0, n + 1, link[ord[i]]);
            dp2.Modify(0, n + 1, cost[ord[i]]);
            if (i > 0) {
                dp1.Update(b[ord[i - 1]], x + link[ord[i]]);
                dp2.Update(b[ord[i - 1]], y + cost[ord[i]]);
            }
        } else {
            dp1.Modify(0, n + 1, 1E18);
            dp2.Modify(0, n + 1, 1E18);
            dp1.Update(b[ord[i - 1]], x + link[ord[i]]);
            dp2.Update(b[ord[i - 1]], y + cost[ord[i]]);
        }
#if 0
        cout << "dp1: ";
        for (int j = 0; j <= n; ++j) cout << dp1.Query(j, j + 1) << " "; cout << "\n";
        cout << "dp2: ";
        for (int j = 0; j <= n; ++j) cout << dp2.Query(j, j + 1) << " "; cout << "\n";
#endif
    }
    double res = min(dp1.Query(0, n + 1), dp2.Query(0, n + 1));
    if (res > 1E15) cout << "-1\n";
    else cout << fixed << setprecision(15) << res << "\n";
}

