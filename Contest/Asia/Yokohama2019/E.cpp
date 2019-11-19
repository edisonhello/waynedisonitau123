#include <bits/stdc++.h>
using namespace std;

const int kN = 5000 + 5;
const int kMod = 1'000'000'000 + 7;
int dp1[kN][kN], dp2[kN][kN], pv[kN], a[kN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    a[n + 1] = n + 1;
    for (int i = 1; i <= n + 1; ++i) {
        int j = i - 1;
        while (j >= 1 && a[j + 1] > a[j]) --j;
        pv[i] = j + 1;
        printf("i = %d pv = %d\n", i, pv[i]);
    }
    dp1[0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= i + 1; ++k) {
            for (int j = max(pv[i] - 1, 1); j < i - 1; ++j) if (a[i + 1] > a[j]) (dp1[i][k] += dp2[j][i + 1 - k]) %= kMod;
            if (a[i + 1] > a[i - 1]) (dp1[i][k] += dp2[i - 1][i + 2 - k]) %= kMod;
            for (int j = pv[i] - 1; j < i - 1; ++j) if (a[i + 1] > a[j]) (dp2[i][k] += dp1[j][i + 1 - k]) %= kMod;
            if (a[i + 1] > a[i - 1]) (dp2[i][k] += dp1[i - 1][i + 2 - k]) %= kMod;
            printf("dp1[%d][%d] = %d\n", i, k, dp1[i][k]);
            printf("dp2[%d][%d] = %d\n", i, k, dp2[i][k]);
        } 
    }
    int ans = 0;
    for (int i = n - m + 1; i <= m + 1; ++i) {
        (ans += dp1[n][i]) %= kMod;
    }
    for (int i = n - m + 2; i <= m + 2; ++i) {
        (ans += dp2[n][i]) %= kMod;
    }
    printf("%d\n", (ans + ans) % kMod);
}
