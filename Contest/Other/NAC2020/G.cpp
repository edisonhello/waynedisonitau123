#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, p, q;
    cin >> n >> p >> q;
    int s;
    cin >> s;
    vector<int> x(p), y(q);
    for (int i = 0; i < p; ++i) cin >> x[i];
    for (int i = 0; i < q; ++i) cin >> y[i];
    sort(x.rbegin(), x.rend());
    int res = 1'000'000'000 + 1;
    for (int d = 30; d >= 0; --d) {
        if (res - (1 << d) < 0) continue;
        multiset<int> st(y.begin(), y.end());
        int got = 0;
        int g = res - (1 << d);
        for (int i = 0; i < p; ++i) {
            int up = min(s - x[i], x[i] + g);
            auto it = st.upper_bound(up);
            if (it != st.begin()) {
                if (*prev(it) >= x[i] - g) {
                    st.erase(prev(it));
                    got++;
                }
            }
        }
        if (got >= n) res -= (1 << d);
    }
    if (res == 1'000'000'000 + 1) res = -1;
    cout << res << "\n";
    return 0;
}


