#include <bits/stdc++.h>
using namespace std;
#define double long double

double fac[50];
double C(int n, int m) {
    return fac[n] / (fac[m] * fac[n - m]);
}

double pw(double b, int n) {
    double a = 1;
    while (n) {
        if (n & 1) a *= b;
        b *= b; n >>= 1;
    }
    return a;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < 50; ++i) fac[i] = fac[i - 1] * i;
    int t; cin >> t; while (t--) {
        double pa, pb; cin >> pa >> pb;
        double pp = 0;
        double QQ = pa * (1 - pb) / ((pa * (1 - pb)) + (pb * (1 - pa)));
        for (int i = 0; i <= 10; ++i) {
            for (int j = 0; j <= 10; ++j) {
                double prob = C(10, i) * pw(pa, i) * pw(1 - pa, 10 - i) * C(10, j) * pw(pb, j) * pw(1 - pb, 10 - j);
                int si = i + 10 - j;
                int sj = j + 10 - i;
                // cerr << fixed << setprecision(20);
                // cerr << "i j si sj prob " << i << ' ' << j << ' ' << si << ' ' << sj << ' ' << prob << endl;
                if (si == sj) {
                    pp += prob * QQ;
                } else {
                    if (si > sj) {
                        pp += prob;
                    }
                }
            }
        }

        double p = 0;
        for (int i = 0; i < (1 << 7); ++i) {
            double ppp = 1;
            int w = 0;
            for (int z = 0; z < 7; ++z) {
                if (i & (1 << z)) ppp *= pp, ++w;
                else ppp *= (1 - pp);
            }
            if (w >= 4) p += ppp;
        }

        cout << fixed << setprecision(12) << p << endl;
    }
}
