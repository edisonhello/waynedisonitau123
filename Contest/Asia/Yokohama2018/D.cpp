#include <bits/stdc++.h>
using namespace std;

string s, t;

int dp[4050][4050];
int vi[4050][4050];
int fm[2][4050][2];

int dfs1(int i, int j) {
    if (i == s.size() - 1 && j == t.size() - 1) return 0;
    if (vi[i][j]) return dp[i][j];
    vi[i][j] = 1;
    return dp[i][j] = min(dfs1(fm[0][i][0], fm[1][j][0]), dfs1(fm[0][i][1], fm[1][j][1])) + 1;
}

void dfs(int i, int j) {
    if (i == s.size() - 1 && j == t.size() - 1) return;
    int p0 = dfs1(fm[0][i][0], fm[1][j][0]);
    int p1 = dfs1(fm[0][i][1], fm[1][j][1]);
    if (p0 <= p1) {
        cout << 0;
        dfs(fm[0][i][0], fm[1][j][0]);
    }
    else {
        cout << 1;
        dfs(fm[0][i][1], fm[1][j][1]);
    }
}


int main() {
    cin >> s >> t;
    for (char &c : s) c -= '0';
    for (char &c : t) c -= '0';

    int n = s.size(), m = t.size();

    s = " " + s + " ";
    t = " " + t + " ";


    for (int i = 0; i <= n; ++i) {
        int j;
        for (j = i + 1; s[j] == 1; ++j); fm[0][i][0] = j;
        for (j = i + 1; s[j] == 0; ++j); fm[0][i][1] = j;

        // cerr << "fm[0][" << i << "][0] = " << fm[0][i][0] << ", ";
        // cerr << "fm[0][" << i << "][1] = " << fm[0][i][1] << endl;
    }
    fm[0][n + 1][0] = fm[0][n + 1][1] = n + 1;

    for (int i = 0; i <= m; ++i) {
        int j;
        for (j = i + 1; t[j] == 1; ++j); fm[1][i][0] = j;
        for (j = i + 1; t[j] == 0; ++j); fm[1][i][1] = j;

        // cerr << "fm[1][" << i << "][0] = " << fm[1][i][0] << ", ";
        // cerr << "fm[1][" << i << "][1] = " << fm[1][i][1] << endl;
    }
    fm[1][m + 1][0] = fm[1][m + 1][1] = m + 1;

    dfs(0, 0);
}
