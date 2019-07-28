#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int h[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("alpinism.in", "r", stdin);
    freopen("alpinism.out", "w", stdout);
#endif
    int k, n; scanf("%d%d", &k, &n);
    for (int i = 0; i < n; ++i) scanf("%d", &h[i]);
    h[n] = k;

    double need = h[0];

    for (int i = 1; i <= n; ++i) {
        int dist = h[i] - h[i - 1];
        need = max(need, dist + need / 2);
    }

    printf("%.20lf\n", need);
}
