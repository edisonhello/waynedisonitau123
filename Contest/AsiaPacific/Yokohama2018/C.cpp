#include <bits/stdc++.h>
using namespace std;

int c[1555555];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int r, s, p; cin >> r >> s >> p;
    while (p--) {
        int x, y; cin >> x >> y;
        int d = (r - x + 1);
        if (y <= s) d += 1 + (s - y);
        else d += (y - s);
        ++c[d];
        // cerr << "to fin d = " << d << endl;
    }
    for (int i = 1; i <= 1555550; ++i) {
        if (c[i] > 1) {
            c[i + 1] += c[i] - 1;
            c[i] = 1;
        }
    }
    int mx = 0;
    for (int i = 1; i <= 1555550; ++i) if (c[i]) mx = i;
    cout << mx << endl;
}
