#include <bits/stdc++.h>
using namespace std;

long long dp[10][100];

int main() {
    for (int i = 1; i <= 60; ++i) dp[1][i] = 2 * i;
    for (int i = 2; i <= 7; ++i) {
        dp[i][1] = 2;
        for (int j = 2; j <= 60; ++j) dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1];
    }
    int x, y;
    while (cin >> x >> y) {
        if (x == 0 && y == 0) break;
        cout << dp[x][y] << endl;
    }
}
