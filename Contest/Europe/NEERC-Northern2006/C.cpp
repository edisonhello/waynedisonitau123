#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
double v[maxn], a[maxn], h[maxn], sh[maxn], x[maxn], d[maxn], t[maxn];
double speed[maxn], ans[maxn];

int main() {
    int n, m; cin >> n >> m;
    double s; cin >> s;
    for (int i = 0; i < n; ++i) cin >> v[i] >> a[i];
    for (int i = 0; i < m; ++i) cin >> x[i] >> d[i];
    for (int i = 0; i < n; ++i) h[i] = v[i] / s;
    double q; cin >> q;
    while (true) {
        int z = 0;
        while (z < n && fabs(h[z]) < 1e-9) z++;
        // cout << "z = " << z << endl;
        if (z == n) break;
        for (int i = z; i < n; ++i) {
            sh[i] = h[i];
            if (i > z) sh[i] += sh[i - 1];
        }
        // printf("height: "); for (int i = 0; i < n; ++i) printf("%.3lf ", h[i]); puts("");
        for (int i = z; i < n; ++i) {
            speed[i] = 0;
            if (i == z) speed[i] += q;
            for (int j = 0; j < m; ++j) {
                if (x[j] >= (i > z ? sh[i - 1] : 0) && x[j] < sh[i]) {
                    speed[i] += d[j];
                }
            }
            speed[i] *= a[i];
            speed[i] /= s;
            if (i > z) speed[i] += speed[i - 1];
            // printf("speed[%d] = %.3lf\n", i, speed[i]);
        }
        for (int i = z; i < n; ++i) {
            t[i] = 1e9;
            for (int j = 0; j < m; ++j) {
                if (x[j] >= (i ? sh[i - 1] : 0) && x[j] < sh[i]) {
                    if (speed[i] > 0) t[i] = min(t[i], (sh[i] - x[j]) / speed[i]);
                }
            }
            if (i == z) t[i] = min(t[i], sh[i] / speed[i]);
        }
        double tall = 1e9;
        for (int i = z; i < n; ++i) {
            tall = min(tall, t[i]);
        }
        for (int i = z; i < n; ++i) {
            sh[i] -= speed[i] * tall;
        }
        for (int i = z; i < n; ++i) {
            if (i == z) h[i] = sh[i];
            else h[i] = sh[i] - sh[i - 1];
        }
        // cout << tall << endl;
        ans[z] += q * a[z] * tall;
        // cout << "add " << q * a[z] * tall << endl;
    }
    for (int i = 0; i < n; ++i)
        cout << fixed << setprecision(20) << ans[i] << endl;
}
