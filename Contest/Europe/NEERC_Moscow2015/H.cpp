#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e5 + 5;
const int magic = 1024;
int a[maxn];
long long dp[2][magic + 1];
 
int hex(char *s) {
    int a = -1, b = -1;
    if (s[0] >= '0' && s[0] <= '9') a = s[0] - '0';
    else a = s[0] - 'A' + 10;
    if (s[1] >= '0' && s[1] <= '9') b = s[1] - '0';
    else b = s[1] - 'A' + 10;
    return a << 4 | b;
}
 
int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        char s[10]; scanf("%s", s);
        a[i] = hex(s);
    }
 
    for (int i = 1; i <= magic; ++i) dp[0][i] = -1e18;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= magic; ++j) {
            dp[i & 1][j] = -1e18;
            if (i - j - 1 >= 0) dp[i & 1][j] = dp[i & 1 ^ 1][j] + ((i - j - 1) ^ a[i]);
            if (j > 0) {
                dp[i & 1][j] = max(dp[i & 1][j], dp[i & 1 ^ 1][j - 1]);
            }
        }
    }
 
    long long ans = -1e18;
    for (int i = 0; i <= magic; ++i) ans = max(ans, dp[n & 1][i]);
    printf("%lld\n", ans);
    return 0;
}
