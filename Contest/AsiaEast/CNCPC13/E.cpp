#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<vector<int>> g(N);
        for (int i = 0; i < N - 1; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            u--;
            v--;
            g[u].push_back(w);
            g[v].push_back(w);
        }
        int64_t ans = 0;
        for (int i = 0; i < N; ++i) {
            int j = min_element(g[i].begin(), g[i].end()) - g[i].begin();
            ans += 1LL * g[i][j] * (g[i].size() - 1);
            ans += accumulate(g[i].begin(), g[i].end(), 0LL);
            ans -= g[i][j];
        }
        cout << ans << "\n";
    }
}

