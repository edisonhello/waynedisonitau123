#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define double long double
using namespace std;
 
const int maxn = 1e5 + 5;
const double kEps = 1e-15;
const int kMagic = 700;
int x[maxn], y[maxn], z[maxn];
int gx[maxn], gy[maxn], gz[maxn];
double dx[maxn], dy[maxn], dz[maxn];
 
int main() {
    int m, n, S, W;
    while (scanf("%d%d%d%d", &m, &n, &S, &W) != EOF) {
        if (!n && !m && !S && !W) break;
        for (int i = 0; i < m; ++i) scanf("%d%d%d", &x[i], &y[i], &z[i]);        
        int g = S;
        for (int i = 0; i < n; ++i) {
            x[i + m] = (g / 7) % 100 + 1;
            y[i + m] = (g / 700) % 100 + 1;
            z[i + m] = (g / 70000) % 100 + 1;
            if (g % 2 == 0) g >>= 1;
            else g = (g >> 1) ^ W;
        }
 
        map<tuple<int, int, int>, int> zz;
 
        vector<int> od;
        for (int i = 0; i < n + m; ++i) {
            int g = __gcd(abs(x[i]), __gcd(abs(y[i]), abs(z[i])));
            gx[i] = x[i] / g;
            gy[i] = y[i] / g;
            gz[i] = z[i] / g;
            auto tp = make_tuple(gx[i], gy[i], gz[i]);
            if (zz.find(tp) == zz.end() || make_tuple(x[zz[tp]], y[zz[tp]], z[zz[tp]]) > make_tuple(x[i], y[i], z[i])) {
                zz[tp] = i;
            }
        }
        for (auto it : zz) od.push_back(it.second);
        for (int j = 0; j < (int)od.size(); ++j) {
            int i = od[j];
            double leng = sqrt(x[i] * x[i] + y[i] * y[i] + z[i] * z[i]);
            dx[i] = x[i] / leng;
            dy[i] = y[i] / leng;
            dz[i] = z[i] / leng;
        }
        double ang = -1e9;
        tuple<int, int, int> z1, z2;
 
        auto Angle = [&](int i, int j) {
            return dx[i] * dx[j] + dy[i] * dy[j] + dz[i] * dz[j];
        };
 
        sort(od.begin(), od.end(), [&](int i, int j) {
            return dx[i] < dx[j];
        });
        
        for (int i = 0; i < (int)od.size(); ++i) {
            for (int j = max(0, i - kMagic); j < i; ++j) {
                double ag = Angle(od[i], od[j]);
                tuple<int, int, int> v1 = make_tuple(x[od[i]], y[od[i]], z[od[i]]);
                tuple<int, int, int> v2 = make_tuple(x[od[j]], y[od[j]], z[od[j]]);
                if (v1 > v2) swap(v1, v2);
                if (ag > ang || fabs(ag - ang) < kEps && make_pair(v1, v2) < make_pair(z1, z2)) {
                    ang = ag;
                    z1 = v1;
                    z2 = v2;
                } 
            }
        }
 
        sort(od.begin(), od.end(), [&](int i, int j) {
            return dy[i] < dy[j];
        });
        
        for (int i = 0; i < (int)od.size(); ++i) {
            for (int j = max(0, i - kMagic); j < i; ++j) {
                double ag = Angle(od[i], od[j]);
                tuple<int, int, int> v1 = make_tuple(x[od[i]], y[od[i]], z[od[i]]);
                tuple<int, int, int> v2 = make_tuple(x[od[j]], y[od[j]], z[od[j]]);
                if (v1 > v2) swap(v1, v2);
                if (ag > ang || fabs(ag - ang) < kEps && make_pair(v1, v2) < make_pair(z1, z2)) {
                    ang = ag;
                    z1 = v1;
                    z2 = v2;
                } 
            }
        }
 
        sort(od.begin(), od.end(), [&](int i, int j) {
            return dz[i] < dz[j];
        });
        
        for (int i = 0; i < (int)od.size(); ++i) {
            for (int j = max(0, i - kMagic); j < i; ++j) {
                double ag = Angle(od[i], od[j]);
                tuple<int, int, int> v1 = make_tuple(x[od[i]], y[od[i]], z[od[i]]);
                tuple<int, int, int> v2 = make_tuple(x[od[j]], y[od[j]], z[od[j]]);
                if (v1 > v2) swap(v1, v2);
                if (ag > ang || fabs(ag - ang) < kEps && make_pair(v1, v2) < make_pair(z1, z2)) {
                    ang = ag;
                    z1 = v1;
                    z2 = v2;
                } 
            }
        }
        printf("%d %d %d %d %d %d\n", get<0>(z1), get<1>(z1), get<2>(z1), get<0>(z2), get<1>(z2), get<2>(z2));
    }
    return 0;
}
