#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int W, L;
    cin >> W >> L;
    vector<int> vec;
    for (int g : {__gcd(W - 1, L - 1), __gcd(W - 2, L), __gcd(W, L - 2), __gcd(__gcd(L - 1, W), W - 2), __gcd(__gcd(W - 1, L), L - 2)}) {
      for (int i = 1; i * i <= g; ++i) {
        if (g % i == 0) {
          vec.push_back(i);
          vec.push_back(g / i);
        }
      }
    }
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    cout << vec.size();
    for (int u : vec) cout << " " << u;
    cout << "\n";
  }
}

