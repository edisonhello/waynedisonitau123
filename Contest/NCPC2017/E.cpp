#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
int a[maxn], r[maxn];

int main() {
    int n, m; 
    while (scanf("%d %d", &n, &m) == 2) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < n; ++i) scanf("%d", &r[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        bitset<100005> dp;
        dp[0] = 1;
        for (int i = 0; i < n; ++i) {
            int k = 0;
            while (a[i]) {
                int g = -1;
                if (a[i] >= (1 << k)) g = (1 << k);
                else g = a[i];
                dp |= dp << (r[i] * g);
                a[i] -= g;
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i) {
            if (dp[i]) ++ans;
        }
        printf("%d\n", ans);
    }
}

