#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    constexpr int kM = 100'000;
    constexpr int kB = 100;
    vector<bitset<kM>> pf;
    for (int i = 0; i < n; i += kB) {
        bitset<kM> b;
        for (int j = 0; j < kB && i + j < n; ++j) b.flip(a[i + j]);
        if (pf.empty()) pf.push_back(b);
        else pf.push_back(pf.back() ^ b);
    }
    while (true) {
        int q;
        cin >> q;
        if (q == 0) break;
        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if (t == 1) {
                int x, y;
                cin >> x >> y;
                x--, y--;
                for (int j = x / kB; j < pf.size(); ++j) {
                    pf[j].flip(a[x]);
                    pf[j].flip(y);
                }
                a[x] = y;
            } else {
                int l, r;
                cin >> l >> r;
                l--, r--;
                bitset<kM> res;
                if (l / kB == r / kB) {
                    for (int i = l; i <= r; ++i) res.flip(a[i]);
                } else {
                    res = pf[r / kB - 1] ^ pf[l / kB];
                    for (int i = l; i < (l / kB + 1) * kB; ++i) res.flip(a[i]);
                    for (int i = (r / kB) * kB; i <= r; ++i) res.flip(a[i]);
                }
                if (res.count() == 0) cout << -1 << endl;
                else cout << res._Find_first() + 1 << endl;
            }
        }
    }
    return 0;
}

