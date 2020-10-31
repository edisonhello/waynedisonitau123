#include <bits/stdc++.h>
using namespace std;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int GetDice(int dice, int dir) {
    auto Bind = [] (vector<int> v) {
        int r = 0;
        for (int i = 0; i < 6; ++i) r |= v[i] << i;
        return r;
    };

    vector<int> v;
    for (int i = 0; i < 6; ++i) v.push_back(dice >> i & 1);

    if (dir == 0) {
        return Bind(vector<int>{v[4], v[2], v[0], v[3], v[1], v[5]});
    } else if (dir == 1) {
        return Bind(vector<int>{v[3], v[5], v[2], v[1], v[4], v[0]});
    } else if (dir == 2) {
        return Bind(vector<int>{v[2], v[4], v[1], v[3], v[0], v[5]});
    } else {
        return Bind(vector<int>{v[5], v[3], v[2], v[0], v[4], v[1]});
    }
}

int main() {
    while (true) {
        vector<string> mp;
        {
            string s;
            while (getline(cin, s)) {
                if (s == "") break;
                mp.push_back(s); 
            }
            if (mp.empty()) break;
        }
        int n = mp.size(), m = mp[0].size();

        map<pair<int, int>, int> id;
        int nn = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == '#') continue;

                // cerr << "i j " << i << ' ' << j << " get " << nn << endl;
                id[make_pair(i, j)] = nn++;
            }
        }

        vector<vector<pair<int, int>>> g(nn);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == '#') continue;
                int z = id[make_pair(i, j)];
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (mp[nx][ny] == '#') continue;
                    int zz = id[make_pair(nx, ny)];
                    g[z].emplace_back(zz, d);
                    // cerr << "connect " << z << " with " << zz << " pos dir = " << d << endl;
                }
            }
        }

        int s = -1, t = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == 'C')
                    s = id[make_pair(i, j)];
                else if (mp[i][j] == 'G') 
                    t = id[make_pair(i, j)];
            }
        }

        int state = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mp[i][j] == 'P')
                    state |= 1 << id[make_pair(i, j)];
            }
        }

        unordered_set<int> vis;

        queue<tuple<int, int, int, int>> q;
        q.emplace(state, 0, s, 0);
        bool answer = 0;

        while (q.size()) {
            int state, dice, at, step;
            tie(state, dice, at, step) = q.front(); q.pop();
            // cerr << "state = " << bitset<9>(state) << " dice = " << (bitset<6>(dice)) << " at = " << at << " step " << step << endl;
            // if (at == t && dice == 0b111111) {
            //     cout << step << '\n';
            //     answer = 1;
            //     break;
            // }

            // if (at != s && at != t) {
                if ((dice >> 1 & 1) ^ (state >> at & 1)) {
                    dice ^= 1 << 1;
                    state ^= 1 << at;
                }
            // }

            if (at == t && dice == 0b111111) {
                cout << step << '\n';
                answer = 1;
                break;
            }

            for (auto &e : g[at]) {
                int to, dir;
                tie(to, dir) = e;
                int ndice = GetDice(dice, dir);

                int nencode = state | (ndice << 20) | (to << 26);
                if (vis.count(nencode)) continue;
                vis.insert(nencode);

                // cerr << "   to state = " << bitset<9>(state) << " dice = " << (bitset<6>(ndice)) << " to = " << to << endl;

                q.emplace(state, ndice, to, step + 1);
            }
        }

        if (!answer) {
            cout << -1 << '\n';
        }
    }
    return 0;
}
