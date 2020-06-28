#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    vector<vector<int>> dist(n * m, vector<int>(n * m, 200));
    vector<vector<tuple<int, int, int>>> from(n * m, vector<tuple<int, int, int>>(n * m));
    constexpr int dx[4] = {1, 0, -1, 0};
    constexpr int dy[4] = {0, 1, 0, -1};
    constexpr char kChar[4] = {'D', 'R', 'U', 'L'};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] != '#') {
                dist[i * m + j][i * m + j] = 0;
                for (int k = 0; k < 4; ++k) {
                    if (i + dx[k] < 0 || i + dx[k] >= n) continue;
                    if (j + dy[k] < 0 || j + dy[k] >= m) continue;
                    if (s[i + dx[k]][j + dy[k]] == '#') continue;
                    dist[i * m + j][(i + dx[k]) * m + (j + dy[k])] = 1;
                    from[i * m + j][(i + dx[k]) * m + (j + dy[k])] = make_tuple(-1, -1, k);
                }
            }
        }
    }
    vector<vector<pair<int, int>>> que(100);
    for (int i = 0; i < n * m; ++i) {
        for (int j = 0; j < n * m; ++j) {
            if (dist[i][j] == 200) continue;
            que[dist[i][j]].emplace_back(i, j);
        }
    }
    vector<vector<bool>> vis(n * m, vector<bool>(n * m));
    for (int i = 0; i < 100; ++i) {
        for (auto g : que[i]) {
            int u = g.first, v = g.second;
            if (vis[u][v]) continue;
            vis[u][v] = true;
            int x1 = u / m, y1 = u % m;
            int x2 = v / m, y2 = v % m;
            for (int k = 0; k < 4; ++k) {
                if (x1 + dx[k] < 0 || x1 + dx[k] >= n) continue;
                if (y1 + dy[k] < 0 || y1 + dy[k] >= m) continue;
                if (x2 + dx[2 ^ k] < 0 || x2 + dx[2 ^ k] >= n) continue;
                if (y2 + dy[2 ^ k] < 0 || y2 + dy[2 ^ k] >= m) continue;
                if (s[x1 + dx[k]][y1 + dy[k]] == '#') continue;
                if (s[x2 + dx[2 ^ k]][y2 + dy[2 ^ k]] == '#') continue;
                int uu = (x1 + dx[k]) * m + (y1 + dy[k]);
                int vv = (x2 + dx[2 ^ k]) * m + (y2 + dy[2 ^ k]);
                if (dist[uu][vv] > dist[u][v] + 2) {
                    dist[uu][vv] = dist[u][v] + 2;
                    from[uu][vv] = make_tuple(u, v, k);
                    if (dist[uu][vv] < 100) {
                        que[dist[uu][vv]].emplace_back(uu, vv);
                    }
                }
            }
        }
    }
    vector<vector<int>> g(n * m);
    for (int i = 0; i < n * m; ++i) {
        for (int j = 0; j < n * m; ++j) {
            assert(dist[i][j] == dist[j][i]);
            if (dist[i][j] <= 100) g[i].push_back(j);
        }
    }
    int st = -1, ed = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == 'S') {
                st = i * m + j;
            }
            if (s[i][j] == 'F') {
                ed = i * m + j;
            }
        }
    }
    assert(st != -1 && ed != -1);
    vector<int> qu(1, st);
    vector<int> ds(n * m, -1);
    vector<int> fr(n * m, -1);
    ds[st] = 0;
    for (int it = 0; it < qu.size(); ++it) {
        int x = qu[it];
        for (int u : g[x]) {
            if (ds[u] == -1) {
                ds[u] = ds[x] + 1;
                fr[u] = x;
                qu.push_back(u);
            }
        }
    }
    cout << ds[ed] << "\n";
    if (ds[ed] == -1) return 0;

    auto Path = [&](int x, int y) {
        string res = "";
        while (dist[x][y] > 1) {
            int a = get<0>(from[x][y]);
            int b = get<1>(from[x][y]);
            int c = get<2>(from[x][y]);
            res += kChar[c ^ 2];
            x = a;
            y = b;
        }
        string rev = res;
        reverse(rev.begin(), rev.end());
        if (dist[x][y] == 0) return res + rev;
        return res + kChar[get<2>(from[x][y])] + rev;
    };

    vector<string> ans;
    for (int x = ed; x != st; x = fr[x]) {
        ans.push_back(Path(fr[x], x));
    }
    reverse(ans.begin(), ans.end());
    for (auto &s : ans) cout << s << "\n";
    return 0;
}

