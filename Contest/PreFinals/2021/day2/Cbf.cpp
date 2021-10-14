#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> s(N);
  for (int i = 0; i < N; ++i) cin >> s[i];
  sort(s.begin(), s.end());
  int ans = 0;
  do {
    bool ok = false;
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        for (int k = j + 1; k < N; ++k) {
          ok |= s[i] > s[k] && s[k] > s[j];
        }
      }
    }
    ans += ok;
  } while (next_permutation(s.begin(), s.end()));
  cout << ans << "\n";
}
