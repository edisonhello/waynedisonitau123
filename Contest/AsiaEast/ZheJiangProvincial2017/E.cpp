#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> ds(A.begin(), A.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < N; ++i) {
        B[i] = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin();
    }
    int M = ds.size();

    vector<int> lc, rc, sz;
    vector<int64_t> sum;
    // lc.reserve(100000);
    // rc.reserve(100000);
    // sz.reserve(100000);
    // sum.reserve(100000);

    auto GetNode = [&](int z = -1) {
        int res = lc.size();
        if (z == -1) {
            lc.push_back(-1);
            rc.push_back(-1);
            sz.push_back(0);
            sum.push_back(0);
        } else {
            lc.push_back(lc[z]);
            rc.push_back(rc[z]);
            sz.push_back(sz[z]);
            sum.push_back(sum[z]);
        }
        return res;
    };
    vector<int> root(N + 1);

    auto Build = [&]() {
        auto dfs = [&](auto dfs, int l, int r) -> int {
            int res = GetNode();
            if (r - l == 1) return res;
            int m = (l + r) >> 1;
            int x = dfs(dfs, l, m);
            int y = dfs(dfs, m, r);
            lc[res] = x;
            rc[res] = y;
            return res;
        };

        return dfs(dfs, 0, M);
    };

    int Q;
    cin >> Q;
    vector<int> L(Q), R(Q), K(Q);
    vector<vector<int>> S(N + 1);
    for (int i = 0; i < Q; ++i) {
        cin >> L[i] >> R[i] >> K[i];
        L[i]--;
        S[R[i]].push_back(i);
    }

    root[0] = Build();

    auto Modify = [&](int r, int p) {
        auto dfs = [&](auto dfs, int l, int r, int o) -> int {
            int res = GetNode(o);
            if (r - l == 1) {
                sz[res]++;
                sum[res] += ds[l];
                return res;
            }
            int m = (l + r) >> 1;
            if (p < m) {
                int x = dfs(dfs, l, m, lc[o]);
                lc[res] = x;
            } else {
                int y = dfs(dfs, m, r, rc[o]);
                rc[res] = y;
            }
            sz[res] = sz[lc[res]] + sz[rc[res]];
            sum[res] = sum[lc[res]] + sum[rc[res]];
            return res;
        };

        return dfs(dfs, 0, M, r);
    };

    for (int i = 0; i < N; ++i) {
        root[i + 1] = Modify(root[i], B[i]);
    }
    vector<int64_t> res(Q);

    auto Query = [&](int tl, int tr, int k) {
        auto dfs = [&](auto dfs, int l, int r, int x, int y, int k) -> int64_t {
            if (r - l == 1) {
                assert(sz[y] - sz[x] >= k);
                return 1LL * k * ds[l];
            }
            int m = (l + r) >> 1;
            assert(sz[y] >= sz[x]);
            assert(sum[y] >= sum[x]);
            if (sz[rc[y]] - sz[rc[x]] >= k) {
                return dfs(dfs, m, r, rc[x], rc[y], k);
            } else {
                assert(rc[x] != -1);
                assert(sum[rc[y]] >= sum[rc[x]]);
                return sum[rc[y]] - sum[rc[x]] + dfs(dfs, l, m, lc[x], lc[y], k - (sz[rc[y]] - sz[rc[x]]));
            }
        };

        return dfs(dfs, 0, M, tl, tr, k);
    };

    for (int i = 1; i <= N; ++i) {
        for (int u : S[i]) {
            res[u] = Query(root[L[u]], root[i], K[u]);
        }
    }
    for (int i = 0; i < Q; ++i) {
        int m = R[i] - L[i];
        res[i] += 1LL * m * (m + 1) * (2 * m + 1) / 6;
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) Solve();
}

