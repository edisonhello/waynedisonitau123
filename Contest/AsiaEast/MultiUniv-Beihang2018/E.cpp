#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-9;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, R; cin >> n >> R;
        double ans = 2 * R * pi;
        // cerr << ans << endl;
        while (n--) {
            int x, y, r; cin >> x >> y >> r;
            int dd = x * x + y * y;
            double d = sqrt((double)dd);
            if (d + r < R) ;
            else if (d - r >= R); 
            else {
                double ang1 = acos((R * R + dd - r * r) / (2 * d * R));
                ans -= ang1 * 2 * R;
                double ang2 = acos((r * r + dd - R * R) / (2 * d * r));
                ans += ang2 * 2 * r;
                // cerr << "ang1 ang2 " << ang1 << ' ' << ang2 << endl;
                // cerr << "cos " << cos(ang1) << ' ' << cos(ang2) << endl;
            }
            // cerr << "ans = " << ans << endl;
        }
        cout << fixed << setprecision(10) << ans << endl;
    }
}

