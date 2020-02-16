#include <bits/stdc++.h>
using namespace std;

int pos[1004][3];

int main() {
    int n; cin >> n;
    int mnh = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> pos[i][0] >> pos[i][1] >> pos[i][2];
        mnh = max(mnh, pos[i][2]);
    }

    int l, r, d, u;
    auto ok = [&] (int H) -> bool {
        l = -400000000, r = 400000000, d = -400000000, u = 400000000;
        for (int i = 1; i <= n; ++i) {
            int dd = H - pos[i][2];
            l = max(l, pos[i][0] - dd);
            r = min(r, pos[i][0] + dd);
            d = max(d, pos[i][1] - dd);
            u = min(u, pos[i][1] + dd);
        }
        return l <= r && d <= u;
    };

    int L = mnh, R = 400000000;
    while (L < R) {
        int M = (L + R) >> 1;
        if (ok(M)) R = M;
        else L = M + 1;
    }
    ok(L);
    cout << l << ' ' << u << ' ' << L << endl;

}

