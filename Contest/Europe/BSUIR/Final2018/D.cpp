#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;
vector<pair<int, int>> pos[kN];
vector<int> dk[kN];
vector<int> dp[kN];
vector<pair<int, int>> fr[kN];

using Data = tuple<int, int, int>;
Data nd[kN * 4];

void Modify(int l, int r, int p, Data v, int o = 0) {
    if (r - l == 1) {
        nd[o] = v;
        return;
    }
    int m = (l + r) >> 1;
    if (p < m) Modify(l, m, p, v, o * 2 + 1);
    else Modify(m, r, p, v, o * 2 + 2);
    nd[o] = max(nd[o * 2 + 1], nd[o * 2 + 2]);
}

Data Query(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return make_tuple(0, -1, -1);
    if (l >= ql && r <= qr) return nd[o];
    int m = (l + r) >> 1;
    return max(Query(l, m, ql, qr, o * 2 + 1), Query(m, r, ql, qr, o * 2 + 2));
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int> ds;
    for (int i = 0; i < n; ++i) {
        int m; scanf("%d", &m);
        dk[i].resize(m);
        for (int j = 0; j < m; ++j) {
            scanf("%d", &dk[i][j]);
            ds.push_back(dk[i][j]);
        }
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < n; ++i) {
        sort(dk[i].begin(), dk[i].end());
        dk[i].resize(unique(dk[i].begin(), dk[i].end()) - dk[i].begin());
        dp[i].resize(dk[i].size());
        fr[i].resize(dk[i].size());
        for (int j = 0; j < dk[i].size(); ++j) {
            dk[i][j] = lower_bound(ds.begin(), ds.end(), dk[i][j]) - ds.begin();
            pos[dk[i][j]].emplace_back(i, j);
        }
    }

    auto CyclicQuery = [&](int l, int r) {
        if (l <= r) return Query(0, n, l, r + 1);
        return max(Query(0, n, 0, r + 1), Query(0, n, l, n));
    };

    for (int i = ds.size() - 1; i >= 0; --i) {
        for (auto j : pos[i]) {
            int l = (j.first + 1) % n, r = (j.first + k + 1) % n;
            Data dt = CyclicQuery(l, r);
            dp[j.first][j.second] = get<0>(dt) + 1;
            fr[j.first][j.second] = make_pair(get<1>(dt), get<2>(dt));
        }
        for (auto j : pos[i]) {
            Modify(0, n, j.first, make_tuple(dp[j.first][j.second], j.first, j.second));
        }
    }
    int ans = 0;
    int x = -1, y = -1;
    for (int i = 0; i < k + 1; ++i) {
        for (int j = 0; j < dk[i].size(); ++j) {
            if (dp[i][j] > ans) {
                x = i;
                y = j;
                ans = dp[i][j];
            }
        }
    }
    printf("%d\n", ans);
    if (ans == 0) return 0;
    while (true) {
        printf("%d %d\n", x + 1, ds[dk[x][y]]);
        if (dp[x][y] == 1) break;
        tie(x, y) = fr[x][y];
    }
    return 0;
}
