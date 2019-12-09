#include <bits/stdc++.h>
using namespace std;

int f[1000006];

int main() {
    int n; cin >> n;
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (i % 3 == 0) f[i] = f[i / 3];
        else if (i % 3 == 1) f[i] = 1;
        else f[i] = -1;
    }

    // int sum = 0, mx = 0;
    // for (int i = 1; i <= n; ++i) {
    //     sum += f[i];
    //     assert(abs(sum) <= 20);
    //     mx = max(mx, abs(sum));
    // }

    // cout << mx << endl;
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << f[i];
    }
    cout << endl;
}
