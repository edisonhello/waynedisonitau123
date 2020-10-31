#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int l, n, m; cin >> l >> n >> m;
        priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> p1, p2;
        priority_queue<int, vector<int>, greater<int>> ept;
        
        for (int i = 0; i < n; ++i) {
            int z; cin >> z;
            p1.emplace(z, z);
        }
        for (int i = 0; i < m; ++i) {
            int z; cin >> z;
            p2.emplace(z, z);
            ept.push(z);
        }

        vector<int64_t> ot;
        for (int i = 0; i < l; ++i) {
            auto p = p1.top(); p1.pop();
            ot.push_back(p.first);
            p1.emplace(p.first + p.second, p.second);
        }

        vector<int64_t> it;
        for (int i = 0; i < l; ++i) {
            auto p = p2.top(); p2.pop();
            it.push_back(-p.first);
            p2.emplace(p.first + p.second, p.second);
        }
        reverse(it.begin(), it.end());

        // for (auto i : ot) cerr << i << ' '; cerr << endl;
        // for (auto i : it) cerr << i << ' '; cerr << endl;

        int64_t mxdiff = 0;
        for (int i = 0; i < l; ++i) mxdiff = max(mxdiff, ot[i] - it[i]);

        cout << mxdiff << endl;

    }
}

