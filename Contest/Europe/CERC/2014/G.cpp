#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
const int kMod = 1'000'000'000 + 87;
const int kMult = 7122;
int h[kN], pw[kN], dp[kN];
char s[kN];

int main() {
    int t; scanf("%d", &t);
    pw[0] = 1;
    for (int i = 1; i < kN; ++i) pw[i] = 1LL * pw[i - 1] * kMult % kMod;

    auto Query = [&](int l, int r) {
        return (h[r] + kMod - 1LL * h[l - 1] * pw[r - l + 1] % kMod) % kMod;
    };

    while (t--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) h[i] = (1LL * h[i - 1] * kMult + s[i]) % kMod;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;
            if (i % 2 == 0 && Query(1, i / 2) == Query(i / 2 + 1, i))
                dp[i] = min(dp[i], dp[i / 2] + 1);
            printf("dp[%d] = %d\n", i, dp[i]);
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
