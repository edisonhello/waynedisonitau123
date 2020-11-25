#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, h, H; cin >> n >> h >> H;
        vector<int> x(n);
        vector<int> c(n);
        for (int i = 0; i < n; ++i) cin >> x[i];
        for (int i = 0; i < n; ++i) cin >> c[i];

        int mnt = INT_MAX, win = -1;

        for (int i = 0; i < n; ++i) {
            int tt = x[i] % (2 * H);
            int add = 0;
            if (h <= tt && tt < 2 * H - h) {
                add = 2 * H - h - tt;
            }
            int t = x[i] + add + c[i];
            if (t < mnt) {
                mnt = t;
                win = i;
            }
        }

        cout << win + 1 << '\n';
    }
}

