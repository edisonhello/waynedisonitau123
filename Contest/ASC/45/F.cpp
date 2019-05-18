#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
    freopen("flights.in", "r", stdin);
    freopen("flights.out", "w", stdout);
#endif
    int n, m; 
    while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) return 0;
        vector<tuple<int, int, int>> edge;
        vector<int> to(n, -1);
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            if (x > y) swap(x, y);
            if (x == 0) {
                to[y] = i;
                continue;
            }
            edge.emplace_back(x, y, i);
        }
        vector<long long> deg(n, 0);
        vector<int> ans(m, 0);
        int j = 1;
        for (int i = 0; i < (int)edge.size(); ++i) {
            int x, y, z; tie(x, y, z) = edge[i];
            deg[x] += j;
            deg[y] += j;
            ans[z] = j++;
        }
        vector<int> v(n - 1);
        iota(v.begin(), v.end(), 1);
        sort(v.begin(), v.end(), [&](int i, int j) { return deg[i] < deg[j]; });
        for (int i = 0; i < (int)v.size(); ++i) ans[to[v[i]]] = j++;
        puts("Yes");
        for (int i = 0; i < m; ++i) printf("%d ", ans[i]);
        puts("");
    }
}
