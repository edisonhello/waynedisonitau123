#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n * (n - 1) / 2; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back(w);
        g[v].push_back(w);
    }
    int64_t res = 0;
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
        for (int j = 1; j < g[i].size(); j += 2) res += g[i][j];
    }
    cout << res << endl;
}

