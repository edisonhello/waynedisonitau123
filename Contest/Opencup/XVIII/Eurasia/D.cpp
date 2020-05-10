#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<vector<int>> app(n, vector<int>(m, -1));
    for (int i = 0; i < k; ++i) {
        int p, q, r;
        cin >> p >> q >> r;
        p--, q--, r--;
        assert(app[p][q] == -1);
        app[p][q] = r;
    }
    vector<vector<double>> p(t, vector<double>(m - 1));
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            cin >> p[i][j];
            if (i > 0) p[i][j] += p[i - 1][j];
        }
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            if (app[i][j] >= 0) {
                g[i].push_back(j);
            }
        }
    }
    vector<double> ex(t);
    vector<int> tt;
    for (int i = 0; i < n; ++i) {
        if (app[i][m - 1] != -1) tt.push_back(app[i][m - 1]);
    }
    sort(tt.begin(), tt.end());
    tt.resize(unique(tt.begin(), tt.end()) - tt.begin());
    for (int i = 0; i < n; ++i) {
        if (app[i][m - 1] == -1) continue;
        for (int j : tt) {
            if (j < app[i][m - 1]) continue;
            double prod = 1.0;
            for (int u : g[i]) {
                if (j - 1 < app[i][u]) continue;
                double pr = p[j - 1][u];
                if (app[i][u] > 0) pr -= p[app[i][u] - 1][u];
                prod *= 1.0 - pr;
            }
            ex[j] += v[i] * prod;
        }
    }
    int res = max_element(ex.begin(), ex.end()) - ex.begin();
    cout << fixed << setprecision(20) << ex[res] << " " << res + 1 << "\n";
    return 0;
}

