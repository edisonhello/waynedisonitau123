#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-12;

struct P {
    int x, y;
    P operator- (const P b) { return P{x - b.x, y - b.y}; }
    double angle() { return atan2(y, x); }
};

void print(vector<pair<double, double>> segs) {
    for (auto [l, r] : segs) {
        cerr << "(" << l << ", " << r << ") ";
    }
    cerr << endl;
}


int main() {
    int n; cin >> n;
    vector<P> ps;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps.push_back(P{x, y});
    }

    auto merge = [&] (vector<pair<double, double>> segs) {
        vector<pair<double, double>> rt;
        if (segs.empty()) return rt;

        sort(segs.begin(), segs.end());

        double l = segs[0].first, r = segs[0].second;
        double tot = 0;
        for (auto &p : segs) {
            if (p.first <= r) r = max(r, p.second);
            else {
                tot += r - l;
                rt.emplace_back(l, r);
                l = p.first;
                r = p.second;
            }
        }
        tot += r - l;
        rt.emplace_back(l, r);

        return rt;
    };

    auto check = [&] (vector<pair<double, double>> segs) -> vector<pair<double, double>> {
        auto tmp = merge(segs);

        double tot = 0;
        for (auto &[l, r] : tmp) tot += r - l;

        if (tot >= pi - eps) {
            cout << "Impossible" << endl;
            exit(0);
        }
        // cerr << "checked tot = " << tot << endl;

        return tmp;
    };

    auto getnot = [&] (vector<pair<double, double>> segs) {
        segs = merge(segs);

        vector<pair<double, double>> rt;
        double cur = -pi;
        for (auto &p : segs) {
            if (abs(cur - p.first > eps)) rt.emplace_back(cur, p.first);
            cur = p.second;
        }
        if (abs(pi - cur) > eps) rt.emplace_back(cur, pi);

        return rt;
    };

    for (int i = 1; i < n - 1; ++i) {
        vector<pair<double, double>> segs;
        // cerr << "i = " << i << endl;
        double o = (ps[i - 1] - ps[i]).angle();
        segs.emplace_back(o, o);
        for (int j = 1; j < i; ++j) {
            P p1 = ps[j - 1] - ps[i];
            P p2 = ps[j] - ps[i];
            double o1 = p1.angle();
            double o2 = p2.angle();
            if (o2 < o1) swap(o1, o2);
            if (o2 - o1 > pi) {
                segs.emplace_back(o2, pi);
                segs.emplace_back(-pi, o1);
            } else {
                segs.emplace_back(o1, o2);
            }
        }

        auto tmp = check(segs);
        segs.clear();

        o = (ps[i + 1] - ps[i]).angle();
        segs.emplace_back(o, o);
        for (int j = i + 2; j < n; ++j) {
            P p1 = ps[j - 1] - ps[i];
            P p2 = ps[j] - ps[i];
            double o1 = p1.angle();
            double o2 = p2.angle();
            if (o2 < o1) swap(o1, o2);
            if (o2 - o1 > pi) {
                segs.emplace_back(o2, pi);
                segs.emplace_back(-pi, o1);
            } else {
                segs.emplace_back(o1, o2);
            }
        }

        auto tmp2 = check(segs);
        segs.clear();

        // cerr << "tmp" << endl;
        // print(tmp);
        // print(tmp2);

        // tmp = getnot(tmp);
        // tmp2 = getnot(tmp2);

        // cerr << "!tmp" << endl;
        // print(tmp);
        // print(tmp2);

        // for (auto &p : tmp2) tmp.push_back(p);

        // auto tmp3 = merge(tmp);
        // cerr << "merge" << endl;
        // print(tmp3);
        // tmp3 = getnot(tmp3);
        // cerr << "and " << endl;
        // print(tmp3);

        // if (tmp3.size()) {
        //     cout << "Impossible" << endl;
        //     exit(0);
        // }

        int oz = tmp.size() + tmp2.size();
        for (auto &p : tmp2) tmp.push_back(p);

        auto tmp3 = merge(tmp);
        if (tmp3.size() != oz) {
            cout << "Impossible" << endl;
            exit(0);
        }

    }

    cout << "Possible" << endl;
}

