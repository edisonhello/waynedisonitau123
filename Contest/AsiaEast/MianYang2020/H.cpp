#include <bits/stdc++.h>
using namespace std;

// long long BF(long long x, long long y, long long z) {
//     int ans = 0;
//     for (int i = -20; i <= 20; ++i) {
//         for (int j = -20; j <= 20; ++j) {
//             for (int s = -20; s <= 20; ++s) {
//                 for (int t = -20; t <= 20; ++t) {
//                     if (abs(i) + abs(j) == x && abs(s) + abs(t) == y) {
//                         if (abs(i - s) + abs(j - t) == z) {
//                             ++ans;
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     return ans;
// }

int main() {
    int t, T = 0; cin >> t; while (t--) {
        long long x, y, z; cin >> x >> y >> z;
        vector<long long> v{x, y, z};
        sort(v.begin(), v.end());
        x = v[0], y = v[1], z = v[2];

        cout << "Case #" << (++T) << ": ";
        if ((x + y + z) & 1) {
            cout << 0 << '\n';
            continue;
        }
        if (x == 0 && y == 0 && z == 0) {
            cout << 1 << '\n';
            continue;
        }
        if (z > x + y) {
            cout << 0 << '\n';
            continue;
        }

        long long ans = -1;
        if (x + y != z) {
            ans = 4 * (x + y + z);
        } else {
            ans = 4 * (x + 1) * (y + 1) - 4;
        }
        cout << ans << '\n';

        // long long bf = BF(x, y, z);
        // cerr << bf << endl;

        // if (ans != bf) {
        //     cerr << "x y z " << x << ' ' << y << ' ' << z << endl;
        // }

        // assert(ans == bf);
    }
}

