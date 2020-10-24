#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> g(N);
        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < M; ++j) {
                if (s[j] == '1') g[i].push_back(j);
            }
        }
        vector<int> match(M, -1);
        vector<bool> vis(M);

        function<bool(int)> Dfs = [&](int x) {
            for (int u : g[x]) {
                if (vis[u]) continue;
                vis[u] = true;
                if (match[u] == -1 || Dfs(match[u])) {
                    match[u] = x;
                    return true;
                }
            }
            return false;
        };

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            fill(vis.begin(), vis.end(), false);
            ans += Dfs(i);
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
}
