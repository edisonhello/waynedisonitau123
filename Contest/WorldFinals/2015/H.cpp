#include <bits/stdc++.h>
using namespace std;


int main() {
    int w, h, n; cin >> w >> h >> n;
    double A = (double)h / w;

    vector<double> xs(n + 2);
    auto Check = [&] (double x1) -> double {
        xs[0] = 0;
        xs[1] = x1;
        for (int i = 2; i <= n + 1; ++i) {
            xs[i] = (-xs[i - 1] - (A * A - 1) / 2 * xs[i - 2]) / ((A * A - 1) / 2);
            if (xs[i] > w * 2) return w * 2;
        }
        return xs[n + 1];
    };

    double l = 0, r = w;
    int it = 60;
    while (it--) {
        double m = (l + r) / 2;
        if (Check(m) > w) r = m;
        else l = m;
    }

    Check(l);

    double co = (double)h * h / 2;
    for (int i = 1; i <= n + 1; ++i) {
        co += pow((xs[i - 1] * (A - 1) + xs[i] * (A + 1)) / 2, 2) - (xs[i] * xs[i] / 2 * A * A);
    }

    cout << fixed << setprecision(10);
    cout << co << endl;
    for (int i = 1; i <= min(10, n); ++i) cout << xs[i] << endl;

}

