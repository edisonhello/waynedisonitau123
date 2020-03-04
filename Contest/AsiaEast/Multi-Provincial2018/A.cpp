#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t;
    for (int tt = 1; tt <= t; ++tt) {
        cout << "Case #" << tt << ": ";
        uint64_t ans = 0;
        stack<uint32_t> stk;
        stack<uint32_t> mnt;
        int n, p, q, m; cin >> n >> p >> q >> m;
        uint32_t sa, sb, sc; cin >> sa >> sb >> sc;
        auto rng = [&] () {
            sa ^= (sa << 16);
            sa ^= (sa >> 5);
            sa ^= (sa << 1);
            uint32_t t = sa;
            sa = sb;
            sb = sc;
            sc ^= t ^ sa;
            return sc;
        };
        for (int i = 1; i <= n; ++i) {
            if (rng() % (p + q) < p) {
                uint32_t x = rng() % m + 1;
                stk.push(x);
                if (mnt.empty() || mnt.top() <= x) mnt.push(x);
            } else {
                if (stk.size()) {
                    uint32_t x = stk.top();
                    stk.pop();
                    if (mnt.top() == x) mnt.pop();
                }
            }
            if (mnt.size()) {
                ans ^= (uint64_t) i * mnt.top();
            }
        }
        cout << ans << endl;
    }
}
