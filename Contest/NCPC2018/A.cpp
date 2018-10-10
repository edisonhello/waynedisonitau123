#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const long long inf = 1e15;
long long dp[maxn];
int a[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
    int n; scanf("%d", &n);
    for (int i = 0; i <= n; ++i) dp[i] = -inf;
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    long long pmax = -inf;
    int j = 1;
    for (int i = 1; i <= n; ++i) {
        while (i - j > 2) pmax = max(pmax, dp[j]), ++j;
        dp[i] = max(pmax + a[i], 1ll * a[i]);
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[i]);
    printf("%lld\n", ans);
}}
