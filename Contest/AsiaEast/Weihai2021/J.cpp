#include <bits/stdc++.h>
using namespace std;
#define ll int64_t

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    ll a, b;
    cin >> a >> b;
    ll g = __gcd(a, b);
    a /= g;
    b /= g;

    cout << b * (lcm(2 * a, 360) / (2 * a)) - 1 << '\n';
    
  }
}

