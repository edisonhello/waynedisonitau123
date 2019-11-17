#include <bits/stdc++.h>
using namespace std;

const int kN = 1000 + 5;
const int kC = (1 << 13) + 5;
bool dp[kN][kC], tk[kN][kC];
int a[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        reverse(a + 1, a + n + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < kC; ++j)
                dp[i][j] = false;
        }
        dp[0][0] = true;
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < kC; ++j) {
                int k = sum - j;
                if (k < 0) continue;
                if (!dp[i - 1][j]) continue;
                if (j % a[i] == 0) {
                    dp[i][j + a[i]] = true;
                    tk[i][j + a[i]] = true;
                }
                if (k % a[i] == 0) {
                    dp[i][j] = true;
                    tk[i][j] = false;
                }
            }
            sum += a[i];
        }
        if (__builtin_popcount(sum) != 1) {
            puts("no");
            continue;
        }
        bool ok = false;
        for (int i = 1; i < kC; i <<= 1) {
            if (dp[n][i]) {
                ok = true;
                int v = i;
                for (int j = n; j > 0; --j) {
                    if (tk[j][v]) {
                        printf("r");
                        v -= a[j];
                    } else {
                        printf("l");
                    }
                }
                puts("");
                break;
            }
        }
        if (!ok) puts("no");
    }
}
