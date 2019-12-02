#include <bits/stdc++.h>
using namespace std;

bool Query(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    string res; cin >> res;
    return res == ">";
}

const int kN = 200 + 5;

int main() {
    srand(clock() + time(0));
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        // vector<int> all(n + n);
        // iota(all.begin(), all.end(), 0);
        // random_shuffle(all.begin(), all.end());
        // // nth_element(od.begin(), od.begin() + n + 1, od.end(), [&](int i, int j) { return Query(i, j); });
        // // cout << "!" << endl;
        // vector<int> v1(all.begin(), all.begin() + n), v2(all.begin() + n, all.end());
        // sort(v1.begin(), v1.end(), Query);
        // sort(v2.begin(), v2.end(), Query);
        // while (n--) {
        //     if (Query(v1.back(), v2.back())) v1.pop_back();
        //     else v2.pop_back();
        // }
        // cout << "!" << endl;
        vector<pair<int, int>> v; // w, l
        for (int i = 1; i <= n + n; i += 2) {
            int q = Query(i, i + 1);
            if (q == 0) v.emplace_back(i + 1, i);
            else v.emplace_back(i, i + 1);
        }
        sort(v.begin(), v.end(), [&] (pair<int, int> &a, pair<int, int> &b) { return Query(a.second, b.second); });
        vector<int> pool;
        for (int i = 1; i < n; ++i) pool.push_back(v[i].first), pool.push_back(v[i].second);
        sort(pool.begin(), pool.end(), Query);
        Query(v[0].second, pool[n - 2]);
        cout << "!" << endl;
    }
}
