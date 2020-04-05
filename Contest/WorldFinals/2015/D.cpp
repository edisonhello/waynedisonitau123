#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);

int cs[10004][4];

int main() {
    int n, s; cin >> n >> s;

    for (int i = 1; i <= n; ++i) cin >> cs[i][0] >> cs[i][1] >> cs[i][2] >> cs[i][3];

    double tot = (double)100000 * 100000 * 100000;
    for (int i = 1; i <= n; ++i) tot -= (double)4 / 3 * cs[i][0] * cs[i][0] * cs[i][0] * pi;

    auto GetArea = [&] (double L, double R) {
        double rt = (double)100000 * 100000 * (R - L);

        for (int i = 1; i <= n; ++i) {
            double z = cs[i][3];
            double r = cs[i][0];

            auto Cut = [&] (double x) {
                if (x < 0) return (double)0;
                return (-x * x * x / 3 + r * x * x) * pi;
            };

            if (z + r <= L) continue;
            if (z - r >= R) continue;

            double cu = (double)4 / 3 * r * r * r * pi;
            
            cu -= Cut(L - (z - r));
            cu -= Cut(z + r - R);

            rt -= cu;
        }

        return rt;
    };


    double every = tot / s;
    double cur = 0;
    for (int i = 1; i <= s; ++i) {
        double L = cur, R = 100000;
        int it = 50;
        while (it--) {
            double M = (L + R) / 2;
            if (GetArea(cur, M) >= every) R = M;
            else L = M;
        }

        cout << fixed << setprecision(10) << (L - cur) / 1000 << '\n';
        cur = L;
    }
}

