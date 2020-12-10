#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int seg[100005 * 4];

#define mid ((l + r) >> 1)
#define lc (o * 2 + 1)
#define rc (o * 2 + 2)
void modify(int o, int l, int r, int ml, int mr, int x) {
    if (r < ml || mr < l) return;
    if (ml <= l && r <= mr) {
        seg[o] = max(seg[o], x);
        return;
    }
    if (seg[o]) {
        seg[lc] = max(seg[lc], seg[o]);
        seg[rc] = max(seg[rc], seg[o]);
        seg[o] = 0;
    }
    modify(lc, l, mid, ml, mr, x);
    modify(rc, mid + 1, r, ml, mr, x);
}

void dfs(int o, int l, int r) {
    if (l == r) {
        cout << " " << seg[o];
        return;
    }
    if (seg[o]) {
        seg[lc] = max(seg[lc], seg[o]);
        seg[rc] = max(seg[rc], seg[o]);
        seg[o] = 0;
    }
    dfs(lc, l, mid);
    dfs(rc, mid + 1, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int t, T = 0; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<int> t(n), x(n);
        for (int i = 0; i < n; ++i) cin >> t[i] >> x[i];

        vector<int> mxx(100005, 0);
        for (int i = 0; i < n; ++i) {
            mxx[t[i]] = max(mxx[t[i]], x[i]);
        }

        memset(seg, 0, sizeof(seg));

        for (int i = 1; i <= 100000; ++i) {
            for (int nt = 1; nt <= m; nt += i * 2) {
                int r = nt + i - 1;
                r = min(r, m);

                // segs.emplace_back(l, r, i);
                modify(0, 1, m, nt, r, mxx[i]);
            }
        }

        cout << "Case #" << (++T) << ":";
        dfs(0, 1, m);
        cout << '\n';

        
    }
}

