#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x) * (x))

struct P {
    int x, y, z;
    P() : x(0), y(0), z(0) {}
    P(int x, int y, int z) : x(x), y(y), z(z) {}
};

P operator+ (const P &a, const P &b) { return P(a.x + b.x, a.y + b.y, a.z + b.z); }
P operator- (const P &a, const P &b) { return P(a.x - b.x, a.y - b.y, a.z - b.z); }

int operator* (const P &a, const P &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
P operator^ (const P &a, const P &b) { return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<P> ps(n);
    for (int i = 0; i < n; ++i) 
        cin >> ps[i].x >> ps[i].y >> ps[i].z;


    auto _Calc = [&] (vector<int> &v) -> double {
        if (v.empty()) return 0.0;
        double x = 0, y = 0, z = 0;
        for (auto i : v)
            x += ps[i].x, y += ps[i].y, z += ps[i].z;
        x /= v.size(), y /= v.size(), z /= v.size();

        double sum = 0;
        for (auto i : v)
            sum += sq(ps[i].x - x) + sq(ps[i].y - y) + sq(ps[i].z - z);
        return sum;
    };

    if (k == 1) {
        vector<int> a;
        for (int i = 0; i < n; ++i) a.push_back(i);
        cout << fixed << setprecision(12) << _Calc(a) << '\n';
        exit(0);
    }
    if (k == 2) {
        if (n <= 2) {
            cout << "0.000000000" << '\n';
            exit(0);
        }
    }

    vector<int> po, ne;
    double ans = 1e20;

    auto Calc = [&] () { ans = min(ans, _Calc(po) + _Calc(ne)); };

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                P ijk = (ps[j] - ps[i]) ^ (ps[k] - ps[i]);
                po.clear(), ne.clear();
                for (int l = 0; l < n; ++l) if (l != i && l != j && l != k) {
                    if ((ps[l] - ps[i]) * ijk > 0) po.push_back(l);
                    else ne.push_back(l);
                }

                vector<int> zz = {i, j, k};
                for (int z = 0; z < 8; ++z) {
                    for (int i = 0; i < 3; ++i) 
                        if (z & (1 << i)) po.push_back(zz[i]);
                        else ne.push_back(zz[i]);
                    Calc();
                    for (int i = 0; i < 3; ++i) 
                        if (z & (1 << i)) po.pop_back();
                        else ne.pop_back();
                }
            }
        }
    }

    cout << fixed << setprecision(12) << ans << endl;

}

