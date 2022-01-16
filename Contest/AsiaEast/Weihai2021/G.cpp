#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<int> cnt(M + 1);
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    if (x > M) {
      for (int j = 0; j < M; ++j) {
        cout << "0\n";
      }
      return 0;
    }
    cnt[x]++;
  }
  vector<int> vec;
  for (int i = 0; i <= M; ++i) {
    if (cnt[i] > 0) {
      vec.push_back(i);
    }
  }
  constexpr int kP = 998244353;
  vector<int> fc(M + 1, 1), iv(M + 1, 1);

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  for (int i = 1; i <= M; ++i) {
    fc[i] = 1LL * fc[i - 1] * i % kP;
    iv[i] = fpow(fc[i], kP - 2);
  }

  int mx = vec.back();
  for (int i = 1; i <= M; ++i) {
    if (i < mx) {
      cout << "0\n";
      continue;
    }
    int ans = 1;
    for (int u : vec) {
      int c = 1LL * fc[i] * iv[u] % kP * iv[i - u] % kP;
      ans = 1LL * ans * fpow(c, cnt[u]) % kP;
    }
    cout << ans << "\n";
  }
}

