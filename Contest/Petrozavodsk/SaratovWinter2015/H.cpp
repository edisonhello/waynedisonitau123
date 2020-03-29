#include <bits/stdc++.h>
using namespace std;

int64_t Cross(pair<int, int> o, pair<int, int> a, pair<int, int> b) {
    a.first -= o.first;
    a.second -= o.second;
    b.first -= o.first;
    b.second -= o.second;
    return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

vector<pair<int, int>> ConvexHull(vector<pair<int, int>> p) {
    sort(p.begin(), p.end());
    vector<pair<int, int>> ch;
    for (int i = 0; i < p.size(); ++i) {
        while (ch.size() >= 2 && Cross(ch[ch.size() - 2], ch[ch.size() - 1], p[i]) <= 0) ch.pop_back();
        ch.push_back(p[i]);
    }
    return ch;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        if (b[i] == 0 && b[j] == 0) return a[i] > a[j];
        if (b[i] == 0) return true;
        if (b[j] == 0) return false;
        return 1LL * a[i] * b[j] > 1LL * a[j] * b[i];
    });
    int m;
    cin >> m;
    vector<pair<int, int>> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    auto ch = ConvexHull(p);
    vector<int64_t> res(n);
    constexpr int64_t kInf = 3'000'000'000'000'000'000;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j + 1 < ch.size() && 1LL * a[ord[i]] * ch[j + 1].first + 1LL * b[ord[i]] * ch[j + 1].second < 1LL * a[ord[i]] * ch[j].first + 1LL * b[ord[i]] * ch[j].second) j++;
        res[ord[i]] = 1LL * a[ord[i]] * ch[j].first + 1LL * b[ord[i]] * ch[j].second;
        // int64_t res = kInf;
        // for (int j = 0; j < ch.size(); ++j) {
        //     res = min(res, (int64_t)(1LL * a[i] * ch[j].first + 1LL * b[i] * ch[j].second));
        // }
        // cout << res << " ";
    }
    for (int i = 0; i < n; ++i) cout << res[i] << " ";
    cout << "\n";
}

