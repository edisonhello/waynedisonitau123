#include <bits/stdc++.h>
using namespace std;

struct pp {
    int a, c, s;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<pp> ps;
    for (int i = 0; i < n; ++i) {
        pp p;
        cin >> p.a >> p.c >> p.s;
        ps.push_back(p);
    }
    sort(ps.begin(), ps.end(), [&] (const pp &a, const pp &b) -> bool {
        if (a.c == b.c) {
            if (a.a == 1) return 1;
            if (b.a == 1) return 0;
            if (a.a == 3) return 1;
            if (b.a == 3) return 0;
            return 0;
        }
        return a.c > b.c;
    });
    vector<vector<vector<int>>> dp(4, vector<vector<int>>(k + 5, vector<int>(k + 5, 1000000000)));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        // cerr << "new person" << endl;
        pp &p = ps[i - 1];
        // cerr << "p : " << p.a << " " << p.c << " " << p.s << endl;
        for (int j = 0; j <= k; ++j) for (int jj = 0; jj <= k; ++jj) dp[i & 1][j][jj] = dp[(i - 1) & 1][j][jj];
        if (p.a & 2) {
            // cerr << "apply assis" << endl;
            for (int j = 0; j < k; ++j) for (int jj = 1; jj <= k; ++jj) {
                dp[i & 1][j + 1][jj - 1] = min(dp[i & 1][j + 1][jj - 1], dp[(i - 1) & 1][j][jj] + p.s);
            }
        }
        if (p.a & 1) {
            // cerr << "apply boss" << endl;
            for (int j = 0; j < k; ++j) for (int jj = 0; jj < k; ++jj) {
                dp[i & 1][j][jj + 1] = min(dp[i & 1][j][jj + 1], dp[(i - 1) & 1][j][jj] + p.s);
            }
        } 
    }
    // cerr << dp[1][0][1] << " -> ";
    // cerr << dp[2][1][0] << " -> ";
    // cerr << dp[4][1][1] << " -> ";
    // cerr << dp[5][2][0] << "\n";
    cout << dp[n & 1][k][0] << endl;
}
