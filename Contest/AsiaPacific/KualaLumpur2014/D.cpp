#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        vector<int> M(N);
        for (int i = 0; i < N; ++i) cin >> M[i];
        vector<vector<int>> g(N);
        for (int i = 0; i < N; ++i) {
            int P;
            cin >> P;
            if (P > 0) g[P - 1].push_back(i);
        }
        vector<int> dp(N, -1);

        function<int(int)> Dfs = [&](int x) -> int {
            if (dp[x] != -1) return dp[x];
            vector<bool> taken(g[x].size() + 1);
            for (int u : g[x]) {
                int v = Dfs(u);
                if (v < taken.size()) taken[v] = true;
            }
            dp[x] = 0;
            while (taken[dp[x]]) dp[x]++;
            for (int u : g[x]) {
                int v = Dfs(u);
                if (v < taken.size()) taken[v] = false;
            }
            return dp[x];
        };

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            if (M[i] & 1) ans ^= Dfs(i);
        }
        cout << "Case #" << t << ": ";
        if (ans > 0) cout << "first\n";
        else cout << "second\n";
    }
}
