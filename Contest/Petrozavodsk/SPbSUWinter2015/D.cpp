#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] > a[j];
        return b[i] > b[j];
    });

    vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[ord[i]] = i;
    vector<int> bord(n);
    iota(bord.begin(), bord.end(), 0);
    sort(bord.begin(), bord.end(), [&](int i, int j) {
        if (b[i] != b[j]) return b[i] > b[j];
        return pos[i] > pos[j];
    });

    int64_t res = 0;

    vector<int> s(n);
    vector<int> tree(n * 4), tag(n * 4);
    for (int i = 0; i < n; ++i) s[i] = i + 1;

    auto Build = [&]() {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r - l == 1) {
                tree[o] = s[l];
                return;
            }
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        _(_, 0, n);
    };

    Build();

    auto Modify = [&](int ql, int qr, int v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                tree[o] -= v;
                tag[o] += v;
                return;
            }
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] -= tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        _(_, 0, n);
    };

    auto Query = [&](int ql, int qr) {
        auto _ = [&](auto self, int l, int r, int o = 0) -> int {
            if (l >= qr || ql >= r) return 1E9;
            if (l >= ql && r <= qr) return tree[o];
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] -= tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            return min(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
        };
        return _(_, 0, n);
    };

    for (int i = 0; i < n; ++i) {
        if (Query(pos[bord[i]], n) < 2) continue;        
        res += b[bord[i]];
        Modify(pos[bord[i]], n, 2);
    }
    cout << res << "\n";

    return 0;
}

