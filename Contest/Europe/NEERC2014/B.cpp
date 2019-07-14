#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e5 + 5;
int a[maxn], b[maxn], g[maxn];
double ans[maxn];
 
int main() {
#ifdef ONLINE_JUDGE
    freopen("burrito.in", "r", stdin);
    freopen("burrito.out", "w", stdout);
#endif
 
    int n, x, y; scanf("%d%d%d", &n, &x, &y);
    for (int i = 0; i < n; ++i) scanf("%d%d%d", &g[i], &a[i], &b[i]);
 
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    sort(v.begin(), v.end(), [&](int i, int j) {
        return a[i] * b[j] < a[j] * b[i];
    });
 
    double bsum = 0, asum = 0;
    for (int i = 0; i < n; ++i) {
        asum += a[i] * g[i];
        bsum += b[i] * g[i];
        ans[i] = g[i];
    }
 
    // printf("asum = %.20lf bsum = %.20lf\n", asum, bsum);
 
    for (int i = 0; i < n && bsum > y + 1e-9; ++i) {
        int j = v[i];
        // printf("j = %d bsum = %.20lf diff = %.20lf\n", j, bsum, bsum - y);
        if ((bsum - y) > b[j] * g[j]) {
            bsum -= g[j] * b[j];
            asum -= g[j] * a[j];
            ans[j] = 0.0;
        } else {
            double t = (bsum - y) / b[j];
            asum -= t * a[j];
            bsum -= t * b[j];
            assert(bsum <= y || fabs(bsum - y) < 1e-9);
            ans[j] -= t;
            break;
        }
    }
 
    if (bsum > y) {
        puts("-1 -1");
        return 0;
    }
 
    if (asum < x - 1e-9) {
        puts("-1 -1");
        return 0;
    }
 
    printf("%.20lf %.20lf\n", asum, bsum);
    for (int i = 0; i < n; ++i) printf("%.20lf ", ans[i]);
    puts("");
    return 0;
}
