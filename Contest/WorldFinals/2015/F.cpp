#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    for (int i = 0; i < r; ++i) cin >> grid[i];
    string s;
    cin >> s;
    s += '*';

    constexpr int dx[4] = {1, 0, -1, 0};
    constexpr int dy[4] = {0, 1, 0, -1};

    vector<vector<vector<pair<int, int>>>> nxt(r, vector<vector<pair<int, int>>>(c, vector<pair<int, int>>(4, make_pair(-1, -1))));

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            for (int k = 0; k < 4; ++k) {
                int x = i, y = j;
                while (x >= 0 && x < r && y >= 0 && y < c && grid[x][y] == grid[i][j]) {
                    x += dx[k];
                    y += dy[k];
                }
                if (x >= 0 && x < r && y >= 0 && y < c) nxt[i][j][k] = make_pair(x, y);
            }
        }
    }
    constexpr int kInf = 1'000'000'000;
    vector<vector<int>> dp(r, vector<int>(c, kInf));
    dp[0][0] = 0;
    for (int it = 0; it < s.size(); ++it) {
        priority_queue<pair<int, pair<int, int>>> pq;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (dp[i][j] != kInf) {
                    pq.emplace(-dp[i][j], make_pair(i, j));
                }
            }
        }
        vector<vector<bool>> vis(r, vector<bool>(c));
        vector<vector<int>> ndp = dp;
        while (!pq.empty()) {
            int x = pq.top().second.first;
            int y = pq.top().second.second;
            pq.pop();
            if (vis[x][y]) continue;
            vis[x][y] = true;
            for (int k = 0; k < 4; ++k) {
                if (nxt[x][y][k].first == -1) continue;
                int nx, ny;
                tie(nx, ny) = nxt[x][y][k];
                if (ndp[x][y] + 1 < ndp[nx][ny]) {
                    ndp[nx][ny] = ndp[x][y] + 1;
                    pq.emplace(-ndp[nx][ny], make_pair(nx, ny));
                }
            }
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (grid[i][j] == s[it]) {
                    ndp[i][j]++;
                } else {
                    ndp[i][j] = kInf;
                }
            }
        }
        dp = ndp;
    }
    int res = kInf;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            res = min(res, dp[i][j]);
        }
    }
    cout << res << "\n";
}

