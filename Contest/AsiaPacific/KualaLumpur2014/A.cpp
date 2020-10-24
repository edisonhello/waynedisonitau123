#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n, m; cin >> n >> m;
        vector<vector<pair<int, int>>> g(n);
        vector<vector<pair<int, int>>> ig(n);
        for (int i = 0; i < m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            g[u].emplace_back(v, w);
            ig[v].emplace_back(u, w);
        }

        vector<int> d(n, 1000000000);
        vector<int> upd(n, 0);
        d[0] = 0;
        vector<bool> inq(n, false);
        queue<int> q;
        q.push(0);
        inq[0] = 1;

        while (q.size()) {
            int now = q.front(); q.pop(); inq[now] = 0;

            for (auto &p : g[now]) {
                if (d[p.first] > d[now] + p.second) {
                    d[p.first] = d[now] + p.second;
                    ++upd[p.first];
                    if (upd[p.first] >= n) continue;
                    if (!inq[p.first]) {
                        inq[p.first] = 1;
                        q.push(p.first);
                    }
                }
            }
        }

        vector<bool> reach(n, false);
        function<void(int)> dfs = [&] (int now) {
            reach[now] = 1;
            for (auto &p : ig[now]) {
                if (!reach[p.first]) dfs(p.first);
            }
        };

        dfs(0);


        if (d[0] < 0 || upd[0] >= n) {
            cout << "possible" << '\n';
        } else {
            bool yes = 0;
            for (int i = 1; i < n; ++i) if (upd[i] >= n && reach[i]) {
                cout << "possible" << '\n';
                yes = 1;
                break;
            }
            if (!yes) {
                cout << "not possible" << '\n';
            }
        }

    }
}
