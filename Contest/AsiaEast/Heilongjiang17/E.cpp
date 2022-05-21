#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> b(N);
  constexpr int kC = 200'000;
  vector<int> dv(kC + 1);
  vector<int> primes;
  for (int i = 2; i <= kC; ++i) {
    if (!dv[i]) {
      dv[i] = i;
      primes.push_back(i);
    }
    for (int j = 0; i * primes[j] <= kC && j < primes.size(); ++j) {
      dv[i * primes[j]] = primes[j];
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    cin >> b[i];
    int v = 1;
    while (b[i] > 1) {
      int k = dv[b[i]], cnt = 0;
      while (b[i] % k == 0) {
        b[i] /= k;
        cnt++;
      }
      if (cnt % 2 == 1) {
        v *= k;
      }
    }
    b[i] = v;
  }

  constexpr int kP = 1'000'000'000 + 7;
  int s = 0;
  vector<int> cnt(kC + 1);
  for (int i = 0; i < N; ++i) {
    s = (s + b[i]) % kP;
    cnt[b[i]]++;
  }

  vector<int> fsum(kC + 1);
  for (int i = 1; i <= kC; ++i) {
    for (int j = i; j <= kC; j += i) {
      (fsum[i] += 1LL * cnt[j] * j % kP) %= kP;
    }
  }

  auto fpow = [&](int a, int n) {
    int res = 1;
    while (n > 0) {
      if (n & 1) {
        res = 1LL * res * a % kP;
      }
      a = 1LL * a * a % kP;
      n >>= 1;
    }
    return res;
  };

  int ans = 1LL * s * s % kP;

  for (int v = 2; v <= kC; ++v) {
    int t = v;
    bool square_free = true;
    vector<int> fc;
    while (t > 1) {
      int k = dv[t], cnt = 0;
      while (t % k == 0) {
        t /= k;
        cnt++;
      }
      if (cnt > 1) {
        square_free = false;
        break;
      }
      fc.push_back(k);
    }
    if (square_free) {
      int coeff = 1;
      for (int u : fc) {
        coeff = 1LL * coeff * ((1LL * u * u - 1) % kP) % kP *
                fpow(1LL * u * u % kP, kP - 2) % kP;
      }
      if (fc.size() & 1) {
        ans = (ans + kP - 1LL * coeff * fsum[v] % kP * fsum[v] % kP) % kP;
      } else {
        ans = (ans + 1LL * coeff * fsum[v] % kP * fsum[v] % kP) % kP;
      }
    }
  }
  ans = ans + (kP - N) % kP;
  ans = 1LL * ans * fpow(2, kP - 2) % kP;
  cout << ans << "\n";
  return 0;
}
