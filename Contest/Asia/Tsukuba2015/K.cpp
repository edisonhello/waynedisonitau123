#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    int n; 
    char s[10];
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

    if (n % 2 == 0 && s[0] == 'B') {
        int ans = 2e9;
        for (int i = 0; i < n / 2; ++i) ans = min(ans, a[i + n / 2] - a[i]);
        printf("%d\n", ans);
        return 0;
    }
    if (n % 2 == 1 && s[0] == 'A') {
        int ans = 2e9;
        for (int i = 0; i < n / 2; ++i) ans = min(ans, a[i + n / 2 + 1] - a[i]);
        printf("%d\n", ans);
        return 0;
    }

    auto Check = [&](int z) {
        int ans = 0;
        for (int i = 0, j; i < n; i = j) {
            for (j = i; j < n && a[j] - a[i] <= z; ++j);
            ans += j - i - 1;
        }
        return ans >= n / 2;
    };

    int ans = 1e9 + 10;
    for (int d = 30; d >= 0; --d) {
        if (ans - (1 << d) >= 0 && Check(ans - (1 << d))) ans -= (1 << d);
    }
    printf("%d\n", ans);
    return 0;
}


