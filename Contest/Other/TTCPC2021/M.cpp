#include <bits/stdc++.h>
using namespace std;

#define int int64_t

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int m, n; cin >> m >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    sort(v.begin(), v.end());

    int tor = -1;
    int ans = 0;

    for (int i : v) {
        if (i > tor) {
            ++ans;
            tor = i + m + m;
        }
    }

    cout << ans << endl;
}
