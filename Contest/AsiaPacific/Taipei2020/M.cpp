#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        set<int> sn, sm;
        for (int i = 0; i < n; ++i) {
            int t; cin >> t; sn.insert(t);
        }
        for (int i = 0; i < m; ++i) {
            int t; cin >> t; sm.insert(t);
        }

        int cnt = 0;
        for (int z = 0; z < (1 << 4); ++z) {
            set<int> ssn, ssm;
            for (int i = 0; i < 4; ++i) if (z & (1 << i)) {
                ssn.insert(!!(i & 2));
                ssm.insert(i & 1);
            }

            if (sn == ssn && sm == ssm) {
                ++cnt;
            }
        }
        cout << cnt << '\n';
    }

}
