#include <bits/stdc++.h>
using namespace std;

string mp[555];
vector<int> col[555], row[555];
tuple<int, int, int> to[555][555][4]; // [^, >, v, <]

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> mp[i];
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] != '.') {
                row[i].push_back(j);
                col[j].push_back(i);
            }
        }
    }

    function<tuple<int, int, int>(int, int, int)> go = [&] (int x, int y, int dir) {
        if (dir == 0) {
            auto it = lower_bound(col[y].begin(), col[y].end(), x);
            if (it == col[y].begin()) {
                if (mp[x][y] == 'V' || mp[x][y] == 'H') return make_tuple(x, y, 0);
                if (mp[x][y] == '/') return go(x, y, 3);
                if (mp[x][y] == '\\') return go(x, y, 1);
                return make_tuple(x, y, 0);
            } else {
                --it;
                int xx = *it;
                if (mp[xx][y] == 'V' || mp[xx][y] == 'H') return make_tuple(xx, y, 2);
                if (mp[xx][y] == '/') return go(xx, y, 1);
                if (mp[xx][y] == '\\') return go(xx, y, 3);
                return make_tuple(xx, y, 2);
            }
        } else if (dir == 1) {
            auto it = upper_bound(row[x].begin(), row[x].end(), y);
            if (it == row[x].end()) {
                if (mp[x][y] == 'V' || mp[x][y] == 'H') return make_tuple(x, y, 1);
                if (mp[x][y] == '/') return go(x, y, 2);
                if (mp[x][y] == '\\') return go(x, y, 0);
                return make_tuple(x, y, 1);
            } else {
                int yy = *it;
                if (mp[x][yy] == 'V' || mp[x][yy] == 'H') return make_tuple(x, yy, 3);
                if (mp[x][yy] == '/') return go(x, yy, 0);
                if (mp[x][yy] == '\\') return go(x, yy, 2);
                return make_tuple(x, yy, 3);
            }
        } else if (dir == 2) {
            auto it = upper_bound(col[y].begin(), col[y].end(), x);
            if (it == col[y].end()) {
                if (mp[x][y] == 'V' || mp[x][y] == 'H') return make_tuple(x, y, 2);
                if (mp[x][y] == '/') return go(x, y, 1);
                if (mp[x][y] == '\\') return go(x, y, 3);
                return make_tuple(x, y, 2);
            } else {
                int xx = *it;
                if (mp[xx][y] == 'V' || mp[xx][y] == 'H') return make_tuple(xx, y, 0);
                if (mp[xx][y] == '/') return go(xx, y, 3);
                if (mp[xx][y] == '\\') return go(xx, y, 1);
                return make_tuple(xx, y, 0);
            }
        } else if (dir == 3) {
            auto it = lower_bound(row[x].begin(), row[x].end(), y);
            if (it == row[x].begin()) {
                if (mp[x][y] == 'V' || mp[x][y] == 'H') return make_tuple(x, y, 3);
                if (mp[x][y] == '/') return go(x, y, 0);
                if (mp[x][y] == '\\') return go(x, y, 2);
                return make_tuple(x, y, 3);
            } else {
                --it;
                int yy = *it;
                if (mp[x][yy] == 'V' || mp[x][yy] == 'H') return make_tuple(x, yy, 1);
                if (mp[x][yy] == '/') return go(x, yy, 2);
                if (mp[x][yy] == '\\') return go(x, yy, 0);
                return make_tuple(x, yy, 1);
            }
        }
        return make_tuple(-1, -1, -1);
    };
    
    // auto Dir = [&] (const pair<int, int> src, const pair<int, int> dst) {
    //     int r = 0;
    //     if (to[dst.first][dst.second][0] == src) r |= 1;
    //     if (to[dst.first][dst.second][1] == src) r |= 2;
    //     if (to[dst.first][dst.second][2] == src) r |= 1;
    //     if (to[dst.first][dst.second][3] == src) r |= 2;
    //     return r;
    // };


    int s = 0;
    vector<vector<int>> id(n, vector<int>(m, -1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'V' || mp[i][j] == 'H') {
                to[i][j][0] = go(i, j, 0);
                to[i][j][1] = go(i, j, 1);
                to[i][j][2] = go(i, j, 2);
                to[i][j][3] = go(i, j, 3);
                // for (int d = 0; d < 4; ++d) {
                //     cerr << "to " << i << ' ' << j << ' ' << d << ' ' << " = " << get<0>(to[i][j][d]) << ',' << get<1>(to[i][j][d]) << endl;
                // }
                id[i][j] = s++;
            }
        }
    }
    vector<int> uf(s * 2), sz(s * 2);
    vector<bool> ban(s * 2);
    for (int i = 0; i < s * 2; ++i) uf[i] = i;
    for (int i = 0; i < s; ++i) sz[2 * i + 1] = 1;

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
        x = Find(x);
        y = Find(y);
        if (x == y) return;
        sz[y] += sz[x];
        if (ban[x]) ban[y] = true;
        uf[x] = y;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] != 'V' && mp[i][j] != 'H') continue;
            for (int k = 0; k < 4; ++k) {
                int x = mp[i][j] == 'V' ? (k == 1 || k == 3) : (k == 0 || k == 2);
                x = 2 * id[i][j] + x;
                if (mp[get<0>(to[i][j][k])][get<1>(to[i][j][k])] == '#') {
                    // cout << "ban x = " << x << endl;
                    ban[Find(x)] = true;
                    continue;
                }
                char c = mp[get<0>(to[i][j][k])][get<1>(to[i][j][k])];
                int t = id[get<0>(to[i][j][k])][get<1>(to[i][j][k])];
                int d = get<2>(to[i][j][k]);
                int y = c == 'V' ? (d == 1 || d == 3) : (d == 0 || d == 2);
                y = 2 * t + y;
                // cout << "c = " << c << " t = " << t << " d = " << d << endl;
                // cout << "x = " << x << " y = " << y << endl;
                Merge(x, y);
                Merge(x ^ 1, y ^ 1);
            }
            /* if (mp[i][j] == 'V') {
                if (mp[to[i][j][0].first][to[i][j][0].second] == '#') {
                    ban[id[i][j]] = true;
                } else {
                    char c = mp[to[i][j][0].first][to[i][j][0].second]
                    int t = id[to[i][j][0].first][to[i][j][0].second];
                    int d = Dir(make_pair(i, j), to[i][j][0].first);
                    if (mp == 
                }
                if (mp[to[i][j][2].first][to[i][j][2].second] == '#') {
                    ban[id[i][j]] = true;
                }
                if (mp[to[i][j][1].first][to[i][j][1].second] == '#') {
                    ban[id[i][j] + s] = true;
                }
                if (mp[to[i][j][3].first][to[i][j][3].second] == '#') {
                    ban[id[i][j] + s] = true;
                }
                if (mp[to[i][j][0].first][to[i][j][0].second] == 'V')
            }
            if (mp[i][j] == 'H') {

            } */
        }
    }
    for (int i = 0; i < s; ++i) {
        int a = Find(2 * i), b = Find(2 * i + 1);
        if (a == b) {
            // cout << "i = " << i << endl;
            cout << "-1\n";
            return 0;
        }
    }
    // cout << "here" << endl;
    int res = 0;
    vector<bool> used(s * 2);
    for (int i = 0; i < s; ++i) {
        if (used[Find(i * 2)] || used[Find(i * 2 + 1)]) continue;
        int a = Find(i * 2), b = Find(i * 2 + 1);
        // cout << "i = " << i << " a = " << a << " b = " << b << endl;
        if (ban[a] && ban[b]) {
            cout << "-1\n";
            return 0;
        }
        if (ban[a]) res += sz[b];
        else if (ban[b]) res += sz[a];
        else res += min(sz[a], sz[b]);
        used[a] = true;
        used[b] = true;
    }
    cout << res << "\n";
}
