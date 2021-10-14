#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; cin >> n;
  long long tot = 0;
  while (n--) {
    long long pog = 0;
    int k; cin >> k;
    vector<pair<long long, long long>> p(k);
    for (auto &[x, y] : p) cin >> x >> y;
    for (int i = 0; i < k; ++i) {
      int j = i == k - 1 ? 0 : i + 1;
      pog += p[i].first * p[j].second - p[i].second * p[j].first;
    }
    tot += abs(pog);
  }

  cout << (tot / 2) << endl;
}
