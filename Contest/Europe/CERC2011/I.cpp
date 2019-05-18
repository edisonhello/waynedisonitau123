#include <bits/stdc++.h>
using namespace std;

int a[1000006],okR[1000006], who[1000006];
vector<int> app[1000006];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, q; while (cin >> n >> q) {
        if (n == 0 && q == 0) break;
        vector<int> num; num.reserve(n);
        for (int i = 1; i <= n; ++i) cin >> a[i], num.push_back(a[i]);
        sort(num.begin(), num.end());
        num.resize(unique(num.begin(), num.end()) - num.begin());
        for (int i = 1; i <= n; ++i) a[i] = upper_bound(num.begin(), num.end(), a[i]) - num.begin();
        for (int i = 1; i <= n; ++i) app[i].clear();
        for (int i = 1; i <= n; ++i) app[a[i]].push_back(i);
        okR[n] = n + 1;
        for (int i = n - 1; i >= 1; --i) {
            okR[i] = okR[i + 1];
            who[i] = who[i + 1];
            auto it = upper_bound(app[a[i]].begin(), app[a[i]].end(), i);
            if (it == app[a[i]].end());
            else if (*it - 1 <= okR[i]) who[i] = a[i], okR[i] = *it - 1;
        }
        while (q--) {
            int l, r; cin >> l >> r;
            if (r <= okR[l]) cout << "OK\n";
            else cout << num[who[l] - 1] << '\n';
        }
        cout << '\n';
    }
}
