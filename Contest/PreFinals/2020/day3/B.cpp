#include <bits/stdc++.h>
using namespace std;

struct Hold {
    int x, y, w;

    Hold() = default;
    Hold(int x, int y, int w) : x(x), y(y), w(w) {}
};

int main() {
    int h, w, r, s;
    cin >> h >> w >> r >> s;
    vector<string> grid(h);
    for (int i = 0; i < h; ++i) {
        cin >> grid[i];
    }
    vector<Hold> holds;
    int sum = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (grid[i][j] >= '0' && grid[i][j] <= '9') {
                holds.emplace_back(i, j, grid[i][j] - '0');
                sum += grid[i][j] - '0';
            }
        }
    }
    int n = holds.size();
    vector<vector<int>> g(n);

    auto Dist = [&](const auto &a, const auto &b) {
        return 1LL * (a.x - b.x) * (a.x - b.x) + 1LL * (a.y - b.y) * (a.y - b.y);
    };

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (Dist(holds[i], holds[j]) <= r * r) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    int bot = -1, top = h + 1;
    for (int i = 0; i < n; ++i) {
        bot = max(bot, holds[i].x);
        top = min(top, holds[i].x);
    }
    int st = -1, ed = -1;
    for (int i = 0; i < n; ++i) {
        if (holds[i].x == bot) st = i;
        if (holds[i].x == top) ed = i;
    }
    constexpr double kInf = 1E9;
    constexpr double kEps = 1E-9;
    vector<vector<double>> dp(sum + 1, vector<double>(n, kInf));    
    dp[holds[st].w][st] = 0.0;
    for (int i = 0; i <= sum; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fabs(dp[i][j] - kInf) < kEps) continue;
            for (int u : g[j]) {
                if (i + holds[u].w <= sum) {
                    dp[i + holds[u].w][u] = min(dp[i + holds[u].w][u], dp[i][j] + sqrt(Dist(holds[j], holds[u])));
                }
            }
        }
    }
    double res = kInf;
    for (int i = 0; i <= min(s, sum); ++i) {
        res = min(res, dp[i][ed]);
    }
    if (fabs(res - kInf) < kEps) cout << -1 << "\n";
    else cout << fixed << setprecision(12) << res << "\n";
}

