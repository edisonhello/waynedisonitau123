#include <bits/stdc++.h>
using namespace std;

#define double long double

double pos[3][2];
double dis[3];
double w;

double go(double a, double b, double l) {
    if (l <= w) {
        double theta = acos((a * a + l * l - b * b) / (2 * a * l));
        if (theta > acos(-1) / 2 + 1e-8) return 1e9;
        if (a * cos(theta) > w + 1e-8) return 1e9;
        return a * sin(theta);
    } else {
        double theta = acos(w / l);
        double phi = acos((l * l + a * a - b * b) / (2 * l * a));
        if (phi - theta > acos(-1) / 2 + 1e-8) return 1e9;
        if (cos(phi - theta) * a > w + 1e-8) return 1e9;
        // cerr << a << " " << b << " " << l << " get " << l * sin(theta) + a * sin(phi - theta) << endl;
        // cerr << "theta = " << theta << " , phi = " << phi << endl;
        return l * sin(theta) + max(a * sin(phi - theta), (double)0);
    }
}

double go() {
    return min(min(go(dis[0], dis[1], dis[2]), min(go(dis[1], dis[2], dis[0]), go(dis[2], dis[0], dis[1]))),
        min(go(dis[1], dis[0], dis[2]), min(go(dis[2], dis[1], dis[0]), go(dis[0], dis[2], dis[1]))));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 2; ++j) cin >> pos[i][j]; cin >> w;
        dis[0] = hypot(pos[0][0] - pos[1][0], pos[0][1] - pos[1][1]);
        dis[1] = hypot(pos[0][0] - pos[2][0], pos[0][1] - pos[2][1]);
        dis[2] = hypot(pos[2][0] - pos[1][0], pos[2][1] - pos[1][1]);
        double ans = go();
        if (ans > 1e7) cout << "impossible" << '\n';
        else cout << fixed << setprecision(10) << ans << '\n';
    }
}
