#include <bits/stdc++.h>
using namespace std;

const int kN = 10'000'000 + 1;
int dp[kN];

int main() {
#ifdef ONLINE_JUDGE
    freopen("funny.in", "r", stdin);
    freopen("funny.out", "w", stdout);
#endif
    dp[1] = 0;
    for (int i = 1; i < kN; ++i) {
        for (int j = i + i; j < kN; j += i)
            dp[j] = max(dp[j], dp[i] + 1);
    }
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;
        printf("%d %d - ", n, m);
        if (dp[n] > dp[m]) puts("Vera");
        else puts("Harry");
    }
}
