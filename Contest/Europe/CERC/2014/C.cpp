#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        bool ok = false;
        for (int k = 2; ; ++k) {
            if (k * (k + 1) / 2 > n) break;
            if (2 * n % k == 0) {
                int d = 2 * n / k;
                int x2 = d - (k - 1);
                if (x2 > 0 && x2 % 2 == 0) {
                    int x = x2 / 2;
                    printf("%d = %d", n, x);
                    x += 1;
                    for (int i = 1; i < k; ++i) printf(" + %d", x), x++;
                    ok = true;
                    puts("");
                    break;
                }
            }
        }
        if (!ok) puts("IMPOSSIBLE");
    }
}
