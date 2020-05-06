#include <bits/stdc++.h>
#define double long double
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    vector<int> ds(y.begin(), y.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    for (int i = 0; i < n; ++i) {
        w[i] = lower_bound(ds.begin(), ds.end(), y[i]) - ds.begin();
    }

    constexpr double kEps = 1E-12;

    auto Count = [&](double rot) {
        vector<double> z(n);
        for (int i = 0; i < n; ++i) {
            double dx = y[i] / tan(rot);
            z[i] = x[i] - dx;
        }
        vector<int> fenw(ds.size() + 1);
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j) {
            if (fabs(z[i] - z[j]) < kEps) return y[i] < y[j];
            return z[i] < z[j];
        });
        int64_t res = 0;

        auto Query = [&](int p) {
            int res = 0;
            for (int i = p + 1; i > 0; i -= i & -i) {
                res += fenw[i];
            }
            return res;
        };

        auto Update = [&](int p) {
            for (int i = p + 1; i < fenw.size(); i += i & -i) {
                fenw[i]++;
            }
        };

        for (int i = 0; i < n; ++i) {
            res += Query(w[ord[i]]);
            Update(w[ord[i]]);
        }
        return res;
    };

    int64_t n2 = 1LL * n * (n - 1) / 2;
    constexpr double kPi = acos(-1);
    constexpr int kIter = 100;
    if (n2 & 1) {
        double l = 0.0, r = kPi;
        for (int it = 0; it < kIter; ++it) {
            double m = 0.5 * (l + r);
            if (Count(m) >= n2 / 2 + 1) r = m;
            else l = m;
        }
        cout << fixed << setprecision(20) << l << "\n";
    } else {
        double a = 0, b = 0;
        {
            double l = 0.0, r = kPi;
            for (int it = 0; it < kIter; ++it) {
                double m = 0.5 * (l + r);
                if (Count(m) >= n2 / 2) r = m;
                else l = m;
            }
            a = l;
        }
        {
            double l = 0.0, r = kPi;
            for (int it = 0; it < kIter; ++it) {
                double m = 0.5 * (l + r);
                if (Count(m) >= n2 / 2 + 1) r = m;
                else l = m;
            }
            b = l;
        }
        cout << fixed << setprecision(20) << (a + b) / 2 << "\n";
    }
}

