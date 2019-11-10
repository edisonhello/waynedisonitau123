#include <bits/stdc++.h>
using namespace std;

int main() {
    int64_t l, r, w;
    cin >> l >> r >> w;
    int64_t g = __gcd(r, w);
    r /= g, w /= g, l /= g;
    if (r + w - 2 >= l) cout << "DEADLOCK" << endl;
    else cout << "OK" << endl;
}
