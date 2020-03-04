#include <bits/stdc++.h>
using namespace std;

long long tot[50];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int k, x; cin >> k >> x;
        int bb = k;
        tot[0] = 1;
        for (int i = 1; i < 50; ++i) tot[i] = tot[i - 1] * bb;
        /* vector<int> ans;
        int dig = 1;
        --x;
        for (; tot[dig] <= x; ++dig) {
            x -= tot[dig];
            ans.push_back(0);
        }
        ans.push_back(0);
        cerr << "x = " << x << endl;
        if (x == 0) {
            for (int i = 0; i < dig - 1; ++i) cout << (10 - k);
            cout << '\n';
            continue;
        }
        int digs = 1;
        for (; tot[digs] < x; ++digs);
        while (digs--) {
            ans[digs + 1] = x / tot[digs];
            x %= tot[digs];
        }
        for (int i : ans) {
            cout << i + (10 - k);
        }
        cout << '\n'; */
    }
}
