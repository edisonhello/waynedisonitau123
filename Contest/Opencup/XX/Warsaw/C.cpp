#include <bits/stdc++.h>
using namespace std;

int mp[2005][2005];
int qTime, n;
int xl, xr, yl, yr;
int bmax;
int bx, by;

int rnd(int l, int r) {
    // TODO remove this
    return rand() % (r - l + 1) + l;
}

#ifdef DEBUG
int _mp[2005][2005];
void init() {
    set<int> st;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        // int x = rand() % 1000000000 + 1;
        int x = i * 10000 + j;
        while (st.count(x)) x = rand() % 1000000000 + 1;
        st.insert(x);
        _mp[i][j] = x;
    }
}
#endif

void answer(int x, int y) {
#ifdef DEBUG
    int mx = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) mx = max(mx, _mp[i][j]);
    assert(mx == _mp[x][y]);
#else
    cout << "! " << x << " " << y << endl;
#endif
    exit(0);
}

vector<pair<int, int>> _useful;

int ask(int x, int y) {
    if (!(x >= 1 && x <= n && y >= 1 && y <= n)) return 0;
    if (mp[x][y]) return mp[x][y]; // asked
    if (qTime == 3 * n + 210) {
        int mx = 0;
        for (auto p : _useful) { mx = max(mx, mp[p.first][p.second]); }
        for (auto p : _useful) if (mp[p.first][p.second] == mx) answer(p.first, p.second);
    }
    ++qTime;
    _useful.emplace_back(x, y);
    // cerr << "First time ask " << x << " " << y << endl;
#ifdef DEBUG
    mp[x][y] = _mp[x][y];
#else
    cout << "? " << x << " " << y << endl; 
    cin >> mp[x][y];
#endif
    return mp[x][y];
}

void update_boarder(int xl, int xr, int yl, int yr) {
    // cerr << "update_boarder start" << endl;
    // cerr << "xl xr yl yr = " << xl << " " << xr << " " << yl << " " << yr << endl;
    bx = 0, by = 0;
    bmax = -1;
    for (int x = xl; x <= xr; ++x) {
        if (ask(x, yl) > bmax) {
            bmax = ask(x, yl);
            bx = x, by = yl;
        }
        if (ask(x, yr) > bmax) {
            bmax = ask(x, yr);
            bx = x, by = yr;
        }
    }
    for (int y = yl; y <= yr; ++y) {
        if (ask(xl, y) > bmax) {
            bmax = ask(xl, y);
            bx = xl, by = y;
        }
        if (ask(xr, y) > bmax) {
            bmax = ask(xr, y);
            bx = xr, by = y;
        }
    }
    // cerr << "update_boarder end" << endl;
}


int main() {
    cin >> n;
#ifdef DEBUG
    init();
#endif
    if (n * n <= 3 * n + 210) {
        int mx = 0;
        int ax = -1, ay = -1;
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
            if (ask(i, j) > mx) {
                mx = ask(i, j);
                ax = i, ay = j;
            }
        }
        answer(ax, ay);
    }

    xl = 0, xr = n + 1, yl = 0, yr = n + 1;
    bmax = 0;
    bx = 0, by = 0;

    while (true) {
        if (xl == xr && yl == yr) answer(xl, xr);
        int xm = (xl + xr) >> 1;
        // cerr << "start split x at xm = " << xm << endl;
        // cerr << "xl = " << xl << ", xr = " << xr << endl;
        update_boarder(xl, xr, yl, yr);
        for (int y = yl; y <= yr; ++y) {
            if (ask(xm, y) > bmax) {
                bmax = ask(xm, y);
                bx = xm, by = y;
            }
        }
        // cerr << "bx = " << bx << ", by = " << by << endl;
        // cerr << "check useful" << endl;
        bool ok = false;
        // cerr << "ok = " << ok << ", xl xr yl yr = " << xl << " " << xr << " " << yl << " " << yr << endl;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x = bx + dx, y = by + dy;
                if (ok) continue;
                if (x < xl || x > xr || y < yl || y > yr) continue;
                if (ask(x, y) > bmax) {
                    if (x < xm) xr = xm;
                    else xl = xm;
                    ok = true;
                    break;
                }
            }
        }
        // cerr << "ok = " << ok << ", xl xr yl yr = " << xl << " " << xr << " " << yl << " " << yr << endl;
        if (!ok) break;




        

        int ym = (yl + yr) >> 1;
        // cerr << "start split y at ym = " << ym << endl;
        // cerr << "yl = " << yl << ", yr = " << yr << endl;
        update_boarder(xl, xr, yl, yr);
        for (int x = xl; x <= xr; ++x) {
            if (ask(x, ym) > bmax) {
                bmax = ask(x, ym);
                bx = x, by = ym;
            }
        }
        // cerr << "bx = " << bx << ", by = " << by << endl;
        ok = false;
        // cerr << "ok = " << ok << ", xl xr yl yr = " << xl << " " << xr << " " << yl << " " << yr << endl;
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int x = bx + dx, y = by + dy;
                if (ok) continue;
                if (x < xl || x > xr || y < yl || y > yr) continue;
                if (ask(x, y) > bmax) {
                    if (y < ym) yr = ym;
                    else yl = ym;
                    ok = true;
                    break;
                }
            }
        }
        // cerr << "ok = " << ok << ", xl xr yl yr = " << xl << " " << xr << " " << yl << " " << yr << endl;
        if (!ok) break;
    }

    // cerr << "out!" << endl;

    answer(bx, by);
}
