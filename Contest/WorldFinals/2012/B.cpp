#include <bits/stdc++.h>
using namespace std;

const double kPi = acos(-1);
const int kIter = 50;

vector<double> Multiply(const vector<double> &a, const vector<double> &b) {
    vector<double> res(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j)
            res[i + j] += a[i] * b[j];
    }
    return res;
}

int main() {
    int n, tc = 0;
    while (scanf("%d", &n) == 1) {
        vector<double> p(n + 1);
        for (int i = 0; i <= n; ++i) scanf("%lf", &p[i]);
        p = Multiply(p, p);
        double low, high; scanf("%lf%lf", &low, &high);
        double inc; scanf("%lf", &inc);

        auto Integral = [&](double x) {
            double v = 0, d = x;
            for (int i = 0; i < p.size(); ++i) {
                v += p[i] / (i + 1) * d;
                d *= x;
            }
            return v * kPi;
        };

        double base = Integral(low);

        auto Volume = [&](double x) {
            return Integral(x) - base;
        };
        printf("Case %d: ", ++tc);
        double total = Volume(high);
        printf("%.2lf\n", total);
        if (total < inc) {
            puts("insufficient volume");
            continue;
        }
        for (int i = 1; i <= 8; ++i) {
            double target = inc * i;
            if (target > total) break;
            double l = low, r = high;
            for (int it = 0; it < kIter; ++it) {
                double mid = (l + r) * 0.5;
                if (Volume(mid) > target) r = mid;
                else l = mid;
            }
            printf("%.2lf ", l - low);
        }
        puts("");
    }
    return 0;
}

