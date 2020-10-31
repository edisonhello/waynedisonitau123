#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int M, n, rn; cin >> M >> n >> rn;
        vector<int> cost(n), price(n);
        for (int i = 0; i < n; ++i) {
            int c; cin >> c;
            if (c == 0) {
                cost[i] = 10001;
                cin >> price[i];
            } else cin >> cost[i] >> price[i];
        }

        vector<vector<vector<pair<int, int>>>> rules(n);
        vector<set<int>> affe(n);
        while (rn--) {
            int target; cin >> target; --target;
            int nn; cin >> nn; 
            vector<pair<int, int>> rule;
            while (nn--) {
                int x, i; cin >> x >> i;
                --x;
                rule.emplace_back(x, i);
                affe[x].insert(target);
            }
            rules[target].push_back(rule);
        }

        vector<int> d(cost);
        vector<bool> vis(n, false);
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < n; ++i) pq.emplace(-d[i], i);

        while (pq.size()) {
            int now = pq.top().second;
            pq.pop();
            if (vis[now]) continue;
            vis[now] = 1;
            for (auto i : affe[now]) {
                for (auto &rule : rules[i]) {
                    int nco = 0;
                    for (auto p : rule) {
                        nco += d[p.first] * p.second;
                    }

                    if (nco < d[i]) {
                        d[i] = nco;
                        pq.emplace(-nco, i);
                    }
                }
            }
        }

        vector<int> pack(M + 1, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = d[i]; j <= M; ++j) {
                pack[j] = max(pack[j], pack[j - d[i]] + price[i]);
            }
        }

        cout << *max_element(pack.begin(), pack.end()) << '\n';
    }
}

