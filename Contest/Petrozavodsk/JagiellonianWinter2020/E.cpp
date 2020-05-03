#include <bits/stdc++.h>
using namespace std;

enum Type { POINT, QUERY };

struct Point {
    int x, y, z, w;
    Type type;

    Point() = default;
    Point(int x, int y, int z, Type type, int w) : x(x), y(y), z(z), type(type), w(w) {}

    bool operator<(const Point &rhs) const {
        return x < rhs.x;
    }
};

vector<int> Solve(vector<Point> p, int n) {
    sort(p.begin(), p.end());
    vector<int> ds, dz;
    for (int i = 0; i < p.size(); ++i) {
        ds.push_back(p[i].y);
        dz.push_back(p[i].z);
    }
    sort(ds.begin(), ds.end());
    sort(dz.begin(), dz.end());
    for (int i = 0; i < p.size(); ++i) {
        p[i].y = lower_bound(ds.begin(), ds.end(), p[i].y) - ds.begin();
        p[i].z = lower_bound(dz.begin(), dz.end(), p[i].z) - dz.begin();
    }

    constexpr int kInf = 1'000'000'000 + 123;
    vector<int> fenw(ds.size() + 1, -kInf);
    vector<int> upd;

    auto Modify = [&](int p, int v) {
        for (int i = p + 1; i < fenw.size(); i += i & -i) {
            fenw[i] = max(fenw[i], v);
            upd.push_back(i);
        }
    };

    auto Query = [&](int p) {
        int res = -kInf;
        for (int i = p + 1; i > 0; i -= i & -i) {
            res = max(res, fenw[i]);
        }
        return res;
    };

    auto Revert = [&]() {
        for (int u : upd) fenw[u] = -kInf;
        upd.clear();
    };

    vector<int> res(n, -kInf);

    auto DivideConquer = [&](auto self, int l, int r, vector<Point> p) {
        if (r - l == 1) {
            for (int i = 0, j = 0; i < p.size(); i = j) {
                vector<Point> wait;
                while (j < p.size() && p[j].x == p[i].x) {
                    if (p[j].type == POINT) Modify(p[j].y, p[j].w);
                    if (p[j].type == QUERY) wait.push_back(p[j]);
                    j++;
                }
                for (auto &p : wait) {
                    res[p.w] = max(res[p.w], Query(p.y));
                }
            }
            Revert();
            return;
        }
        int m = (l + r) >> 1;
        vector<Point> lp, rp;
        for (int i = 0, j = 0; i < p.size(); i = j) {
            vector<Point> wait;
            while (j < p.size() && p[j].x == p[i].x) {
                if (p[j].z >= m && p[j].type == POINT) {
                    Modify(p[j].y, p[j].w);
                }
                if (p[j].z < m && p[j].type == QUERY) wait.push_back(p[j]);

                (p[j].z >= m ? rp : lp).push_back(p[j]);
                j++;
            }
            for (auto &p : wait) {
                res[p.w] = max(res[p.w], Query(p.y));
            }
        }
        Revert();
        self(self, l, m, lp);
        self(self, m, r, rp);
    };

    DivideConquer(DivideConquer, 0, dz.size(), p);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Point> point;
    for (int i = 0; i < n; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        point.emplace_back(x, y - r, y + r, POINT, x);
    }

    vector<int> target(q);
    for (int i = 0; i < q; ++i) {
        int x1, y1, x2, y2, a, b;
        cin >> x1 >> y1 >> x2 >> y2 >> a >> b;
        if (x1 > x2) swap(x1, x2);
        point.emplace_back(x2, a, b, QUERY, i);
        target[i] = x1;
        // query.push_back((Query){x1, y1, x2, y2, a, b, i});
    }

    auto res = Solve(point, q);
    for (int i = 0; i < q; ++i) cout << (res[i] >= target[i] ? "NO" : "YES") << "\n";
    return 0;
}

