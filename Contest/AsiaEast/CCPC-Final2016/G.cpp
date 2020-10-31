#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";

        int m; cin >> m;
        map<pair<int, int>, int> mp;
        vector<vector<pair<int, int>>> g;
        auto Id = [&] (int x, int y) {
            auto p = make_pair(x, y);
            auto it = mp.find(p);
            if (it != mp.end()) {
                return it->second;
            }
            int z = mp.size();
            g.emplace_back();
            return mp[p] = z;
        };

        vector<tuple<int, int, int>> edges;
        while (m--) {
            int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
            a = Id(a, b);
            b = Id(c, d);
            g[a].emplace_back(b, e);
            g[b].emplace_back(a, e);
            edges.emplace_back(a, b, e);
        }

        // for (auto p : mp) {
        //     cerr << p.first.first << ' ' << p.first.second << " = " << p.second << endl;
        // }

        int n = mp.size();
        int ans = INT_MAX;

        vector<int> d(n, 1000000000);
        priority_queue<pair<int, int>> pq;
        vector<bool> vis(n, false);

        for (auto &bye : edges) {
            int x, y, z;
            tie(x, y, z) = bye;

            fill(d.begin(), d.end(), 1000000000);
            fill(vis.begin(), vis.end(), false);
            while (pq.size()) pq.pop();

            d[x] = 0;
            pq.emplace(0, x);


            while (pq.size()) {
                int now = pq.top().second;
                pq.pop();
                if (vis[now]) continue;
                vis[now] = 1;
                if (now == y) break;
                if (d[now] >= ans - z) break;

                for (auto &p : g[now]) {
                    if (p.first == x || p.first == y) {
                        if ((p.first ^ now) == (x ^ y)) continue;
                    }

                    if (d[p.first] > d[now] + p.second) {
                        d[p.first] = d[now] + p.second;
                        pq.emplace(-d[p.first], p.first);
                    }
                }
            }

            // cerr << "x y d[y] z " << x << ' ' << y << ' ' << d[y] << ' ' << z << endl;

            ans = min(ans, d[y] + z);
        }

        if (ans >= 500000000) ans = 0;
        cout << ans << '\n';
    }

}

