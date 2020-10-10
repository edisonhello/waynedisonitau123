#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, q, r; cin >> p >> q >> r;
    int s = p + r - q;
    if (s <= 0) {
        cout << -1 << endl;
        exit(0);
    }
    int a = 5 * p + r + s - 3 * q;
    int b = 5 * p + r + q - 3 * s;
    int c = (p + q + r + s) * 2;
    int g1 = __gcd(c, a);
    int g2 = __gcd(b, c);
    int aa = a / g1, bb = c / g1, cc = b / g2, dd = c / g2;
    if (aa <= 0 || aa >= bb) {
        cout << -1 << endl;
        exit(0);
    }
    if (cc <= 0 || cc >= dd) {
        cout << -1 << endl;
        exit(0);
    }
    cout << a / g1 << "/" << c / g1 << " " << b / g2 << "/" << c / g2 << endl;
}
