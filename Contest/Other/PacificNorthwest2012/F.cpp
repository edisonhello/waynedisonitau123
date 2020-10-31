#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-9;

struct P {
    int x, y;

    P operator- (P b) { return P{x - b.x, y - b.y}; }
    int operator* (P b) { return x * b.x + y * b.y; }
    int operator^ (P b) { return x * b.y - y * b.x; }
    double abs() { return hypot(x, y); }
};

vector<P> Parse(string s) {
    stringstream ss(s);
    ss >> s;
    vector<P> ps;
    while (ss >> s) {
        if (s == "none") continue;
        int x, y;
        sscanf(s.c_str(), "(%d,%d)", &x, &y);
        ps.emplace_back(P{x, y});
    }
    return ps;
}

int main() {
    string s;
    while (getline(cin, s)) {
        string t; 
        getline(cin, t);

        vector<P> ps = Parse(s), qs = Parse(t);
        
        if (ps.size() <= 1u) {
            cout << "0" << '\n';
            continue;
        }

        double ans = 1e15;
        for (int i = 0; i < (int)ps.size(); ++i) {
            for (int j = i + 1; j < (int)ps.size(); ++j) {
                P dir = ps[j] - ps[i];
                double a = dir.abs();
                double pmin = pi;
                double pmax = 0;
                double nmin = pi;
                double nmax = 0;
                bool nosol = 0;

                for (int k = 0; k < (int)ps.size(); ++k) if (k != i && k != j) {
                    int crx = (dir ^ (ps[k] - ps[i]));
                    double b = (ps[k] - ps[i]).abs();
                    double c = (ps[k] - ps[j]).abs();
                    double cox = -(a * a - b * b - c * c) / (2 * b * c);
                    double o = acos(cox);
                    // cerr << "o = " << o << endl;
                    if (crx > 0) {
                        pmin = min(pmin, o);
                    } else if (crx < 0) {
                        nmin = min(nmin, o);
                    } else {
                        int dot = dir * (ps[k] - ps[i]);
                        int sq = dir * dir;

                        if (dot > sq || dot < 0) nosol = 1;
                    }
                }

                for (int k = 0; k < (int)qs.size(); ++k) {
                    int crx = (dir ^ (qs[k] - ps[i]));
                    double b = (qs[k] - ps[i]).abs();
                    double c = (qs[k] - ps[j]).abs();
                    double cox = -(a * a - b * b - c * c) / (2 * b * c);
                    double o = acos(cox);
                    if (crx > 0) {
                        pmax = max(pmax, o);
                    } else if (crx < 0) {
                        nmax = max(nmax, o);
                    } else {
                        int dot = dir * (qs[k] - ps[i]);
                        int sq = dir * dir;

                        if (0 <= dot && dot <= sq) nosol = 1;
                    }
                }

                // cerr << "pmax pmin nmax nmin " << pmax << ' ' << pmin << ' ' << nmax  << ' ' << nmin << endl;
                if (pmax >= pmin - eps) nosol = 1;
                if (nmax >= nmin - eps) nosol = 1;

                double l = pmax, r = pmin;
                l = max(l, pi - nmin);
                r = min(r, pi - nmax);
                if (l >= r - eps) nosol = 1;

                if (nosol) continue;
                // cerr << "l r " << l << ' ' << r << endl;

                if (l <= pi / 2 && pi / 2 <= r) {
                    ans = min(ans, a / 2);
                } else if (r <= pi / 2) {
                    ans = min(ans, a / sin(r) / 2);
                } else {
                    ans = min(ans, a / sin(l) / 2);
                }

                // cerr << "ans = " << ans << endl;
            }
        }

        if (ans > 1e14) {
            cout << "The Orcs are close" << '\n';
        } else {
            cout << fixed << setprecision(12) << ans << '\n';
        }
    }
}
