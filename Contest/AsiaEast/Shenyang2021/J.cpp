#include <bits/stdc++.h>
using namespace std;
#define left lakdsjf

int rec[100005];
int vis[100005];

vector<int> base = {1, 10, 100, 1000, 10000};

  auto GetVal = [](const int &val, int i) { return (val / base[i]) % 10; };

  auto Decrease = [](int &vv, int i, int x) {
    // cout << "dec " << vv << ' ' << i << ' ' << x << ' ';
    int ii = GetVal(vv, i);
    int to = (ii - x + 10) % 10;
    vv -= base[i] * ii;
    vv += base[i] * to;
    // cout << " bec " << vv << endl;
  };

  auto Increase = [](int &vv, int i, int x) {
    return Decrease(vv, i, 10 - x);
  };

void init() {
  queue<int> q;
  q.push(0);
  vis[0] = 1;

  while (q.size()) {
    int now = q.front();
    q.pop();

    for (int i = 0; i < 5; ++i) for (int j = 0; j < 5; ++j) if (i != j) {
      int nx = now;
      Increase(nx, i, 1);
      Decrease(nx, j, 1);
      if (vis[nx]) continue;
      vis[nx] = 1;
      q.push(nx);
      rec[nx] = rec[now] + 1;
    }
  }
}

int dfs(int val) {
  assert(vis[val]);
  return rec[val];
  if (val == 0) return 0;
  if (vis[val]) {
    return rec[val];
  }

  vis[val] = true;

  int mn = 1e9;


  for (int i = 0; i < 5; ++i) {
    if (GetVal(val, i) == 0) continue;
    for (int j = 0; j < 5; ++j) {
      if (i == j || GetVal(val, j) == 0) continue;

      int vv = val;
      int ii = GetVal(vv, i);
      int jj = GetVal(vv, j);

      Increase(vv, i, jj);
      Decrease(vv, j, jj);

      mn = min(mn, dfs(vv) + jj);
    }
  }

  // cout << "get val " << val << " ans " << mn << endl;

  return rec[val] = mn;
}

int solve() {
  string s, t;
  cin >> s >> t;
  vector<int> diff = {0};
  for (int i = 0; i < 4; ++i) {
    int d(t[i] - s[i]);
    if (d < 0) d += 10;
    diff.push_back(d);
  }
  diff.push_back(0);

  vector<int> cha;
  for (int i = 1; i < (int)diff.size(); ++i) {
    cha.push_back(diff[i] - diff[i - 1]);
    if (cha.back() < 0) cha.back() += 10;
  }

  int val = 0;
  for (int i : cha) val = val * 10 + i;

  return dfs(val);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  init();
  int t;
  cin >> t;
  while (t--) cout << solve() << '\n';
}

