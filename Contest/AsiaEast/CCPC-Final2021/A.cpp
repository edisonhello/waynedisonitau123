#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  cin >> N >> K;
  vector<string> inst(N);
  vector<string> value(N);
  for (int i = 0; i < N; ++i) {
    cin >> inst[i] >> value[i];
  }
  vector<int> que(N);
  iota(que.begin(), que.end(), 0);
  for (int it = 0; it < que.size(); ++it) {
    int t = que[it];
    if (inst[t] == "echo") {
      cout << value[t];
    } else {
      int m = 0;
      for (int i = 0; i < value[t].size(); ++i) {
        m = m * 10 + (value[t][i] - '0');
      }
      for (int i = 0; i < m && que.size() < K; ++i) {
        que.push_back(i);
      }
    }
  }
  cout << "\n";
}
