#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> vis(N);
    int ans = 0, odd = 0, ed = 0;

    auto Dfs = [&](auto dfs, int x) -> void {
        vis[x] = true;
        odd += (g[x].size() % 2 == 1);
        ed += g[x].size();
        for (int u : g[x]) {
            if (!vis[u]) dfs(dfs, u);
        }
    };

    for (int i = 0; i < N; ++i) {
        if (vis[i]) continue;
        odd = 0;
        ed = 0;
        Dfs(Dfs, i);
        if (ed > 0) ans += max(1, odd / 2);
    }

    while (Q--) {
        int K;
        cin >> K;
        if (ans <= K) cout << "YES\n";
        else cout << "NO\n";
    }
}
