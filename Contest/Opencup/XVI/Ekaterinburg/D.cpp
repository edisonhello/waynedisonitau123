#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
int dp[maxn], sum[maxn];

int main() {
    int n; scanf("%d", &n);
    dp[1] = 1;
    sum[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = (sum[i / 2] + 1) % mod;
        sum[i] = (sum[i - 1] + dp[i]) % mod;
    }
    printf("%d\n", dp[n]);
}
