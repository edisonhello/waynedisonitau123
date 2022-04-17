#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<vector<int>> g(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  if (N == 1) {
    cout << 0 << "\n";
    return 0;
  }
  deque<int> vec;
  for (int i = 0; i < N; ++i) {
    if (g[i].size() & 1) {
      vec.push_back(i);
    }
  }
  vector<int> deg(N);
  vector<int> ans;
  while (!vec.empty()) {
    int x = vec.front();
    vec.pop_front();
    cout << x << " ";
    for (int u : g[x]) {
      ++deg[u];
      if (deg[u] * 2 == g[u].size()) {
        vec.push_front(u); 
      }
    }
  }
  cout << "\n";
}
