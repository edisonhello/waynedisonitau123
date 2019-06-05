#include <bits/stdc++.h>
using namespace std;

int pw[105], fac[105];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n, k, m; cin >> n >> k >> m;
        fac[0] = 1; for (int i = 1; i <= 100; ++i) fac[i] = 1ll * fac[i - 1] * i % m;
        pw[0] = 1; for (int i = 1; i <= 100; ++i) pw[i] = 1ll * pw[i - 1] * (k + 1) % m;
        if (n <= k) { cout << fac[n] << endl; continue; }
        set<vector<int>> st;
        for (int bye = 1; bye <= n - k; ++bye) {
            for (int sz = 0; sz < n - k; ++sz) {
                vector<int> v;
                for (int i = 1; i <= n - k; ++i) {
                    if (i == bye) continue;
                    if (v.size() == sz) v.push_back(bye);
                    v.push_back(i);
                }
                if (v.size() == sz) v.push_back(bye);
                st.insert(v);
            }
        }
        int sum = 0;
        for (const vector<int> &v : st) {
            int f = 0, x = 0;
            for (int i : v) {
                x = max(x, i);
                if (x == i) ++f;
            }
            sum = (sum + 1ll * pw[f - 1] * fac[k + 1]) % m;
        }
        cout << sum << endl;
    }
}
