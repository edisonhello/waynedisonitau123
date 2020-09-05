#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

vector<int> dijk(vector<vector<int>> &g, int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);
    vector<bool> vis(g.size(), false);
    vector<int> d(g.size(), 1000000000);
    d[s] = 0;
    while (pq.size()) {
        while (pq.size() && vis[pq.top().second]) pq.pop();
        if (pq.empty()) break;

        int now = pq.top().second;
        vis[now] = 1;

        for (int i : g[now]) {
            int nd = d[now] + 1;
            if (nd < d[i]) {
                d[i] = nd;
                pq.emplace(nd, i);
            }
        }
    }
    return d;
}

void solve(int n, int m) {
    vector<vector<pair<int, char>>> mp(n, vector<pair<int, char>>(m));
    auto Id = [&] (int x, int y) { return x * m + y; };
    vector<vector<int>> G(n * m);
    vector<vector<int>> iG(n * m);
    auto AddEdge = [&] (int u, int v) {
        // cerr << "addedge " << u << ' ' << v << endl;
        G[u].push_back(v);
        iG[v].push_back(u);
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == n - 1 && j == m - 1) continue;
            int x; char d;
            scanf("%d%c", &x, &d);
            mp[i][j] = make_pair(x, d);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == n - 1 && j == m - 1) continue;
            int ni = i, nj = j;
            if (mp[i][j].second == 'E') nj += mp[i][j].first;
            if (mp[i][j].second == 'W') nj -= mp[i][j].first;
            if (mp[i][j].second == 'N') ni -= mp[i][j].first;
            if (mp[i][j].second == 'S') ni += mp[i][j].first;
            if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                AddEdge(Id(i, j), Id(ni, nj));
            }
        }
    }

    vector<int> d = dijk(G, 0);
    vector<int> id = dijk(iG, Id(n - 1, m - 1));

    int normal = d[Id(n - 1, m - 1)];
    tuple<int, int, int, pair<int, char>> best(INT_MAX, -1, -1, make_pair(-1, 'Z'));

    for (int i = 0; i < n; ++i) {
        int mind = 1e9;
        int nearj = -1;
        for (int j = 0; j < m; ++j) {
            auto Gen = [&] (int k) {
                if (k < j) return make_pair(j - k, 'W');
                else return make_pair(k - j, 'E');
            };
            int nd = d[Id(i, j)] + 1 + mind;
            best = min(best, make_tuple(nd, i, j, Gen(nearj)));
            if (id[Id(i, j)] <= mind) {
                mind = id[Id(i, j)];
                nearj = j;
            }
        }
        mind = 1e9;
        nearj = -1;
        for (int j = m - 1; j >= 0; --j) {
            auto Gen = [&] (int k) {
                if (k < j) return make_pair(j - k, 'W');
                else return make_pair(k - j, 'E');
            };
            int nd = d[Id(i, j)] + 1 + mind;
            best = min(best, make_tuple(nd, i, j, Gen(nearj)));
            if (id[Id(i, j)] <= mind) {
                mind = id[Id(i, j)];
                nearj = j;
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        int mind = 1e9;
        int neari = -1;
        for (int i = 0; i < n; ++i) {
            auto Gen = [&] (int k) {
                if (k < i) return make_pair(i - k, 'N');
                else return make_pair(k - i, 'S');
            };
            int nd = d[Id(i, j)] + 1 + mind;
            best = min(best, make_tuple(nd, i, j, Gen(neari)));
            if (id[Id(i, j)] <= mind) {
                mind = id[Id(i, j)];
                neari = i;
            }
        }
        mind = 1e9;
        neari = -1;
        for (int i = n - 1; i >= 0; --i) {
            auto Gen = [&] (int k) {
                if (k < i) return make_pair(i - k, 'N');
                else return make_pair(k - i, 'S');
            };
            int nd = d[Id(i, j)] + 1 + mind;
            best = min(best, make_tuple(nd, i, j, Gen(neari)));
            if (id[Id(i, j)] <= mind) {
                mind = id[Id(i, j)];
                neari = i;
            }
        }
    }

    if (get<0>(best) >= 1000000000 && normal >= 1000000000) {
        cout << "impossible" << '\n';
    } else if (get<0>(best) >= normal) {
        cout << "none " << normal << '\n';
    } else {
        cout << get<1>(best) << ' ' << get<2>(best) << ' ' << get<3>(best).first << get<3>(best).second << ' ' << get<0>(best) << '\n';
    }
}

int main() {
    int T = 1;
    int n, m; 
    while (scanf("%d%d", &n, &m), n) {
        cout << "Case " << T << ": ";
        solve(n, m);
        ++T;
    }
}

