#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<pair<int, int>>> p(k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            a[i][j]--;
            p[a[i][j]].emplace_back(i, j);
        }
    }
    vector<vector<int>> dist(n, vector<int>(n, -1));
    for (auto u : p[0]) dist[u.first][u.second] = 0;
    for (int i = 0; i + 1 < k; ++i) {
        for (auto u : p[i]) {
            if (dist[u.first][u.second] == -1) continue;
            for (auto v : p[i + 1]) {
                int d = abs(u.first - v.first) + abs(u.second - v.second) + dist[u.first][u.second];
                if (dist[v.first][v.second] == -1 || dist[v.first][v.second] > d) {
                    dist[v.first][v.second] = d;
                }
            }
        }
    }
    int res = -1;
    for (auto u : p[k - 1]) {
        if (dist[u.first][u.second] == -1) continue;
        if (res == -1 || dist[u.first][u.second] < res) {
            res = dist[u.first][u.second];
        }
    }
    cout << res << endl;
}


