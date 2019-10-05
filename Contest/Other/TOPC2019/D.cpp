#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    vector<pair<int, int>> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i].first, v[i].second = i + 1;
    map<int, int> cnt;
    for (pair<int, int> p : v) ++cnt[p.first];

    for (auto &p : cnt) if (p.second > n / 2) {
        cout << -1 << endl;
        exit(0);
    }
    while (v.size()) {
        map<int, int> cnt;
        for (pair<int, int> p : v) ++cnt[p.first];
        int fi = v[0].first;
        for (pair<int, int> p : v) if (cnt[p.first] > cnt[fi]) fi = p.first;
        
        for (int i = 0; i < (int)v.size(); ++i) if (v[i].first == fi) {
            int j = (i + 1 == (int)v.size() ? 0 : i + 1);
            if (v[i].first != v[j].first) {
                cout << v[i].second << ' ' << v[j].second << '\n';
                vector<pair<int, int>> vv;
                for (int z = 0; z < (int)v.size(); ++z) {
                    if (z != i && z != j) vv.push_back(v[z]);
                }
                v.swap(vv);
                break;
            }
        }
    }
}
