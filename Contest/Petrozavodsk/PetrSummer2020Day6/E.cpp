#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t; while (t--) {
    int n, m, k; cin >> n >> m >> k;
    if (2 * k > m) cout << "Yuto" << '\n';
    else if ((n * m) % 2 == 1) cout << "Yuto" << '\n';
    else cout << "Platina" << '\n';
  }

}
