#include <bits/stdc++.h>
using namespace std;

// vector<vector<int>> next(vector<vector<int>> v) {
//     int n = v.size(), m = v[0].size();
//     vector<vector<int>> vv(n, vector<int>(m));
//     for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
//         int k = 0;
//         for (int ii = 0; ii <= i; ++ii) for (int jj = 0; jj <= j; ++jj) {
//             k += v[ii][jj];
//         }
//         vv[i][j] = k & 1;
//     }
//     return vv;
// }
// 
// void print(int gen, vector<vector<int>> v) {
//     cout << "gen = " << gen << " v = " << endl;
//     for (auto &vv : v) {
//         for (int i : vv) cout << i;
//         cout << endl;
//     }
// }
// 
// int main() {
//     int n, m; cin >> n >> m;
//     vector<vector<int>> v(n, vector<int>(m));
//     for (int i = 0; i < n; ++i) {
//         string s; cin >> s;
//         for (int j = 0; j < m; ++j) v[i][j] = s[j] - '0';
//     }
// 
//     int gen = 1;
//     auto vv = next(v);
// 
//     print(gen, vv);
// 
//     while (vv != v) {
//         vv = next(vv);
//         ++gen;
//         print(gen, vv);
//     }
// }

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        for (int j = 1; j <= m; ++j) {
            a[i][j] = s[j - 1] - '0';
        }
    }

    vector<vector<bitset<22>>> dp(n + 2, vector<bitset<22>>(m + 2, bitset<22>(0)));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) for (int k = 0; k <= 20; ++k) {
        dp[i][j][k] = a[i][j];
        if (i > (1 << k)) { if (dp[i - (1 << k)][j][k]) dp[i][j].flip(k); }
        if (j > (1 << k)) { if (dp[i][j - (1 << k)][k]) dp[i][j].flip(k); }
        if (i > (1 << k) && j > (1 << k)) { if (dp[i - (1 << k)][j - (1 << k)][k]) dp[i][j].flip(k); }
    }

    vector<vector<int>> dp2(n + 2, vector<int>(m + 2, 0));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        dp2[i][j] = max(dp2[i - 1][j], dp2[i][j - 1]);
        if ((dp[i][j][dp2[i][j]] ^ a[i][j]) == 1) ++dp2[i][j];
    }

    cout << (1 << dp2[n][m]) << endl;
}
