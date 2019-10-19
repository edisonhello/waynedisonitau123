#include <bits/stdc++.h>
using namespace std;

bool Prime(int x) {
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    int m; scanf("%d", &m);
    while (m--) {
        int n; scanf("%d", &n);
        int p = -1;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                p = i;
                break;
            }
        }
        if (p == -1) {
            printf("%d = %d * %d\n", n, 1, n);
            continue;
        }
        int q = n / p;
        if (!Prime(p) || !Prime(q)) {
            printf("%d = %d * %d\n", n, 1, n);
            continue;
        }
        long long x = sqrt(n);
        while (x * x > n) x--;
        while ((x + 1) * (x + 1) <= n) x++;
        bool ans = false;
        for (int i = 0; i < 2; ++i) {
            long long a = x - p;
            long long b = q - x;
            if (b - a - 1 >= 0 && b - a - 1 < x && 0 <= x - a * b && x - a * b < x) ans = true;
            --x;
        }
        if (ans) printf("%d = %d * %d\n", n, p, q);
        else printf("%d = %d * %d\n", n, 1, n);
    }
}
