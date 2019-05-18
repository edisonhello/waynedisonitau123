#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int iter = 10000;
const double pi = acos(-1);
int x[maxn], y[maxn];
double theta[maxn], len[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("tower.in", "r", stdin);
    freopen("tower.out", "w", stdout);
#endif
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
    for (int i = 0; i < n; ++i) theta[i] = atan2(y[i], x[i]);
    for (int i = 0; i < n; ++i) len[i] = hypot(x[i], y[i]);
    double dt = 2 * pi / k / iter;
    double t = 0.0;
    int j = 0;
    double ans = 1e9;
    while (j < iter) {
        double res = 0.0;
        for (int i = 0; i < n; ++i) {
            double th = theta[i] - t;
            // printf("th = %.5lf\n", th);
            if (th < -5e-2) th += 2 * pi;
            else if (th < 0) th = 0;
            else if (fabs(th) < 5e-2) th = 0;
            int fl = floor(th / (2 * pi / k));
            double rth = th - fl * 2 * pi / k;
            double oth = pi - rth - (pi / 2 - pi / k);
            double pth = pi / 2 - pi / k;
            // if (fabs(rth) < 1e-9) {
            //     printf("t = %.20lf\n", t);
            //     printf("%.20lf\n", len[i] / sin(pth) * sin(oth));
            // }
            //printf("rth = %.5lf\n", rth);
            //printf("length = %.5lf\n", len[i] / sin(pth) * sin(oth));
            //printf("oth = %.5lf\n", oth);
            //printf("pth = %.5lf\n", pth);
            res = max(res, len[i] / sin(pth) * sin(oth));
        }
        t += dt; 
        ans = min(ans, res);
        ++j;
    }
    printf("%.20lf\n", ans / (1 + 1e-10));
    return 0;
}
