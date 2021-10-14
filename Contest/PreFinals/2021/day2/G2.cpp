#include <bits/stdc++.h>
using namespace std;

int main() {
  string g;
  cin >> g;
  int64_t A;
  cin >> A;

  int N = g.size();
  int M = N / 2;
  vector<map<__int128, int64_t>> E(N + 1);
  map<__int128, int64_t> D;

  int64_t ans = 0;
  for (int s = 0; s < (1 << (N - M)); ++s) {
    string t = "";
    for (int i = 0; i < N - M; ++i) {
      if (s >> i & 1) {
        t += g[i + M];
      }
    }
    if (t.empty()) continue;
    bool ok = (t.back() != '+');
    bool fp = (t[0] == '+');
    for (int i = 1; i < t.size(); ++i) {
      if (t[i] == '+' && t[i - 1] == '+') ok = false;
    }
    if (!ok) continue;
    bool f = true;
    __int128 b = 0;
    int z = -1;
    for (int i = 0, j = 0; i < t.size(); i = j) {
      if (t[i] == '+') {
        j = i + 1;
        continue;
      }
      __int128 v = 0;
      while (j < t.size() && t[j] != '+') {
        v = v * 10 + (t[j] - '0');
        j++;
      }
      if (f) z = j - i, f = false;
      b += v;
    }
    if (fp) {
      D[b]++;
    } else {
      assert(z != -1);
      E[z][b]++;
      if (b == A) ans++;
    }
  }
  for (int s = 0; s < (1 << M); ++s) {
    string t = "";
    for (int i = 0; i < M; ++i) {
      if (s >> i & 1) {
        t += g[i];
      }
    }
    if (t.empty()) continue;
    bool ok = (t[0] != '+');
    bool fp = (t.back() == '+');
    for (int i = 1; i < t.size(); ++i) {
      if (t[i] == '+' && t[i - 1] == '+') ok = false;
    }
    if (!ok) continue;
    vector<__int128> buf;
    for (int i = 0, j = 0; i < t.size(); i = j) {
      if (t[i] == '+') {
        j = i + 1;
        continue;
      }
      __int128 v = 0;
      while (j < t.size() && t[j] != '+') {
        v = v * 10 + (t[j] - '0');
        j++;
      }
      buf.push_back(v);
    }
    __int128 sum = accumulate(buf.begin(), buf.end(), __int128(0));
    if (sum == A && !fp) ans++;
    if (fp) {
      for (int i = 0; i <= N; ++i) {
        if (E[i].find(A - sum) != E[i].end()) ans += E[i][A - sum];
      }
    } else {
      if (D.find(A - sum) != D.end()) ans += D[A - sum];      
      assert(!buf.empty());
      __int128 x = buf.back();
      __int128 t = sum - x;
      for (int i = 1; i <= N; ++i) {
        if (x * 10 > A) break;
        x *= 10;
        if (E[i].find(A - t - x) != E[i].end()) ans += E[i][A - t - x];
      }
    }
  }
  cout << ans << "\n";
}
