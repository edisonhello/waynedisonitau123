#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while (cin >> n) {
        if (!n) break;

        vector<string> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        unordered_map<string, int> pos;
        for (int i = 0; i < n; ++i) pos[a[i]] = i;

        vector<int> bit(n + 2, 0);

        auto add = [&] (int x) {
            for (++x; x <= n; x += x & -x) 
                ++bit[x];
        };

        auto query = [&] (int x) {
            int v = 0;
            for (++x; x; x -= x & -x)
                v += bit[x];
            return v;
        };

        long long ans = 0;
        for (string &s : b) {
            int p = pos[s];
            ans += query(n - 1) - query(p);
            add(p);
        }

        cout << ans << '\n';
    }
}


