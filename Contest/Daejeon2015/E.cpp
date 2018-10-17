#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        sort(a, a + n);
        if (n == 2) {
            printf("%d\n", a[1] - a[0] + a[1] - a[0]);
            continue;
        }
        int ans = 0;
        for (int i = 0; i + 2 < n; ++i) {
            ans = max(ans, a[i + 2] - a[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
