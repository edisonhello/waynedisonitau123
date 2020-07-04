#include <bits/stdc++.h>
using namespace std;

string mp[2005];
string af[2005];
bool vis[2005][2005];
bool moved[2005][2005];
int walked[2005][2005];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> mp[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) af[i] += '.';
    }

    auto Inside = [&] (int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    vector<pair<int, int>> conn;
    auto Dfs = [&] (auto self, int x, int y) -> void {
        moved[x][y] = 1;
        conn.emplace_back(x, y);
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!Inside(nx, ny)) continue;
            if (moved[nx][ny]) continue;
            if (mp[nx][ny] != '#') continue;
            self(self, nx, ny);
        }
    };

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    for (int j = 0; j < m; ++j) {
        walked[n - 1][j] = (mp[n - 1][j] == '.');
        pq.emplace(walked[n - 1][j], make_pair(n - 1, j));
        vis[n - 1][j] = 1;
    }

    while (pq.size()) {
        pair<int, int> now = pq.top().second; pq.pop();
        int x, y; tie(x, y) = now;
        // cerr << "now x y " << x << ' ' << y << endl;
        if (mp[x][y] == '#' && !moved[x][y]) {
            // cerr << "catched walked = " << walked[x][y] << endl;
            conn.clear();
            Dfs(Dfs, x, y);

            for (auto &pp : conn) {
                af[pp.first + walked[x][y]][pp.second] = '#';
                vis[pp.first][pp.second] = 1;
                
                if (pp.first && !vis[pp.first - 1][pp.second]) {
                    vis[pp.first - 1][pp.second] = 1;
                    walked[pp.first - 1][pp.second] = walked[x][y] + (mp[pp.first - 1][pp.second] == '.');
                    pq.emplace(walked[pp.first - 1][pp.second], make_pair(pp.first - 1, pp.second));
                }
            }
        } else {
            if (x && !vis[x - 1][y]) {
                vis[x - 1][y] = 1;
                walked[x - 1][y] = walked[x][y] + (mp[x - 1][y] == '.');
                pq.emplace(walked[x - 1][y], make_pair(x - 1, y));
            }
        }

        // cerr << "vis: " << endl;
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) cerr << vis[i][j];
        //     cerr << endl;
        // }
        // cerr << "walked: " << endl;
        // for (int i = 0; i < n; ++i) {
        //     for (int j = 0; j < m; ++j) cerr << walked[i][j];
        //     cerr << endl;
        // }

    }

    for (int i = 0; i < n; ++i) cout << af[i] << '\n';

    
}

