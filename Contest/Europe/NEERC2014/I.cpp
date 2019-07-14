#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 5;
int a[maxn], fw[maxn], dp[maxn];
 
int query(int p) {
    int res = 0;
    for (int i = p; i > 0; i -= i & -i)
        res = max(res, fw[i]);
    return res;
}
 
void add(int p, int v) {
    for (int i = p; i < maxn; i += i & -i)
        fw[i] = max(fw[i], v);
}
 
int main() {
#ifdef ONLINE_JUDGE
    freopen("improvements.in", "r", stdin);
    freopen("improvements.out", "w", stdout);
#endif
 
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
 
    for (int i = 0; i < n; ++i) {
        dp[i] = query(a[i]) + 1;
        add(a[i], dp[i]);
    }
 
    for (int i = 0; i < n; ++i) a[i] = n - a[i] + 1;
    memset(fw, 0, sizeof(fw));
 
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int d = query(a[i]) + 1;
        ans = max(ans, dp[i] + d - 1);
        add(a[i], d);
    }
 
    printf("%d\n", ans);
    return 0;
}
