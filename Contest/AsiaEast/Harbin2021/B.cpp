#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<int> a(N);
  for (int i = 0; i < N; ++i) {
    cin >> a[i];
  }
  vector<int> dp1(N);
  vector<int> dp2(N);
  vector<int> slot(200 + 1);
  int ans = 0;
  for (int s = 2; s <= 200; ++s) {
    int prv = 0;
    fill(slot.begin(), slot.end(), -1E9);
    for (int i = 0; i < N; ++i) {
      dp1[i] = 1 + prv;
      if (s > a[i]) {
        dp2[i] = slot[s - a[i]] + 1;
      } else {
        dp2[i] = -1E9;
      }
      slot[a[i]] = max(slot[a[i]], dp1[i]);
      prv = max(prv, dp2[i]);
    }
    ans = max(ans, prv);
  }
  cout << ans << "\n";
  return 0;
}

