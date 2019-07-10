#include <bits/stdc++.h>
using namespace std;
#define double long double

struct Line {
    double x1, y1, x2, y2;
    void input() { cin >> x1 >> y1 >> x2 >> y2; }
} line[10005];

bool same(double a, double b) {
    return abs(a - b) < 1e-10;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) line[i].input();
    auto gogo = [&] (double x, double y) -> pair<double, double> {
        // cerr << "gogo " << x << " " << y << endl;
        for (int ii = 1; ii <= n; ++ii) {
            // cerr << "ii = " << ii << " , x y = " << x << " " << y << endl;
            int i = ii % n;
            double v1x = line[i].x1 - line[i].x2, v1y = line[i].y1 - line[i].y2;
            double v2x = x - line[i].x2, v2y = y - line[i].y2;
            if (same(v2x, 0) && same(v2y, 0)) continue;
            // cerr << "v2x v2y = " << v2x << " " << v2y << endl;
            double l1 = hypot(v1x, v1y);
            double l2 = hypot(v2x, v2y);
            double l3 = hypot(x - line[i].x1, y - line[i].y1);
            if (same(l1 + l2, l3) || same(l1 + l3, l2) || same(l2 + l3, l1)) continue;
            // cerr << "l1 l2 l3 " << l1 << " " << l2 << " " << l3 << endl;
            double ang = acos((l1 * l1 + l2 * l2 - l3 * l3) / (2 * l1 * l2));
            double l = sin(ang) * l2;
            // cerr << "l = " << l << " ang = " << ang << endl;
            double dx = line[i].x2 - line[i].x1, dy = line[i].y2 - line[i].y1;
            swap(dx, dy); dy *= -1;
            double dl = hypot(dx, dy);
            dx = dx / dl * l, dy = dy / dl * l;
            // cerr << "d " << dx << " " << dy << " " << dl << endl;
            double p1x = x + dx, p1y = y + dy;
            double p2x = x - dx, p2y = y - dy;
            // cerr << "p " << p1x << " " << p1y << " " << p2x << " " << p2y << endl;
            if (same(p1x, line[i].x2) && same(p1y, line[i].y2)) { tie(x, y) = make_pair(p1x, p1y); continue; }
            if (same(p2x, line[i].x2) && same(p2y, line[i].y2)) { tie(x, y) = make_pair(p2x, p2y); continue; }
            auto cos_sim = [&] (double x, double y) -> double {
                return abs((x - line[i].x2) * (line[i].x1 - line[i].x2) + (y - line[i].y2) * (line[i].y1 - line[i].y2)) / hypot(x - line[i].x2, y - line[i].y2) / hypot(line[i].x1 - line[i].x2, line[i].y1 - line[i].y2);
            };
            if (cos_sim(p1x, p1y) > cos_sim(p2x, p2y)) tie(x, y) = make_pair(p1x, p1y);
            else tie(x, y) = make_pair(p2x, p2y);
        }
        return make_pair(x, y);
    };
    double x3 = line[0].x1, y3 = line[0].y1, x4 = line[0].x2, y4 = line[0].y2;
    double x5, y5, x6, y6; tie(x5, y5) = gogo(x3, y3), tie(x6, y6) = gogo(x4, y4);
    // cerr << x3 << " " << y3 << " " << x4 << " " << y4 << " " << x5 << " " << y5 << " " << x6 << " " << y6 << endl;
    if (same(x3, x5) && same(y3, y5)) cout << fixed << setprecision(12) << x3 << " " << y3 << endl;
    else if (same(x4, x6) && same(y4, y6)) cout << fixed << setprecision(12) << x4 << " " << y6 << endl;
    else if (same(x5, x6) && same(y5, y6)) cout << fixed << setprecision(12) << x5 << " " << y5 << endl;
    else {
        double x = 7122, y = 5487;
        if (line[0].x1 == line[0].x2) x = line[0].x1;
        else {
            double l1 = hypot(x4 - x3, y4 - y3), l2 = hypot(x6 - x5, y6 - y5);
            if (x4 < x3) l1 *= -1;
            if (x6 < x5) l2 *= -1;
            if (abs(l1 - l2) < 1e-10) {
                cout << "-1" << endl;
                exit(0);
            }
            x = (x3 * l2 - l1 * x5) / (l2 - l1);
        }
        if (line[0].y1 == line[0].y2) y = line[0].y1;
        else {
            double l1 = hypot(x4 - x3, y4 - y3), l2 = hypot(x6 - x5, y6 - y5);
            if (y4 < y3) l1 *= -1;
            if (y6 < y5) l2 *= -1;
            if (abs(l1 - l2) < 1e-10) {
                cout << "-1" << endl;
                exit(0);
            }
            y = (y3 * l2 - l1 * y5) / (l2 - l1);
        }
        cout << fixed << setprecision(12) << x << " " << y << endl;
    }

}
