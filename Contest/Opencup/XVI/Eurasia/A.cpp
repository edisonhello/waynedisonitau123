#include <bits/stdc++.h>
using namespace std;

double pos[100005][2];

pair<double, double> spin(double x, double y, double o) {
    double c = cos(o), s = sin(o);
    return make_pair(x * c - y * s, x * s + y * c);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m; 
    for (int i = 1; i <= n; ++i) cin >> pos[i][0] >> pos[i][1];
    while (m--) {
        double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        for (int i = 1; i <= n; ++i) {
            double crs = (pos[i][0] - x1) * (y2 - y1) - (pos[i][1] - y1) * (x2 - x1);
            double dot = (pos[i][0] - x1) * (x2 - x1) + (pos[i][1] - y1) * (y2 - y1);
            // cerr << crs << " " << dot << endl;
            if (crs > 0) {
                double theta = acos(dot / hypot(x2 - x1, y2 - y1) / hypot(pos[i][0] - x1, pos[i][1] - y1));
                pair<double, double> oo = spin(pos[i][0] - x1, pos[i][1] - y1, theta * 2);
                pos[i][0] = x1 + oo.first;
                pos[i][1] = y1 + oo.second;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << fixed << setprecision(10) << pos[i][0] << " " << pos[i][1] << '\n';
    }
}
