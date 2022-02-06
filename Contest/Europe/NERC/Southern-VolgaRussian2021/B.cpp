#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N, A, B;
    cin >> N >> A >> B;
    vector<int> left = {A}, right = {B};
    vector<bool> used(N + 1);
    used[A] = true;
    used[B] = true;
    for (int i = N; left.size() < N / 2 && i > 0; --i) {
      if (i == A || i == B) {
        continue;
      }
      left.push_back(i);
      used[i] = true;
    }
    if (left.size() != N / 2) {
      cout << "-1\n";
      continue;
    }
    for (int i = 1; i <= N; ++i) {
      if (!used[i]) {
        right.push_back(i);
      }
    }
    if (*max_element(right.begin(), right.end()) != B ||
        *min_element(left.begin(), left.end()) != A) {
      cout << "-1\n";
      continue;
    }
    for (int u : left) cout << u << " ";
    for (int u : right) cout << u << " ";
    cout << "\n";
  }
}
