#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

int main() {
    int q; cin >> q;
    while (q--) {
        int x, y, t; cin >> x >> y >> t;
        double theta = t % 360;
        theta = theta / 180 * pi;
        double cs = cos(-theta), sn = sin(-theta);
        double tx = x * cs - sn * y;
        double ty = x * sn + cs * y;
        cout << fixed << setprecision(20) << tx << ' ' << ty << endl;
    }
}
