#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, K, M;
  cin >> N >> K >> M;
  vector<int> deg(N);
  vector<vector<int>> g(N);
  for (int i = 0; i < M; ++i) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    deg[y]++;
  }
  vector<int> C(N * K);
  vector<vector<int>> pos(N);
  for (int i = 0; i < N * K; ++i) {
    cin >> C[i];
    C[i]--;
    pos[C[i]].push_back(i);
  }
  for (int i = 0; i < N; ++i) {
    reverse(pos[i].begin(), pos[i].end());
  }
  vector<int> tdeg(N);
  vector<int> ans(N * K);
  for (int i = 0; i < K; ++i) {
    copy(deg.begin(), deg.end(), tdeg.begin());
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int j = 0; j < N; ++j) {
      if (tdeg[j] == 0) {
        assert(!pos[j].empty());
        pq.push(pos[j].back());
        pos[j].pop_back();
      }
    }
    while (!pq.empty()) {
      int p = pq.top();
      pq.pop();
      ans[p] = i;
      int x = C[p];
      for (int u : g[x]) {
        if (--tdeg[u] == 0) {
          assert(!pos[u].empty());
          pq.push(pos[u].back());
          pos[u].pop_back();
        }
      }
    }
  }
  for (int i = 0; i < N * K; ++i) cout << ans[i] + 1 << " ";
  cout << "\n";
}
