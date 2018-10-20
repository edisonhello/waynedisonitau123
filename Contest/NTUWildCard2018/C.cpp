#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
vector<pair<int, int>> ed[maxn];
int fa[maxn], mrg;

int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    ++mrg;
    fa[x] = y;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        if (n == 0 && m == 0) break;
        for (int i = 0; i < maxn; ++i) ed[i].clear();
        for (int i = 0; i < m; ++i) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            --a, --b;
            ed[c].emplace_back(a, b);
        }
        for (int i = 0; i < n; ++i) fa[i] = i;
        mrg = 0;
        int ans = 1001;
        for (int i = 1; i <= 1000; ++i) {
            for (int j = 0; j < ed[i].size(); ++j) {
                int x, y; tie(x, y) = ed[i][j];
                merge(x, y);
            }
            int cc = n - mrg;
            if (cc <= n / 2) ans = min(ans, i);
        }
        printf("%d\n", ans);
    }
    return 0;
}
