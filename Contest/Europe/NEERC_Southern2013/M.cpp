#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int d[909][909];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) d[i][j] = 10000;
        for (int i = 1; i <= n; ++i) d[i][i] = 0;
        vector<pair<int, int>> e; e.reserve(m);
        while (m--) {
            int u, v; cin >> u >> v;
            d[u][v] = 1;
            e.emplace_back(u, v);
        }
        for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (auto [i, j] : e) {
            int mn = 1000;
            for (int k = 1; k <= n; ++k) {
                if (k == i || k == j) continue;
                if (d[i][k] == d[j][k] + 1 || d[k][j] == d[k][i] + 1) continue;
                mn = min(mn, d[i][k] + d[k][j]);
            }
            if (mn == 1000) cout << 0 << " ";
            else cout << mn << " ";
        }
        cout << '\n';
    }
}
