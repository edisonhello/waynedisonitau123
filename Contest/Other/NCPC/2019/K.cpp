#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5;
int c[maxn], dp[maxn][maxn];
bool v[maxn][maxn];

int dfs(int l, int r) {
    if (v[l][r]) return dp[l][r];
    if (l == r) return c[l];
    v[l][r] = true;
    dp[l][r] = max(c[l] - dfs(l + 1, r), c[r] - dfs(l, r - 1));
    return dp[l][r];
}

int main() {
    int k; scanf("%d", &k);
    while (k--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &c[i]);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dp[i][j] = 1e9;
                v[i][j] = false;
            }
        }
        printf("%d\n", dfs(0, n - 1));
    }
}
