#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, L, n;
    cin >> H >> L >> n;
    vector<int> p(n), v(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> v[i];
    }
    vector<pair<int64_t, int>> ev;
    for (int i = 0; i < n; ++i) {
        int64_t l = p[i] < L ? 0 : (1LL * p[i] * v[i] - 1LL * v[i] * L + H - 1) / H;
        int64_t r = 1LL * p[i] * v[i] / H;
        ev.emplace_back(l, 1);
        ev.emplace_back(r + 1, -1);
    }
    sort(ev.begin(), ev.end());
    int res = 0, cover = 0;
    int64_t pos = 0;
    for (int i = 0, j = 0; i < ev.size(); i = j) {
        while (j < ev.size() && ev[j].first == ev[i].first) {
            cover += ev[j].second;
            j++;
        }
        if (cover > res) {
            res = cover;
            pos = ev[i].first;
        }
    }
    cout << pos << "\n";
    return 0;
}

