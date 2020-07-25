#include <bits/stdc++.h>
using namespace std;

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        long long x3, y3, x4, y4; cin >> x3 >> y3 >> x4 >> y4;

        vector<vector<int>> bruh(10, vector<int>(10, 0));
        vector<vector<int>> vis(10, vector<int>(10, 0));

        vector<long long> xs = {x1, x2, x3, x4};
        sort(xs.begin(), xs.end());
        vector<long long> ys = {y1, y2, y3, y4};
        sort(ys.begin(), ys.end());

        x1 = lower_bound(xs.begin(), xs.end(), x1) - xs.begin() + 2;
        x2 = lower_bound(xs.begin(), xs.end(), x2) - xs.begin() + 2;
        x3 = lower_bound(xs.begin(), xs.end(), x3) - xs.begin() + 2;
        x4 = lower_bound(xs.begin(), xs.end(), x4) - xs.begin() + 2;
        y1 = lower_bound(ys.begin(), ys.end(), y1) - ys.begin() + 2;
        y2 = lower_bound(ys.begin(), ys.end(), y2) - ys.begin() + 2;
        y3 = lower_bound(ys.begin(), ys.end(), y3) - ys.begin() + 2;
        y4 = lower_bound(ys.begin(), ys.end(), y4) - ys.begin() + 2;

        for (int i = x1; i < x2; ++i) {
            for (int j = y1; j < y2; ++j) bruh[i][j] += 1;
        }

        for (int i = x3; i < x4; ++i) {
            for (int j = y3; j < y4; ++j) bruh[i][j] += 2;
        }

        auto Dfs = [&] (auto self, int i, int j) -> void {
            vis[i][j] = 1;
            for (int d = 0; d < 4; ++d) {
                int ii = i + dx[d], jj = j + dy[d];
                if (ii >= 0 && ii < 10 && jj >= 0 && jj < 10 && bruh[ii][jj] == bruh[i][j] && !vis[ii][jj])
                    self(self, ii, jj);
            }
        };

        int c = 0;
        for (int i = 0; i < 10; ++i) for (int j = 0; j < 10; ++j) if (!vis[i][j])
            Dfs(Dfs, i, j), ++c;

        cout << c << '\n';
    }
}

