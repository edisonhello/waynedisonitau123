#pragma GCC optimize("O3")

#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

const int maxn = 2000 + 5;
const int mod = 1e9 + 123;
const int mult = 131;
int h[maxn][maxn + maxn], fa[maxn], sz[maxn];
bool qr[maxn][maxn];
vector<int> ans[maxn], z[maxn];
char s[maxn][maxn + maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

int iter = 0;

void merge(int x, int y, int q, int k) {
    x = find(x), y = find(y);
    assert(x != y);
    if (sz[x] > sz[y]) swap(x, y);
    ++iter;
    for (int i = 0; i < q; ++i) {
        if (qr[x][i] && qr[y][i]) {
            ans[i].push_back(k);
        }
        qr[y][i] |= qr[x][i];
    }
    sz[y] += sz[x];
    fa[x] = y;
}

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, m, q; scanf("%d%d%d", &n, &m, &q);
        for (int i = 0; i < n; ++i) scanf("%s", s[i]);
        for (int i = 0; i < n; ++i) {
            h[i][m] = 0;
            h[i][m - 1] = s[i][m - 1];
            for (int j = m - 2; j >= 0; --j)
                h[i][j] = (h[i][j + 1] * 1LL * mult + s[i][j]) % mod;
        }

        for (int i = 0; i < n; ++i) fa[i] = i, sz[i] = 1;

        for (int i = 0; i < q; ++i) {
            int k; scanf("%d", &k);
            for (int j = 0; j < n; ++j) qr[j][i] = false;
            for (int j = 0; j < k; ++j) {
                int v; scanf("%d", &v);
                qr[v][i] = true;
            }
            ans[i].clear();
        }

        for (int i = 0; i < m; ++i) {
            vector<pair<int, int>> vv;
            for (int j = 0; j < n; ++j) {
                int k = h[j][i + 1];
                if (find(j) != j) continue;
                vv.emplace_back(k, find(j));
                // cc[k].push_back(find(j));
            }
            sort(vv.begin(), vv.end());
            for (int j = 0; j + 1 < (int)vv.size(); ++j) {
                if (vv[j].first == vv[j + 1].first)
                    merge(vv[j].second, vv[j + 1].second, q, i);
            }
            /* for (auto it : cc) {
               if (it.second.size() > 1) {
               assert(it.second.size() == 2);
               merge(it.second[0], it.second[1], q, i);
               }
               } */
        }

        assert(iter < n);
        iter = 0;

        printf("Case #%d:\n", tc);
        for (int i = 0; i < q; ++i) {
            sort(ans[i].begin(), ans[i].end());
            ans[i].resize(unique(ans[i].begin(), ans[i].end()) - ans[i].begin());
            printf("%d ", (int)ans[i].size());
            for (int j : ans[i]) printf("%d ", j);
            puts("");
        }
    }
    return 0;
}
