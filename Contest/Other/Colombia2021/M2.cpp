#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  set<int> head;
  for (int i = 0; i < N; ++i) {
    head.insert(i);
  }
  bool cont = true;
  vector<int> to(N);
  vector<int> ans;

  vector<int> uf(N);
  iota(uf.begin(), uf.end(), 0);
  vector<int> base(N);
  for (int i = 0; i < N; ++i) {
    base[i] = i;
  }

  function<int(int)> Find = [&](int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
  };

  for (int i = 0; i < N - 1; ++i) {
    if (!cont || a[i] < 1 || a[i] > N || head.count(a[i] - 1) == 0 || Find(i) == Find(a[i] - 1)) {
      cont = false;
      int g = Find(i);
      head.erase(base[g]);
      int t = *head.begin();
      head.erase(t);
      head.insert(base[g]);
      int x = Find(t);
      uf[g] = x;
      base[x] = base[g];
      ans.push_back(t);
    } else {
      head.erase(a[i] - 1);
      ans.push_back(a[i] - 1);
      int x = Find(i);
      int y = Find(a[i] - 1);
      uf[x] = y;
      base[y] = base[x];
    }
  }
  assert(head.size() == 1);
  ans.push_back(*head.begin());
  for (int u : ans) cout << u + 1 << " ";
  cout << "\n";
  return 0;
}
