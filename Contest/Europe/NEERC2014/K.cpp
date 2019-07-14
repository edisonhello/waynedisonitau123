#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1000 + 5;
int a[maxn], b[maxn];
 
int main() {
#ifdef ONLINE_JUDGE
    freopen("knockout.in", "r", stdin);
    freopen("knockout.out", "w", stdout);
#endif
 
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);
    for (int i = 0; i < m; ++i) {
        int l, r, t; scanf("%d%d%d", &l, &r, &t);
        int ans = 0;
        for (int j = 0; j < n; ++j) {
            int dd = abs(a[j] - b[j]) * 2;
            int td = t % dd;
            int dest = -1;
            if (td <= abs(a[j] - b[j])) {
                if (a[j] < b[j]) dest = a[j] + td;
                else dest = a[j] - td;
            } else {
                td -= abs(a[j] - b[j]);
                if (a[j] < b[j]) dest = b[j] - td;
                else dest = b[j] + td;
            }
 
            if (dest >= l && dest <= r) ++ans;
        }
        printf("%d\n", ans);
    }
}
