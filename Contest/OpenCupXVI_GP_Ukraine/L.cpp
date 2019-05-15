#include <bits/stdc++.h>
using namespace std;

const int maxn = 300 + 5;
const int maxm = 40 + 5;

int x[maxm], y[maxm], pos[maxn][3];
int cnt[maxm][maxm][7];
int inside[maxm][maxm][maxm];
double w[maxm][maxm];
double d[maxm][maxm][1 << 6];

double dist(int i, int j) {
    return hypot(x[i] - x[j], y[i] - y[j]);
}

int cross(int x, int y, int a, int b) {
    return x * b - y * a;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> pos[i][0] >> pos[i][1];
    for (int i = 1; i <= n; ++i) cin >> pos[i][2];
    for (int i = 1; i <= m; ++i) cin >> x[i] >> y[i];
    // for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) {
    //     for (int k = 1; k <= n; ++k) {
    //         if (cross(x[i], y[i], pos[k][0], pos[k][1]) >= 0
    //             && cross(x[j], y[j], pos[k][0], pos[k][1]) <= 0
    //             && cross(pos[k][0] - x[j], pos[k][1] - y[j], -x[j], -y[j]) >= 0) ++cnt[i][j][pos[k][2]];
    //         if (cross(x[i], y[i], pos[k][0], pos[k][1]) <= 0
    //             && cross(x[j], y[j], pos[k][0], pos[k][1]) >= 0
    //             && cross(pos[k][0] - x[j], pos[k][1] - y[j], -x[j], -y[j]) <= 0) --cnt[i][j][pos[k][2]];
    //     }
    //     for (int z = 1; z <= k; ++z) cout << "cnt " << i << " " << j << " " << k << " = " << cnt[i][j][k] << endl;
    // }
    // for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= m; ++k) {
    //     for (int z = 1; z <= 6; ++z) if (cnt[i][j][z] + cnt[j][k][z] + cnt[k][i][z] > 0) inside[i][j][k] |= 1 << (z - 1);
    //     cerr << "inside " << i << " " << j << " " << k << " = " << inside[i][j][k] << endl;
    // }
    for (int i = 1; i <= m; ++i) for (int j = 1; j <= m; ++j) for (int k = 1; k <= m; ++k) {
        int area = abs(cross(x[k] - x[i], y[k] - y[i], x[j] - x[i], y[j] - y[i]));
        if (area == 0) continue;
        for (int p = 1; p <= n; ++p) {
            int area1 = abs(cross(pos[p][0] - x[i], pos[p][1] - y[i], pos[p][0] - x[j], pos[p][1] - y[j]));
            int area2 = abs(cross(pos[p][0] - x[i], pos[p][1] - y[i], pos[p][0] - x[k], pos[p][1] - y[k]));
            int area3 = abs(cross(pos[p][0] - x[j], pos[p][1] - y[j], pos[p][0] - x[k], pos[p][1] - y[k]));
            if (area == area1 + area2 + area3) inside[i][j][k] |= 1 << (pos[p][2] - 1);
        }
        // cerr << "inside " << i << " " << j << " " << k << " = " << inside[i][j][k] << endl;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j)
            w[i][j] = dist(i, j);
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            d[i][j][0] = w[i][j];
            for (int p = 1; p < (1 << k); ++p)
                d[i][j][p] = 1e9;
        }
    }

    for (int p = 1; p <= m; ++p) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                for (int x = 0; x < (1 << k); ++x) {
                    for (int y = 0; y < (1 << k); ++y)
                        d[i][j][x | y | inside[i][p][j]] = min(d[i][j][x | y | inside[i][p][j]], d[i][p][x] + d[p][j][y]);
                }
            }
        }
    }
    double ans = 1e9;
    for (int i = 1; i <= m; ++i)
        ans = min(ans, d[i][i][(1 << k) - 1]);

    if (ans > 5e8) 
        cout << "-1" << endl;
    else
        cout << fixed << setprecision(20) << ans << endl;
}
