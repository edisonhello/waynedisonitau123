#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000009;

vector<int> cs;
int idmap[333];

int to[33][33][33][2][2][2][2];

void add(int &x, int y) {
    x = (x + y >= mod ? x + y - mod : x + y);
}

void init() {
    cs.push_back('a' - 1);
    for (int i = 'a'; i <= 'z'; ++i) cs.push_back(i);
    cs.push_back('?');
    int m = cs.size();
    for (int i = 0; i < m; ++i) idmap[cs[i]] = i;
    // for (int i = 0; i < m; ++i) cerr << "map " << char(cs[i]) << " to " << i << endl;

    for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < m; ++k) {
        for (int y = 0; y < 2; ++y) for (int z = 0; z < 2; ++z) {
            for (int ii = (cs[i] == '?' ? 1 : i); ii < (cs[i] == '?' ? m - 1 : i + 1); ++ii) 
                for (int jj = (cs[j] == '?' ? 1 : j); jj < (cs[j] == '?' ? m - 1 : j + 1); ++jj) 
                    for (int kk = (cs[k] == '?' ? 1 : k); kk < (cs[k] == '?' ? m - 1 : k + 1); ++kk) {
                        if (y == 1 && ii > jj) continue;
                        if (z == 1 && jj > kk) continue;
                        int ny = y, nz = z;
                        if (y == 1 && ii < jj) ny = 0;
                        if (z == 1 && jj < kk) nz = 0;
                        // fprintf(stderr, "ii = %d, jj = %d, kk = %d, add to[%d][%d][%d][%d][%d][%d][%d] by %d\n", ii, jj, kk, i, j, k, y, z, ny, nz, 1);
                        add(to[i][j][k][y][z][ny][nz], 1);
                    }
            // for (int ny = 0; ny < 2; ++ny) for (int nz = 0; nz < 2; ++nz) {
            //     fprintf(stderr, "to[%d][%d][%d][%d][%d][%d][%d] = %d\n", i, j, k, y, z, ny, nz, to[i][j][k][y][z][ny][nz]);
            // }
        }
    }
}

void solve() {
    string s[4];
    cin >> s[1] >> s[2] >> s[3];
    s[1] = " " + s[1];
    s[2] = " " + s[2];
    s[3] = " " + s[3];
    int n = max(max(s[1].size(), s[2].size()), s[3].size());
    while (s[0].size() < n) s[0] += char('a' - 1);
    while (s[1].size() < n) s[1] += char('a' - 1);
    while (s[2].size() < n) s[2] += char('a' - 1);
    while (s[3].size() < n) s[3] += char('a' - 1);

    vector<array<array<int, 2>, 2>> dp(n + 3);
    for (int i = 0; i < n + 3; ++i) dp[i][0][0] = dp[i][0][1] = dp[i][1][0] = dp[i][1][1] = 0;
    
    dp[0][1][1] = 1;
    for (int i = 1; i <= n; ++i) for (int y = 0; y < 2; ++y) for (int z = 0; z < 2; ++z) for (int ny = 0; ny < 2; ++ny) for (int nz = 0; nz < 2; ++nz) {
        add(dp[i][ny][nz], dp[i - 1][y][z] * 1ll * to[idmap[s[1][i]]][idmap[s[2][i]]][idmap[s[3][i]]][y][z][ny][nz] % mod);
        // fprintf(stderr, "%d %d %d\n", idmap[s[1][i]], idmap[s[2][i]], idmap[s[3][i]]);
        // fprintf(stderr, "dp[%d][%d][%d] = %d\n", i, y, z, dp[i][ny][nz]);
    }

    cout << dp[n][0][0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    // cerr << "b4 init" << endl;
    init();
    // cerr << "af init" << endl;
    int t; cin >> t; while (t--) solve();
}
