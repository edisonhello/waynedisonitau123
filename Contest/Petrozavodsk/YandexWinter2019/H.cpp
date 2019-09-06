#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5;
int a[maxn][maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) scanf("%d", &a[i][j]);
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = 1e9;
        for (int j = 0; j < n; ++j) x = min(x, a[i][j]);
        ans = max(ans, x);
    }
    printf("%d\n", ans);
    return 0;
}
