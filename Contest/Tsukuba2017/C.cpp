#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], b[maxn];

int main() {
    int n, t; scanf("%d%d", &n, &t);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        if (i) b[i] = max(b[i], b[i - 1]);
    }
    long long p = 0;
    for (int i = 0; i < n; ++i) {
        int d = 31, k = 0;
        while (d--) {
            int r = k + (1 << d);
            if (r > t) continue;
            if (p + a[i] + (r - 1) * 1ll * b[i] <= t) k = r;
        } 
        printf("%d\n", k + 1);
        p += a[i];
    }
}
