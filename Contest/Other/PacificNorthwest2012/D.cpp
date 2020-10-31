#include <bits/stdc++.h>
using namespace std;

int sign(long long x) {
    return x < 0 ? -1 : x > 0 ? 1 : 0;
}

long long crx(pair<int, int> &a, pair<int, int> &b) {
    return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, w, h; while (cin >> n >> w >> h) {
        if (n == 0) break;

        vector<pair<pair<int, int>, pair<pair<int, int>, double>>> v;
        bool atmid = 0;
        for (int i = 0; i < n; ++i) {
            pair<int, int> p;
            cin >> p.first >> p.second;
            if (p.first * 2 == w && p.second * 2 == h) {
                atmid = 1;
                continue;
            }

            pair<int, int> m(p.first * 2 - w, p.second * 2 - h);

            v.emplace_back(p, make_pair(m, atan2(m.second, m.first)));
        }

        sort(v.begin(), v.end(), [&] (pair<pair<int, int>, pair<pair<int, int>, double>> &a, pair<pair<int, int>, pair<pair<int, int>, double>> &b) { return a.second.second < b.second.second; });

        for (int i = 0; i < (int)v.size(); ++i) {
            int j = (i + n / 2 - 1);
            if (j >= v.size()) j -= v.size();
            // [i, j]
            if (sign(crx(v[i].second.first, v[j].second.first)) * 
                sign(crx(v[i].second.first, v[(j + 1) % v.size()].second.first)) <= 0) {
                for (int k = i; k != j; k = (k + 1) % v.size()) {
                    cout << v[k].first.first << ' ' << v[k].first.second << '\n';
                }
                cout << v[j].first.first << ' ' << v[j].first.second << '\n';
                break;
            }
        }


    }
}
