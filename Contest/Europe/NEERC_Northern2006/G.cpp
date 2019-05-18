#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int deg[maxn];

int calc(int n, int d) {
    if (n <= d) return 0;
    return n / d + calc(n / d + n % d, d);
}

int main() {
    int n, d; scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i) {
        int f; scanf("%d", &f);
        ++deg[f];
    }
    long long ans = 0;
    for (int i = 0; i <= n; ++i) ans += calc(deg[i], d);
    printf("%lld\n", ans);
}
