#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> deg(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    deg[u]++;
    deg[v]++;
  }
  for (int i = 0; i < N; ++i) {
    if (deg[i] > 3) {
      cout << "0\n";
      return 0;
    }
  }
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    ans += deg[i] <= 2;
  }
  cout << ans << "\n";
}

