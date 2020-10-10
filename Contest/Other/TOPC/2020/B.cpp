#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> get1(int a, int b, int p) {
    if (a <= p && p <= b) {
        return vector<pair<int, int>>{{0, p - a}, {0, b - p}};
    } else if (p <= a) {
        return vector<pair<int, int>>{{a - p, b - p}};
    } else {
        return vector<pair<int, int>>{{p - b, p - a}};
    }
}

int main() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int q; cin >> q;
    while (q--) {
        int p; cin >> p;
        vector<pair<int, int>> segs = get1(a, b, p);
        auto tmp = get1(c, d, p);
        for (auto p : tmp) segs.push_back(p);
        sort(segs.begin(), segs.end());

        vector<pair<int, int>> nseg;
        int nl = -1;
        int nr = -1;
        int ans = 0;
        for (auto &p : segs) {
            if (p.first > nr) {
                ans += nr - nl;
                nl = p.first;
                nr = p.second;
            } else {
                nr = max(nr, p.second);
            }
        }
        ans += nr - nl;

        cout << ans << '\n';;
    }
}
