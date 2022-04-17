#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  while (cin >> N >> M) {
    int64_t ans = 1;
    for (int i = 0; i < M; ++i) {
      int w, u, v;
      cin >> w >> u >> v;
      if (w & 1) {
        ans *= w;
      }
    }
    cout << ans << "\n";
  }
}
