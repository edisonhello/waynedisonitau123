#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, d, k; cin >> n >> d >> k;
    vector<pair<int, string>> v;
    for (int i = 0; i < n; ++i) {
        string s; int c;
        cin >> s >> c;
        v.emplace_back(c, s);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    long long all = 0;
    for (int i = 0; i < k; ++i) {
        all += v[i].first;
    }
    if (all < d) {
        cout << "impossible" << endl;
        return 0;
    }
    all = 0;
    for (int i = 0; i < k; ++i) {
        all += v[i].first;
        if (all >= d) {
            cout << i + 1 << endl;
            for (int j = 0; j <= i; ++j) cout << v[j].second << ", YOU ARE FIRED!" << endl;
            return 0;
        }
    }
    assert(false);
}
