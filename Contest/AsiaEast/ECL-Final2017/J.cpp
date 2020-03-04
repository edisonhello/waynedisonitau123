#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int v[maxn];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &v[i]);

        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int a = i - 2 >= 0 ? v[i - 2] : 0;
            int b = i - 1 >= 0 ? v[i - 1] : 0;
            int d = i + 1 < n  ? v[i + 1] : 0;
            int e = i + 2 < n  ? v[i + 2] : 0;
            int k = min(a, b) + min(d, e) + min(b - min(a, b), d - min(d, e));
            ok &= k >= v[i];
        }
        if (ok) printf("Case #%d: Yes\n", tc);
        else printf("Case #%d: No\n", tc);
    }
}
