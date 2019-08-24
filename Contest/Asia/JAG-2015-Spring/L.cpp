#include <bits/stdc++.h>
using namespace std;

const int maxn = 20 + 5;
int dp[maxn][maxn][maxn][maxn];
bool v[maxn][maxn][maxn][maxn];
bool uu[100000];
string s[maxn];

int mex(vector<int> v) {
    for (int u : v) uu[u] = true;
    int res = 0;
    while (uu[res]) ++res;
    for (int u : v) uu[u] = false;
    return res;
}

int dfs(int u, int d, int l, int r) {
    if (u > d || l > r) return 0;
    if (u == d && l == r) {
        if (s[u][l] == 'X') return 0;
        else return 1;
    }
    if (v[u][d][l][r]) return dp[u][d][l][r];
    vector<int> z;
    for (int i = u; i <= d; ++i) {
        for (int j = l; j <= r; ++j) {
            if (s[i][j] == '.') {
                z.push_back(dfs(u, i - 1, l, j - 1) ^ dfs(u, i - 1, j + 1, r) ^ dfs(i + 1, d, l, j - 1) ^ dfs(i + 1, d, j + 1, r));
            }
        }
    }
    v[u][d][l][r] = true;
    dp[u][d][l][r] = mex(z);
    return dp[u][d][l][r];
}

int main() {
    int h, w; cin >> h >> w;
    for (int i = 0; i < h; ++i) cin >> s[i];

    cout << (dfs(0, h - 1, 0, w - 1) ? "First" : "Second") << endl;
}
