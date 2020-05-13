#include <bits/stdc++.h>
using namespace std;

int ob[255][22];
int d[255][255];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= n; ++j) {
        string x; cin >> x;
        if (x == "X") ob[i][j] = -1;
        else ob[i][j] = atoi(x.c_str());
    }

    for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) d[i][j] = 1e9;
    // for (int i = 1; i <= m; ++i) d[i][i] = 0;

    for (int j = 1; j <= n; ++j) {
        vector<pair<int, int>> v;
        for (int i = 1; i <= m; ++i) {
            if (ob[i][j] == -1) continue;
            v.emplace_back(ob[i][j], i);
        }

        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());

        for (int i = 1; i < (int)v.size(); ++i) {
            // cerr << "v[" << i << "] = " << v[i].first << ' ' << v[i].second << endl;
            d[v[i - 1].second][v[i].second] = v[i - 1].first - v[i].first;
            // cerr << "edge " << v[i - 1].second << " to " << v[i].second << " w " << v[i - 1].first - v[i].first << endl;
        }
    }

    for (int k = 1; k <= m; ++k) for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }

    int loop = 1e9;
    for (int i = 1; i <= m; ++i) loop = min(loop, d[i][i]);

    if (loop == 1e9) cout << -1 << endl;
    else cout << loop << endl;
}

