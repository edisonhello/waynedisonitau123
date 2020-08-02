#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; cin >> n;
  vector<pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end());
  vector<int> have;
  vector<int> add;
  int p; cin >> p;
  for (int i = 0; i < p; ++i) {
    int x; cin >> x;
    have.push_back(x);
  }
  sort(have.begin(), have.end());

  for (int i = 0; i < n; ++i) {

    auto Exist = [&] (int x) {
      for (int i : add) if (i == x) return true;
      for (int i : have) if (i == x) return true;
      return false;
    };

    auto PutEmpty = [&] () {
      for (int j = a[i].first + 1; j <= a[i].second; ++j) if (!Exist(j)) {
        add.push_back(j);
        return;
      }
      assert(0);
    };

    int now = 0;
    for (int j : have) if (a[i].first <= j && j <= a[i].second) ++now;
    for (int j : add) if (a[i].first <= j && j <= a[i].second) ++now;
    if (now > 2) {
      cout << "impossible" << endl;
      exit(0);
    }
    if (now == 2) continue;
    if (now == 0) { PutEmpty(); ++now; }

    if (i != n - 1 && a[i].second == a[i + 1].first && !Exist(a[i].second)) {
      int nxt = 0;
      for (int j : have) if (a[i + 1].first <= j && j <= a[i + 1].second) ++nxt;
      for (int j : add) if (a[i + 1].first <= j && j <= a[i + 1].second) ++nxt;
      if (nxt < 2) {
        add.push_back(a[i].second);
      } else {
        PutEmpty(); 
      }
    } else {
      PutEmpty(); ++now;
    }
  }

  sort(add.begin(), add.end());
  cout << add.size() << endl;
  for (int i : add) cout << i << ' ';
  cout << endl;
}
