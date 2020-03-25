#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int64_t> f(51);
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= 50; ++i) {
        f[i] = f[i - 1] + f[i - 2];
    }
    int n;
    cin >> n;
    int x = 1e9, y = 1e9;
    for (int i = 1; i + 1 <= 50; ++i) {
        for (int a = 0; a * f[i] <= n; ++a) {
            if ((n - a * f[i]) % f[i + 1] == 0) {
                int b = (n - a * f[i]) / f[i + 1];
                if (a + b < x + y) {
                    x = a;
                    y = b;
                } else if (a + b == x + y && a < x) {
                    x = a;
                    y = b;
                }
            }
        }
    }
    cout << x << ' ' << y << endl;
}

