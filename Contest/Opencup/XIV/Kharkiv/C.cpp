#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
int fa[maxn];

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < 2 * (n + m); ++i) fa[i] = i;
    for (int i = 0; i < k; ++i) {
        int x, y, c; scanf("%d%d%d", &x, &y, &c);
        --x, --y;
        if (x % 2 == 0 || y % 2 == 0) c ^= 1;
        y += n;
        if (c) {
            fa[find(2 * x)] = find(2 * y + 1);
            fa[find(2 * y)] = find(2 * x + 1);
        } else {
            fa[find(2 * x)] = find(2 * y);
            fa[find(2 * x + 1)] = find(2 * y + 1);
        }
    }

    for (int i = 0; i < n + m; ++i) {
        if (find(2 * i) == find(2 * i + 1)) {
            puts("0");
            return 0;
        }
    }

    int comp = 0;
    for (int i = 0; i < 2 * (n + m); ++i) {
        if (find(i) == i) ++comp;
    }
    comp >>= 1;
    
    int ans = 1;
    for (int i = 0; i < comp - 1; ++i) ans = ans * 2 % mod;
    printf("%d\n", ans);
    return 0;
}
