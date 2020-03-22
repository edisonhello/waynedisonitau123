#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<uint32_t>> v(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            string s;
            cin >> s;
            uint32_t mask = 0;
            for (int k = 0; k < s.size(); ++k) {
                mask |= (1U << (s[k] - 'a'));
            }
            v[i].push_back(mask);
        }
    }
    vector<vector<int>> res(n, vector<int>(n, -1));
    for (int p = 0; p < n; ++p) {
        res[p][p] = 0;
        uint32_t mask = (1 << p);
        int dist = 1;
        while (true) {
            bool found = false;
            uint32_t nmask = mask;
            for (int i = 0; i < n; ++i) {
                if (mask >> i & 1) continue;
                for (uint32_t u : v[i]) {
                    if ((u & mask) == u) {
                        found = true;
                        nmask |= (1 << i);
                        res[i][p] = dist;
                    }
                }
            }
            mask = nmask;
            dist++;
            if (!found) break;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << res[i][j] << " ";
        cout << endl;
    }
}

