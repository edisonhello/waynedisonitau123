#include <bits/stdc++.h>
#define double long double
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, L;
        cin >> n >> L;
        vector<int> a(n), t(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> t[i];
        }
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j) {
            return a[i] > a[j];
        });
        double v = 0.0;
        double dist = 0.0;
        double ans = 0.0;
        bool ok = false;
        for (int i = 0; i < n; ++i) {
            double aa = a[ord[i]] / 1000.0;
            double tt = t[ord[i]] / 1000000.0;
            double dd = (v + v + aa * tt) * tt / 2;
            if (dist + dd >= L) {
                double l = 0.0, r = tt;
                for (int it = 0; it < 100; ++it) {
                    double m = (l + r) / 2;
                    double ddd = (v + v + aa * m) * m / 2;
                    if (dist + ddd >= L) r = m;
                    else l = m;
                }
                ans += l;
                ok = true;
                break;
            } else {
                ans += tt;
                dist += dd;
                v += aa * tt;
            }
        }
        if (!ok) ans += (L - dist) / v;
        cout << fixed << setprecision(20) << ans << "\n";
    }
    return 0;
}

