#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> s(n + 1);
    const int kM = (1 << 20);
    vector<int> f(kM, n + 1);
    f[0] = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s[i + 1] = s[i] ^ a[i];
        f[s[i + 1]] = min(f[s[i + 1]], i + 1);
    }
    for (int s = kM - 1; s >= 0; --s) {
        for (int i = 0; i < 20; ++i) {
            if ((s >> i & 1) == 0) {
                f[s] = min(f[s], f[s ^ (1 << i)]);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        int res = 0;
        for (int j = 19; j >= 0; --j) {
            if ((s[i] >> j & 1) == 0 && f[res | (1 << j)] <= i) {
                res |= (1 << j);
            }
        }
        cout << 2 * res + s[i] << " ";
    }
    cout << "\n";
    return 0;
}

