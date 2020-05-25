#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    vector<int> dv(1'000'000 + 1);
    vector<int> pr;
    for (int i = 2; i <= 1'000'000; ++i) {
        if (!dv[i]) {
            dv[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= 1'000'000; ++j) {
            dv[i * pr[j]] = pr[j];
            if (i % pr[j] == 0) break;
        }
    }
    vector<int> pcnt(1'000'000 + 1);
    for (int u : pr) pcnt[u]++;
    for (int i = 1; i <= 1'000'000; ++i) pcnt[i] += pcnt[i - 1];
    vector<pair<int, int>> x, y;

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        x.clear();
        y.clear();
        for (int t = 1; ; t = a / (a / (t + 1))) {
            x.emplace_back(a / t, t);
            if (t + 1 > a) break;
        }
        for (int t = 1; ; t = b / (b / (t + 1))) {
            y.emplace_back(b / t, t);
            if (t + 1 > b) break;
        }
        reverse(y.begin(), y.end());
        reverse(x.begin(), x.end());
        x.emplace_back(1'000'000, 0);
        y.emplace_back(1'000'000, 0);
        // for (int i = 0; i < x.size(); ++i) {
        //     int p = i + 1 < x.size() ? x[i + 1].first : 1'000'000;
        //     int g = i + 1 < x.size() ? x[i + 1].second : 0;
        //     l.emplace_back(x[i].first + 1, p, g);
        // }
        // for (int i = 0; i < y.size(); ++i) {
        //     int p = i + 1 < y.size() ? y[i + 1].first : 1'000'000;
        //     int g = i + 1 < y.size() ? y[i + 1].second : 0;
        //     r.emplace_back(y[i].first + 1, p, g);
        // }
        int64_t res = 0;
        int p = 2, i = 0, j = 0;
        while (p <= b - a) {
            while (i + 1 < x.size() && x[i + 1].first < p) i++;
            while (j + 1 < y.size() && y[j + 1].first < p) j++;
            // assert(i + 1 < x.size() && j + 1 < y.size());
            int g = y[j + 1].second - x[i + 1].second;
            // if (g == 1) break;
            int nxt = min(x[i + 1].first, y[j + 1].first);
            res += 1LL * (pcnt[nxt] - pcnt[p - 1]) * g * (g - 1) / 2;
            p = nxt + 1;
        }
        cout << res << endl;
    }
}

