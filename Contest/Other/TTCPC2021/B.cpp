#include <bits/stdc++.h>
using namespace std;

#define ll int64_t

int main() {
    ll W, H, w, h; cin >> W >> H >> w >> h;
    ll x = W - w;
    ll y = H - h;
    ll d = __gcd(x, y);
    cout << x / d + y / d - 2 << ' ' << x / d * y << endl;
}
