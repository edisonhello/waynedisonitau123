#include <bits/stdc++.h>
using namespace std;

double dist(pair<int, int> &a, pair<int, int> &b) {
    return hypot((double)a.first - b.first, (double)a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int z; cin >> z; while (z--) {
        int n; cin >> n;
        vector<pair<int, int>> v(n), u(n);
        for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
        for (int i = 0; i < n; ++i) cin >> u[i].first >> u[i].second;
        sort(u.begin(), u.end());

        vector<pair<int, int>> ans;
        double nowd = 1e20;
        do {
            double sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += dist(v[i], u[i]);
            }

            if (sum < nowd) {
                nowd = sum;
                ans = u;
            }
        } while (next_permutation(u.begin(), u.end()));

        for (int i = 0; i < n; ++i) {
            cout << 2 << '\n';
            cout << v[i].first << ' ' << v[i].second << '\n';
            cout << ans[i].first << ' ' << ans[i].second << '\n';
        }
    }
}

