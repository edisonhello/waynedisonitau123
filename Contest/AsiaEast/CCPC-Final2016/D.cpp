#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n, m, x; cin >> n >> m >> x;
        vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n; ++i) if (i != x) {
            g[i].push_back(x);
            g[x].push_back(i);
        }

        vector<long long> val(n + 1, 0);
        for (int i = 1; i <= n; ++i) cin >> val[i];

        while (m--) {
            int u, v; cin >> u >> v;
            g[v].push_back(u);
            g[u].push_back(v);
        }

        vector<int> minto(n + 1);
        iota(minto.begin(), minto.end(), 0);
        for (int i = 1; i <= n; ++i) {
            for (int j : g[i]) minto[i] = min(minto[i], j);
        }

        vector<int> cnt(n + 1, 0);
        for (int i = 1; i <= n; ++i) ++cnt[minto[i]];

        long long ans = 0;
        long long le = 0;
        for (int i = n; i >= 1; --i) {
            le += cnt[i];
            long long u = min(le, val[i]);
            le -= u;
            val[i] -= u;
            ans += val[i];
        }

        cout << ans << '\n';
    }
}

