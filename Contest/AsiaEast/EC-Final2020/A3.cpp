#pragma GCC optimize("O3")
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

constexpr int kN = 1'000'000;
int chr[kN], cnt[62], pc[62][kN];
int64_t pf[kN];
vector<int> pos[62];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int N = s.size();
  constexpr int kP = 998244353;

  auto Get = [&](char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return 26 + c - 'A';
    return 52 + c - '0';
  };

  for (int i = 0; i < N; ++i) {
    chr[i] = Get(s[i]);
    pos[chr[i]].push_back(i);
  }
  for (int i = 0; i < 62; ++i) {
    reverse(pos[i].begin(), pos[i].end());
  }

  for (int i = 0; i < N; ++i) {
    pf[i] = cnt[chr[i]];
    cnt[chr[i]]++;
    if (i > 0) pf[i] += pf[i - 1];
    pc[chr[i]][i] = 1;
    if (i > 0) {
      for (int j = 0; j < 62; ++j) {
        pc[j][i] += pc[j][i - 1];
      }
    }
  }

  int ans = 0;
  for (int x = 0; x < 62; ++x) {
    for (int y = 0; y < 62; ++y) {
      if (x == y) continue;

      for (int p : pos[x]) {

      }

      int i = 0, j = 0;

      auto GetNext = [&]() {
        if (i < pos[x].size() && j < pos[y].size()) {
          if (pos[x][i] > pos[y][j]) return pos[x][i++];
          else return pos[y][j++];
        } else if (i < pos[x].size()) {
          return pos[x][i++];
        } else if (j < pos[y].size()) {
          return pos[y][j++];
        }
        return -1;
      };
    

      int cnt = 0;
      int64_t s = 0;
      int64_t t = 0;
      while (true) {
        int p = GetNext();
        if (p == -1) break;
        if (chr[p] == y) cnt++, t += s;
        else if (chr[p] == x) {
          s += cnt;
          if (p > 0) {
            int64_t res = 1LL * p * (p - 1) / 2 - pf[p - 1];
            res -= 1LL * pc[x][p - 1] * pc[y][p - 1];
            res -= 1LL * pc[x][p - 1] * (p - pc[x][p - 1] - pc[y][p - 1]);
            res -= 1LL * pc[y][p - 1] * (p - pc[x][p - 1] - pc[y][p - 1]);
            if (res == 0) break;
            if (t >= kP) t %= kP;
            ans += 1LL * t * (res % kP) % kP;
            if (ans >= kP) ans -= kP;
          }
        }
      }
    }
  }
  cout << ans << "\n";
}
