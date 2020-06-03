#include <bits/stdc++.h>
using namespace std;

vector<int> xs[100005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int X, Y; cin >> X >> Y;
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) {
    int x, y; cin >> x >> y;
    xs[x].push_back(y);
  }
  deque<int> ls, rs;
  long long vals = 0;
  int down = 0, up = 0;
  for (int i = 0; i <= X; ++i) {
    if (xs[i].empty()) continue;
    sort(xs[i].begin(), xs[i].end());
    ls.push_back(xs[i][0]);
    rs.push_back(xs[i].back());
    vals += xs[i].back() * 2;
    ++down;
  }
  sort(ls.begin(), ls.end());
  sort(rs.begin(), rs.end());

  long long mn = LLONG_MAX;

  for (int i = 0; i <= Y; ++i) {
    mn = min(mn, vals);
    while (ls.size() && ls[0] == i) {
      ls.pop_front();
      --down;
    }
    while (rs.size() && rs[0] == i) {
      rs.pop_front();
      ++up;
    }
    vals -= down * 2;
    vals += up * 2;
    mn = min(mn, vals);
  }

  cout << mn + X - 1 << endl;
  


}
