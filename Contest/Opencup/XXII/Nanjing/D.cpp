#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      cin >> A[i];
      A[i]--;
    }
    vector<int> fw(N + 1);

    auto Update = [&](int p) {
      for (int i = p + 1; i <= N; i += i & -i) {
        fw[i]++;
      }
    };

    auto Query = [&](int p) {
      int res = 0;
      for (int i = p + 1; i > 0; i -= i & -i) {
        res += fw[i];
      }
      return res;
    };

    int64_t ans = 0;
    vector<int> cnt(N);
    cout << "0";
    vector<vector<int>> pos(N);
    pos[A[0]].push_back(0);
    Update(A[0]);
    int best = A[0];
    for (int i = 1; i < N; ++i) {
      if (A[i] > best) {
        if (pos[best].size() >= 2) {
          ans += 2 + i - pos[best][1];
        } else {
          ans += 2;
        }
        best = A[i];
      } else {
        ans += Query(N - 1) - Query(A[i]);
      }
      if (pos[A[i]].empty()) {
        Update(A[i]);
      }
      pos[A[i]].push_back(i);
      cout << " " << ans;
    }
    cout << "\n";
  }
}

