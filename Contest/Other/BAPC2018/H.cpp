#include <bits/stdc++.h>
using namespace std;
#define int long long 

vector<pair<int, int>> g[100005], ig[100005];
int d[100005][2];
bool vis[100005][2];
int avis[100005][2];

int32_t main() {
    int n, m, s, t; cin >> n >> m >> s >> t;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        ig[v].emplace_back(u, w);
    }

    for (int i = 0; i < n; ++i) d[i][0] = 0x3f3f3f3f3f3f3f3f, d[i][1] = 0;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    d[t][0] = d[t][1] = 0;
    pq.emplace(0, make_pair(t, 0));
    pq.emplace(0, make_pair(t, 1));

    while (pq.size()) {
        while (pq.size() && vis[pq.top().second.first][pq.top().second.second]) pq.pop();
        if (pq.empty()) break;


        int now = pq.top().second.first;
        int type = pq.top().second.second;
        vis[now][type] = 1;
        // cerr << "now, type = " << now << ' ' << type << endl;

        for (auto &e : ig[now]) {
            avis[e.first][type]++;
        }

        for (auto &e : ig[now]) {
            int ei = e.first;
            int et = !type;
            
            int nd = d[now][type] + e.second;

            // cerr << "try update " << ei << ' ' << et << " with nd = " << nd << " orig " << d[ei][et] << endl;
            if (et == 1) {
                // cerr << "avis = " << avis[ei][0] << endl;
                if (avis[ei][0] == (int)g[ei].size()) {
                    // cerr << "try update " << ei << ' ' << et << " with nd = " << nd << " orig " << d[ei][et] << endl;
                    int mx = 0;
                    for (auto &e : g[ei]) {
                        mx = max(d[e.first][0] + e.second, mx);
                    }
                    d[ei][et] = mx;
                    pq.emplace(mx, make_pair(ei, 1));
                }
            } else {
                if (d[ei][et] > nd) {
                    if (avis[ei][1]) {
                        // cerr << "try update " << ei << ' ' << et << " with nd = " << nd << " orig " << d[ei][et] << endl;
                        d[ei][et] = nd;
                        pq.emplace(nd, make_pair(ei, 0));
                    }
                }
            }
        }
    }

    if (!vis[s][1]) {
        cout << "infinity" << endl;
    } else {
        cout << d[s][1] << endl;
    }

    // for (int i = 0; i < n; ++i) cerr << "d " << i << " = " << d[i][0] << ' ' << d[i][1] << endl;


}

