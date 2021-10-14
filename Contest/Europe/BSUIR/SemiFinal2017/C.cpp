#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> cnt(64);
  queue<int> que;

  auto Check = [&](const vector<int> &cnt) {
    vector<int> basis;
    for (int i = 0; i <= 42; ++i) {
      if (cnt[i] > 0) {
        int x = i;
        for (int u : basis) x = min(x, x ^ u);
        if (x > 0) basis.push_back(x);
      }
    }
    int x = 42;
    for (int u : basis) x = min(x, x ^ u);
    return x == 0;
  };

  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    if (s == "+") {
      int x;
      cin >> x;
      cnt[x]++;
      que.push(x);
    } else {
      cnt[que.front()]--;
      que.pop();
    }
    cout << (Check(cnt) ? "Yes" : "No") << "\n";
  }
  return 0;
}
