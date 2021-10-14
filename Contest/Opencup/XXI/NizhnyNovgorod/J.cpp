#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    A[i]--;
  }
  for (int i = 0; i < N; ++i) {
    cin >> B[i];
    B[i]--;
  }
  vector<tuple<int, int, int>> ans;
  ans.emplace_back(0, N - 1, 0);
  sort(A.begin(), A.end());
  for (int i = 0; i < N - 1; ++i) {
    bool is_max = true, is_min = true;
    int p = -1;
    for (int j = i; j < N; ++j) {
      if (A[j] == B[i]) {
        p = j;
        break;
      }
    }
    for (int j = i; j <= p; ++j) {
      is_max &= B[i] >= A[j];
      is_min &= B[i] <= A[j];
    }
    assert(is_max || is_min);
    if (is_max) {
      ans.emplace_back(i, p, 1);
      sort(A.begin() + i, A.begin() + p + 1, greater<int>());
    } else {
      ans.emplace_back(i, p, 0);
      sort(A.begin() + i, A.begin() + p + 1);
    }
  }
  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); ++i) {
    cout << get<0>(ans[i]) + 1 << " " << get<1>(ans[i]) + 1 << " " << (get<2>(ans[i]) ? "D" : "I") << "\n";
  }
}
