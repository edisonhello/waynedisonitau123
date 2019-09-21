#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int d[maxn][maxn];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int main() {
    int r, c, n; cin >> r >> c >> n;
    queue<pair<int, int>> q;
    memset(d, -1, sizeof(d));
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        q.emplace(x, y);
        d[x][y] = 0;
    }
    while (!q.empty()) {
        int x, y;
        tie(x, y) = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx >= 1 && tx <= r && ty >= 1 && ty <= c) {
                if (d[tx][ty] == -1) {
                    d[tx][ty] = d[x][y] + 1;
                    q.emplace(tx, ty);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j)
            ans = max(ans, d[i][j]);
    }
    printf("%d\n", ans + 1);
}


