#include <bits/stdc++.h>
using namespace std;


int main() {
    int n, X, Y; cin >> n >> X >> Y;
    vector<pair<int, int>> seg;
    while (n--) {
        int x, y; cin >> x >> y;
        char c; cin >> c;

        pair<int, int> p;
        if (c == 'E') {
            {
                int d = X - x;
                if (y - d < 0) {
                    d = y;
                    p.first = x + d;
                } else p.first = X + y - d;
            }
            {
                int d = X - x;
                if (y + d > Y) {
                    d = Y - y;
                    p.second = X + Y + (X - (x + d));
                } else p.second = X + y + d;
            }
        } else if (c == 'N') {
            {
                int d = X - x;
                if (y + d > Y) {
                    d = Y - y;
                    p.first = X + Y + (X - (x + d));
                } else p.first = X + y + d;
            }
            {
                if (y + x > Y) {
                    p.second = X + Y + (X - (x - (Y - y)));
                } else p.second = X + Y + X + (Y - (y + x));
            }
        } else if (c == 'W') {
            {
                if (y + x > Y) {
                    p.first = X + Y + (X - (x - (Y - y)));
                } else p.first = X + Y + X + (Y - (y + x));
            }
            {
                if (y - x < 0) {
                    p.second = x - y;
                } else p.second = X + Y + X + (Y - (y - x));
            }
        } else {
            {
                if (y - x < 0) {
                    p.first = x - y;
                } else p.first = X + Y + X + (Y - (y - x));
            }
            {
                int d = X - x;
                if (y - d < 0) {
                    d = y;
                    p.second = x + d;
                } else p.second = X + y - d;
            }
        }

        if (p.second < p.first) p.second += X + X + Y + Y;
        seg.push_back(p);
        // cout << "seg add " << p.first << '-' << p.second << endl;
    }

    auto moveprv = [&] (pair<int, int> x) { x.first -= X + X + Y + Y, x.second -= X + X + Y + Y; return x; };
    auto movenxt = [&] (pair<int, int> x) { x.first += X + X + Y + Y, x.second += X + X + Y + Y; return x; };
    auto is_inside = [&] (pair<int, int> big, pair<int, int> small) {
        return big.first <= small.first && small.second <= big.second;
    };
    auto is_cover = [&] (pair<int, int> big, pair<int, int> small) {
        return is_inside(big, small) ||
               is_inside(big, moveprv(small)) ||
               is_inside(big, movenxt(small));
    };
    auto include = [&] (pair<int, int> p, int x) {
        return p.first <= x && x <= p.second; 
    };

    int mn = 1e9;
    vector<pair<int, int>> tmp;
    for (int i = 0; i < (int)seg.size(); ++i) {
        int yes = true;
        for (int j = 0; j < (int)seg.size(); ++j) if (i != j) {
            if (is_cover(seg[i], seg[j])) yes = false;
            // if (seg[j].first <= seg[i].first && seg[i].second <= seg[j].second) yes = false;
        }
        if (yes) tmp.push_back(seg[i]);
    }

    // cerr << "tmp size = " << tmp.size() << endl;
    // cerr << "tmp = "; for(auto p : tmp) cerr << p.first << "," << p.second << ";"; cerr << endl;

    for (int i = 0; i < (int)tmp.size(); ++i) {
        seg.clear();

        int cR = tmp[i].second;
        for (auto &p : tmp) {
            if (include(p, cR) || include(moveprv(p), cR) || include(movenxt(p), cR)) continue;
            seg.push_back(p);
        }

        for (auto &p : seg) {
            while (p.first < cR) p.first += X + X + Y + Y;
            while (p.second < cR) p.second += X + X + Y + Y;
            if (p.second < p.first) p.second += X + X + Y + Y;
        }

        sort(seg.begin(), seg.end());

        int aa = 1;
        for (auto &p : seg) {
            if (p.first <= cR) continue;
            cR = p.second;
            ++aa;
        }

        mn = min(mn, aa);
    }

    cout << mn << endl;
}


