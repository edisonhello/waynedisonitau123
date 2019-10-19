#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b, c, d, e, f, g;
        cin >> a >> b >> c >> d >> e >> f >> g;
        if (a * b == e * (f + g) &&
            c * d == (e + f) * g &&
            a - c == b - d)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}
