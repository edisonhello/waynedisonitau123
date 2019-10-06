#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
char s[maxn];
int pw[maxn], ans[maxn], fr[maxn][maxn];
bool dp[maxn][maxn];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    scanf("%s", s + 1);

    if (n == 1 && (s[1] == '?' || s[1] == '0')) {
        printf("0\n");
        return 0;
    }

    pw[0] = 1;
    for (int i = 1; i <= n; ++i)
        pw[i] = pw[i - 1] * 10 % k;

    dp[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        char c = s[n - i + 1];
        for (int j = 0; j < k; ++j) {
            for (int d = 0; d < 10; ++d) {
                if (i == n && d == 0) continue;
                if (c == '?' || (char)(d + '0') == c) {
                    if (dp[i - 1][(j + k - pw[i - 1] * d % k) % k]) {
                        dp[i][j] = true;
                        fr[i][j] = d;
                        break;
                    }
                }
            }
        }
    }

    if (!dp[n][0]) {
        printf("-1\n");
        return 0;
    }

    for (int i = n, s = 0; i >= 1; --i) {
        printf("%d", fr[i][s]);
        s = (s + k - pw[i - 1] * fr[i][s] % k) % k;
    }
}
