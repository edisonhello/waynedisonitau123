#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 2e5 + 5;
double ration = sqrt(2) - 1;
int x[maxn], y[maxn], rx[maxn], ry[maxn], f[maxn];
 
double fw[maxn];
int wh[maxn];
 
vector<int> record, dx, dy;
 
void add(int p, double v, int w) {
    // cout << "modify p = " << p << " v = " << v << " w = " << w << endl;
    for (int i = p + 1; i < maxn; i += i & -i) {
        if (v > fw[i]) {
            fw[i] = v;
            wh[i] = w;
            // cout << "setto " << w << endl;
            record.push_back(i);
        }
    }
}
 
double dist(int i, int j) {
    int dx = abs(x[i] - x[j]);
    int dy = abs(y[i] - y[j]);
    if (dx < dy) swap(dx, dy);
    return dx + ration * dy;
}
 
pair<double, int> query(int p) {
    double res = -1e12; int w = -1;
    for (int i = p + 1; i > 0; i -= i & -i) {
        if (fw[i] > res) {
            res = fw[i];
            w = wh[i];
            // cout << "wh[i] = " << wh[i] << endl;
        }
    }
    // cout << "query p = " << p << endl;
    // cout << "query w = " << w << endl;
    // cout << "res = " << res << endl;
    return make_pair(res, w);
}
 
void backup(double v) {
    for (int i : record) {
        fw[i] = v;
        wh[i] = -1;
    }
    record.clear();
}
 
struct point {
    int x, y, rx, ry, i;
    point(int x, int y, int rx, int ry, int i) : x(x), y(y), rx(rx), ry(ry), i(i) {}
};
 
double ans = -1e9;
int mi = -1, mj = -1;
 
void cdq2(int l, int r, const vector<point> &ps) {
    if (r - l == 1) {
        for (int i = 0; i < (int)ps.size(); ++i) {
            double k = ps[i].y + ration * ps[i].x;
            auto pp = query(ps[i].ry);
            if (k + pp.first > ans) {
                ans = k + pp.first;
                mi = ps[i].i;
                mj = pp.second;
            }
            add(ps[i].ry, -k, ps[i].i);
        }
        backup(-1e12);
        return;
    }
    int m = (l + r) >> 1;
    vector<point> lp, rp;
    for (int i = 0; i < (int)ps.size(); ++i) {
        double k = ps[i].y + ration * ps[i].x;
        if (ps[i].rx < m) {
            add(ps[i].ry, -k, ps[i].i);
            lp.push_back(ps[i]);
        } else {
            auto pp = query(ps[i].ry);
            if (k + pp.first > ans) {
                ans = k + pp.first;
                mi = ps[i].i;
                mj = pp.second;
            }
            rp.push_back(ps[i]);
        }
    }
    backup(-1e12);
    cdq2(l, m, lp);
    cdq2(m, r, rp);
}
 
void cdq4(int l, int r, const vector<point> &ps) {
    if (r - l == 1) {
        for (int i = 0; i < (int)ps.size(); ++i) {
            double k = ration * ps[i].x - ps[i].y;
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (k + pp.first > ans) {
                ans = k + pp.first;
                mi = ps[i].i;
                mj = pp.second;
            }
            add(dy.size() - 1 - ps[i].ry, ps[i].y - ration * ps[i].x, ps[i].i);
        }
        backup(-1e12);
        return;
    }
    int m = (l + r) >> 1;
    vector<point> lp, rp;
    for (int i = 0; i < (int)ps.size(); ++i) {
        double k = ration * ps[i].x - ps[i].y;
        if (ps[i].rx >= m) {
            add(dy.size() - 1 - ps[i].ry, ps[i].y - ration * ps[i].x, ps[i].i);
            rp.push_back(ps[i]);
        } else {
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (k + pp.first > ans) {
                ans = k + pp.first;
                mi = ps[i].i;
                mj = pp.second;
            }
            lp.push_back(ps[i]);
        }
    }
    backup(-1e12);
    cdq4(l, m, lp);
    cdq4(m, r, rp);
}
 
void cdq1(int l, int r, const vector<point> &ps) {
    if (r - l == 1) {
        for (int i = 0; i < (int)ps.size(); ++i) {
            double k = ps[i].x + ration * ps[i].y;
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (k + pp.first > ans) {
                ans = k + pp.first;
                // cout << "12: " << ps[i].i << ' ' << pp.second << endl;
                mi = ps[i].i;
                mj = pp.second;
            }
            add(dy.size() - 1 - ps[i].ry, -k, ps[i].i);
        }
        backup(-1e12);
        return;
    }
    int m = (l + r) >> 1;
    vector<point> lp, rp;
    // cout << "l = " << l << " r = " << r << endl;
    for (int i = 0; i < (int)ps.size(); ++i) {
        double k = ps[i].x + ration * ps[i].y;
        if (ps[i].rx < m) {
            // cout << "add " << ps[i].i << endl;
            add(dy.size() - 1 - ps[i].ry, -k, ps[i].i);
            lp.push_back(ps[i]);
        } else {
            // cout << "query " << ps[i].i << endl;
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (k + pp.first > ans) {
                // cout << "pp = " << pp.first << ' ' << pp.second << endl;
                // cout << "123: " << ps[i].i << ' ' << pp.second << endl;
                ans = k + pp.first;
                mi = ps[i].i;
                mj = pp.second;
            }
            rp.push_back(ps[i]);
        }
    }
    backup(-1e12);
    cdq1(l, m, lp);
    cdq1(m, r, rp);
}
 
void cdq3(int l, int r, const vector<point> &ps) {
    if (r - l == 1) {
        for (int i = 0; i < (int)ps.size(); ++i) {
            double k = ps[i].x - ration * ps[i].y;
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (pp.first + k > ans) {
                ans = pp.first + k;
                mi = ps[i].i;
                mj = pp.second;
            }
            add(dy.size() - 1 - ps[i].ry, ration * ps[i].y - ps[i].x, ps[i].i);
        }
        backup(-1e12);
        return;
    }
    int m = (l + r) >> 1;
    vector<point> lp, rp;
    for (int i = 0; i < (int)ps.size(); ++i) {
        double k = ps[i].x - ration * ps[i].y;
        if (ps[i].rx < m) {
            add(dy.size() - 1 - ps[i].ry, ration * ps[i].y - ps[i].x, ps[i].i);
            lp.push_back(ps[i]);
        } else {
            auto pp = query(dy.size() - 1 - ps[i].ry);
            if (pp.first + k > ans) {
                ans = pp.first + k;
                mi = ps[i].i;
                mj = pp.second;
            }
            rp.push_back(ps[i]);
        }
    }
    backup(-1e12);
    cdq3(l, m, lp);
    cdq3(m, r, rp);
}
 
void check_answer(int n, int a, int b) {
 
    auto gd = [&] (int a, int b) -> double {
        double dx = abs(x[a] - x[b]), dy = abs(y[a] - y[b]);
        if (dx > dy) return dx + (sqrt(2) - 1) * dy;
        return dy + (sqrt(2) - 1) * dx;
    };
 
    double dist = 0; 
    int xx, yy;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        if (gd(i, j) > dist) {
            dist = gd(i, j);
            xx = i, yy = j;
        }
    }
    
    if (abs(gd(a, b) - dist) > 1e-7) {
        cerr << gd(a, b) << ' ' << dist << endl;
        cerr << "ans = " << xx << " " << yy << endl;
        cerr << "error" << endl;
        exit(1);
    }
}
 
int main() {
    int n; scanf("%d", &n);
    vector<point> ps;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &x[i], &y[i]);
        rx[i] = x[i] + y[i];
        ry[i] = -x[i] + y[i];
        dx.push_back(rx[i]);
        dy.push_back(ry[i]);
        ps.emplace_back(x[i], y[i], rx[i], ry[i], i);
    }
 
    sort(dx.begin(), dx.end());
    dx.resize(unique(dx.begin(), dx.end()) - dx.begin());
    sort(dy.begin(), dy.end());
    dy.resize(unique(dy.begin(), dy.end()) - dy.begin());
 
    for (int i = 0; i < n; ++i) {
        ps[i].rx = lower_bound(dx.begin(), dx.end(), ps[i].rx) - dx.begin();
        ps[i].ry = lower_bound(dy.begin(), dy.end(), ps[i].ry) - dy.begin();
    }
 
    for (int i = 0; i < maxn; ++i) fw[i] = -1e12, wh[i] = -1;
    sort(ps.begin(), ps.end(), [](point a, point b) { return a.x == b.x ? a.ry > b.ry : a.x < b.x; });
    cdq1(0, dx.size(), ps);
    // printf("%d %d\n", mi + 1, mj + 1);
    for (int i = 0; i < maxn; ++i) fw[i] = -1e12, wh[i] = -1;
    cdq3(0, dx.size(), ps);
    // printf("%d %d\n", mi + 1, mj + 1);
 
    for (int i = 0; i < maxn; ++i) fw[i] = -1e12, wh[i] = -1;
    sort(ps.begin(), ps.end(), [](point a, point b) { return a.x == b.x ? a.ry < b.ry : a.x < b.x; });
    cdq2(0, dx.size(), ps);
    // printf("%d %d\n", mi + 1, mj + 1);
    for (int i = 0; i < maxn; ++i) fw[i] = -1e12, wh[i] = -1;
    sort(ps.begin(), ps.end(), [](point a, point b) { return a.x == b.x ? a.ry > b.ry : a.x < b.x; });
    cdq4(0, dx.size(), ps);
    // printf("ans = %.5lf\n", ans);
    printf("%d %d\n", mi + 1, mj + 1);
    
    // check_answer(n, mi, mj);
    return 0;
}
