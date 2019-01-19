#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
long long sa[maxn], sb[maxn], sc[maxn], sd[maxn];
double dp1[maxn], dp2[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("braess.in", "r", stdin);
    freopen("braess.out", "w", stdout);
#endif
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a, b, c, d;
        scanf("%d%d%d%d", &b, &a, &d, &c);
        sa[i] = sa[i - 1] + a;
        sb[i] = sb[i - 1] + b;
        sc[i] = sc[i - 1] + c;
        sd[i] = sd[i - 1] + d;
    }
    dp1[0] = 0; dp2[0] = 0;
    double all1 = 0.0, all2 = 0.0;
    for (int i = 1; i <= n; ++i) {
        long long a = sa[i] - sa[i - 1];
        long long b = sb[i] - sb[i - 1];
        long long c = sc[i] - sc[i - 1];
        long long d = sd[i] - sd[i - 1];
        double t = 0.0;
        if (a >= c + d) t = c + d;
        else if (c >= a + b) t = a + b;
        else t = a + b * 1.0 * (c + d - a) / (b + d);
        all1 += t;
    }
    long long a = sa[n];
    long long b = sb[n];
    long long c = sc[n];
    long long d = sd[n];
    double t = 0.0;
    if (a >= c + d) t = c + d;
    else if (c >= a + b) t = a + b;
    else t = a + b * 1.0 * (c + d - a) / (b + d);
    all2 = t;
    for (int i = 1; i <= n; ++i) {
        dp1[i] = +1e18;
        dp2[i] = -1e18;
        for (int j = 0; j < i; ++j) {
            long long a = sa[i] - sa[j];
            long long b = sb[i] - sb[j];
            long long c = sc[i] - sc[j];
            long long d = sd[i] - sd[j];
            double t = 0.0;
            if (a >= c + d) t = c + d;
            else if (c >= a + b) t = a + b;
            else t = a + b * 1.0 * (c + d - a) / (b + d);
            dp1[i] = min(dp1[i], dp1[j] + t);
            dp2[i] = max(dp2[i], dp2[j] + t);
        }
    }
    printf("%.20lf\n", all2);
    printf("%.20lf\n", all1);
    printf("%.20lf\n", dp1[n]);
    printf("%.20lf\n", dp2[n]);
}
