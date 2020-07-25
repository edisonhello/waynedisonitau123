#include <bits/stdc++.h>
using namespace std;

string mp[505];
int ans[505][505];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> mp[i];
        mp[i] = " " + mp[i];
    }

    auto Dist = [&] (int i, int j) -> int {
        return min(min(min(i, j), n + 1 - i), n + 1 - j);
    };

    auto Inside = [&] (int i, int j) -> bool {
        return i >= 1 && j >= 1 && i <= n && j <= n;
    };
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mp[i][j] == '.') ans[i][j] = Dist(i, j);
        }
    }
    
    for (int s = 2; s <= n; ++s) {
        queue<tuple<int, int, int>> q;
        vector<vector<bool>> vis(505, vector<bool>(505, 0));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (ans[i][j] == s) {
                    q.emplace(i, j, s - 1);
                    vis[i][j] = 1;
                }
            }
        }

        while (q.size()) {
            int x, y, t; tie(x, y, t) = q.front(); q.pop();
            ans[x][y] = max(ans[x][y], s);
            --t;
            if (t < 0) continue;
            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d], ny = y + dy[d];
                if (Inside(nx, ny) && mp[nx][ny] != '#' && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    q.emplace(nx, ny, t);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
}

