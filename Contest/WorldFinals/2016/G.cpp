#include <bits/stdc++.h>
using namespace std;

pair<int, int> rev(pair<int, int> p, pair<int, int> cen) {
    int dx = p.first - cen.first;
    int dy = p.second - cen.second;
    return make_pair(cen.first - dx, cen.second - dy);
}

long long cross(const pair<int, int> &a, const pair<int, int> &b) {
    return a.first * 1ll * b.second - a.second * 1ll * b.first;
}

int main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> segs;
    vector<int> weis;
    // vector<pair<int, int>> points;

    for (int i = 0; i < n; ++i) {
        int x0, x1, y; cin >> x0 >> x1 >> y;
        if (x1 < x0) swap(x0, x1);
        segs.emplace_back(x0, x1, y);
        weis.emplace_back(abs(x1 - x0));
    }

    auto go = [&] (const pair<int, int> cent) -> long long {
        // cerr << "cent " << cent.first << ' ' << cent.second << endl;
        int foby = cent.second;
        vector<pair<pair<int, int>, int>> ev;
        for (int i = 0; i < n; ++i) {
            if (get<2>(segs[i]) == foby) continue;
            pair<int, int> pl(get<0>(segs[i]), get<2>(segs[i]));
            pair<int, int> pr(get<1>(segs[i]), get<2>(segs[i]));
            if (get<2>(segs[i]) < foby) {
                tie(pl, pr) = make_pair(rev(pr, cent), rev(pl, cent));
            }
            pair<int, int> d1(pl.first - cent.first, pl.second - cent.second);
            pair<int, int> d2(pr.first - cent.first, pr.second - cent.second);
            if (cross(d1, d2) < 0) swap(d1, d2);
            int w = weis[i];
            ev.emplace_back(d1, w);
            ev.emplace_back(d2, -w);
        }

        sort(ev.begin(), ev.end(), [&] (const pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
                long long x = cross(a.first, b.first);
                if (x == 0) return a.second > b.second;
                return x > 0;
        });

        long long mx = 0;
        long long now = 0;
        for (auto [oo, val] : ev) {
            now += val;
            mx = max(mx, now);
        }
        return mx;
    };

    long long mx = 0;
    for (int i = 0; i < n; ++i) {
        pair<int, int> p1(get<0>(segs[i]), get<2>(segs[i]));
        pair<int, int> p2(get<1>(segs[i]), get<2>(segs[i]));
        mx = max(mx, go(p1) + weis[i]);
        mx = max(mx, go(p2) + weis[i]);
    }

    cout << mx << endl;
}

