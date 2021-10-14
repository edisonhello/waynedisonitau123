#include <iostream>
#include <vector>
using namespace std;

int main() {
  constexpr int kP = 1'000'000'000 + 7;

  vector<int> dv(1'000'000 + 1);
  vector<int> pr;
  for (int i = 2; i <= 1'000'000; ++i) {
    if (!dv[i]) {
      dv[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; i * pr[j] <= 1'000'000; ++j) {
      dv[i * pr[j]] = pr[j];
      if (i % pr[j] == 0) break;
    }
  }
  
  int N;
  cin >> N;
  vector<int> cp(1'000'000 + 1);
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    while (x > 1) {
      int d = dv[x], cnt = 0;
      while (x % d == 0) {
        x /= d;
        cnt++;
      }
      if (cnt & 1) cp[d]++;
    }
  }

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) res = 1LL * res * a % kP;
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  int ans = 1;
  for (int i = 2; i <= 1'000'000; ++i) {
    if (dv[i] == i) {
      ans = 1LL * ans * fpow(i, min(cp[i], N - cp[i])) % kP; 
    }
  }
  cout << ans << "\n";
}
