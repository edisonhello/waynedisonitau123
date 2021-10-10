#include <bits/stdc++.h>
using namespace std;


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  vector<tuple<int, int, int, int>> evs;
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    evs.emplace_back(x1, 1, y1, 0);
    evs.emplace_back(x1, 1, y2, 0);
    evs.emplace_back(x2, -1, y1, 0);
    evs.emplace_back(x2, -1, y2, 0);
    evs.emplace_back(x1, 0, y1 + 1, y2 - 1);
    evs.emplace_back(x2, 0, y1 + 1, y2 - 1);
  }

  sort(evs.begin(), evs.end());

  set<int> st;
  for (auto [x, type, y1, y2] : evs) {
    if (type == 1) {
      st.insert(y1);
    } else if (type == -1) {
      st.erase(y1);
    } else {
      auto it = st.lower_bound(y1);
      auto it2 = st.upper_bound(y2);
      if (it != it2) {
        cout << 1 << endl;
        exit(0);
      }
    }
  }

  cout << 0 << endl;
}

