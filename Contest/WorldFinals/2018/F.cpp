#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<string> s(N);
  int L = 0;
  for (int i = 0; i < N; ++i) {
    cin >> s[i];
    L = max(L, static_cast<int>(s[i].size()));
  }
  int ans = 0, opt = -1;
  while (true) {
    vector<int> dp(L), nxt(L);
    int cnt = 0;
    // cout << "L = " << L << endl;
    for (int i = 0; i < N; ) {
      cnt++;
      int width = s[i].size();
      fill(nxt.begin(), nxt.end(), 0);
      int j = i;
      // cout << "i = " << i << endl;
      while (j + 1 < N && width + 1 + s[j + 1].size() <= L) {
        // cout << "blank row = " << cnt << " col = " << width << endl;
        nxt[width] = dp[width] + 1;
        if (width > 0) {
          nxt[width] = max(nxt[width], dp[width - 1] + 1);
        }
        if (width + 1 < L) {
          nxt[width] = max(nxt[width], dp[width + 1] + 1);
        }
        if (nxt[width] > ans) {
          ans = nxt[width];
          opt = L;
        }
        width += 1 + s[j + 1].size();
        j++;
      }
      // while (width < L) {
      //   cout << "blank row = " << cnt << " col = " << width << endl;
      //   nxt[width] = dp[width] + 1;
      //   if (width > 0) {
      //     nxt[width] = max(nxt[width], dp[width - 1] + 1);
      //   }
      //   if (width + 1 < L) {
      //     nxt[width] = max(nxt[width], dp[width + 1] + 1);
      //   }
      //   if (nxt[width] > ans) {
      //     ans = nxt[width];
      //     opt = L;
      //   }
      //   width++;
      // }
      dp.swap(nxt);
      i = j + 1;
    }
    // cout << "L = " << L << " cnt = " << cnt << " ans = " << ans << endl;
    if (cnt <= ans) {
      break;
    }
    L++;
  }
  cout << opt << " " << ans << "\n";
}

