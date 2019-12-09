#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long

const ld pi = acos((ld)(-1));

int main() {
    ll n, m; cin >> n >> m;
    cout << fixed << setprecision(20) <<
        sin(pi / m) / sin(pi / n) *
        cos(pi / (n / __gcd(n, m) * m)) / cos(pi / m) << endl;
}
