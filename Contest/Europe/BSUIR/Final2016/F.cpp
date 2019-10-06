#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const long long inf = 1e18;
int a[maxn];
long long dp[maxn][2][2][2][2];
array<int, 4> fr[maxn][2][2][2][2];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);

    bool positive = true;
    for (int i = 1; i <= n; ++i) positive &= a[i] >= 0;

    if (positive) {
        printf("%lld\n", accumulate(a + 1, a + n + 1, 0ll));
        printf("1 2\n");
        return 0;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int p = 0; p < 2; ++p) {
                    for (int q = 0; q < 2; ++q)
                        dp[i][j][k][p][q] = -inf;
                }
            }
        }
    }
    dp[0][0][0][0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int s = 0; s < 2; ++s) {
                    if (s && dp[i - 1][j][k][s - 1][0] + a[i] > dp[i][j][k][s][1]) {
                        dp[i][j][k][s][1] = dp[i - 1][j][k][s - 1][0] + a[i];
                        fr[i][j][k][s][1] = {j, k, s - 1, 0};
                    }
                    if (dp[i - 1][j][k][s][1] + a[i] > dp[i][j][k][s][1]) {
                        dp[i][j][k][s][1] = dp[i - 1][j][k][s][1] + a[i];
                        fr[i][j][k][s][1] = {j, k, s, 1};
                    }
                    if (dp[i - 1][j][k][s][1] > dp[i][j][k][s][0]) {
                        dp[i][j][k][s][0] = dp[i - 1][j][k][s][1];
                        fr[i][j][k][s][0] = {j, k, s, 1};
                    }
                    if (dp[i - 1][j][k][s][0] > dp[i][j][k][s][0]) {
                        dp[i][j][k][s][0] = dp[i - 1][j][k][s][0];
                        fr[i][j][k][s][0] = {j, k, s, 0};
                    }
                    if (j == 1) {
                        if (s && dp[i - 1][j - 1][k][s - 1][0] > dp[i][j][k][s][1]) {
                            dp[i][j][k][s][1] = dp[i - 1][j - 1][k][s - 1][0];
                            fr[i][j][k][s][1] = {j - 1, k, s - 1, 0};
                        }
                        if (dp[i - 1][j - 1][k][s][1] > dp[i][j][k][s][1]) {
                            dp[i][j][k][s][1] = dp[i - 1][j - 1][k][s][1];
                            fr[i][j][k][s][1] = {j - 1, k, s, 1};
                        }
                    }
                    if (k == 1) {
                        if (dp[i - 1][j][k - 1][s][1] + a[i] > dp[i][j][k][s][0]) {
                            dp[i][j][k][s][0] = dp[i - 1][j][k - 1][s][1] + a[i];
                            fr[i][j][k][s][0] = {j, k - 1, s, 1};
                        }
                        if (dp[i - 1][j][k - 1][s][0] + a[i] > dp[i][j][k][s][0]) {
                            dp[i][j][k][s][0] = dp[i - 1][j][k - 1][s][0] + a[i];
                            fr[i][j][k][s][0] = {j, k - 1, s, 0};
                        }
                    }

                    // printf("dp[%d][%d][%d][%d][0] = %lld\n", i, j, k, s, dp[i][j][k][s][0]);
                    // printf("dp[%d][%d][%d][%d][1] = %lld\n", i, j, k, s, dp[i][j][k][s][1]);

                }
            }
        }
    }

    array<int, 4> pos = {1, 1, 1, 0};
    if (dp[n][1][1][1][1] > dp[n][1][1][1][0])
        pos = {1, 1, 1, 1};

    vector<int> swp;
    for (int i = n; i >= 1; --i) {
        array<int, 4> f = fr[i][pos[0]][pos[1]][pos[2]][pos[3]];

        if (f[0] < pos[0]) swp.push_back(i);
        if (f[1] < pos[1]) swp.push_back(i);

        pos = f;
    }
    printf("%lld\n", max(dp[n][1][1][1][0], dp[n][1][1][1][1]));

    assert((int)swp.size() == 2);
    assert(swp[0] != swp[1]);
    printf("%d %d\n", swp[0], swp[1]);
}
