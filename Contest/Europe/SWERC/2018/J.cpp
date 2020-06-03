#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

const int kIt = 2'00'000;
constexpr int kM = 51 * kIt;

array<int, 2> tri[kM];
int rep[kM];

const uint64_t seed_alt = 0x7263d9bd8409f526;
uint64_t xoroshiro128plus(uint64_t s[2]) {
  uint64_t s0 = s[0], s1 = s[1], result = s0 + s1;
  s1 ^= s0;
  s[0] = ((s0 << 55) | (s0 >> 9)) ^ s1 ^ (s1 << 14);
  s[1] = (s1 << 36) | (s1 >> 28);
  return result;
}

int main() {
  int n; cin >> n;
  uint64_t s1, s2, s3, s4; cin >> s1 >> s2 >> s3 >> s4;

  cc_hash_table<uint64_t, pair<int, int>> r12;
  uint64_t st1[2] = { s1, s1 ^ seed_alt };
  uint64_t st2[2] = { s2, s2 ^ seed_alt };
  uint64_t st3[2] = { s3, s3 ^ seed_alt };
  uint64_t st4[2] = { s4, s4 ^ seed_alt };
  vector<uint64_t> v1s(kIt + 1);
  vector<uint64_t> v2s(kIt + 1);
  vector<uint64_t> v3s(kIt + 1);
  vector<uint64_t> v4s(kIt + 1);
  for (int i = 1; i <= kIt; ++i) {
    v1s[i] = xoroshiro128plus(st1) & ((1ull << n) - 1);
    v2s[i] = xoroshiro128plus(st2) & ((1ull << n) - 1);
    v3s[i] = xoroshiro128plus(st3) & ((1ull << n) - 1);
    v4s[i] = xoroshiro128plus(st4) & ((1ull << n) - 1);
  }
#if 0
  for (int i = 1; i <= kIt; ++i) for (int j = 1; j <= kIt; ++j) {
    r12[v1s[i] ^ v2s[j]] = make_pair(i, j);
  }
  for (int i = 1; i <= kIt; ++i) for (int j = 1; j <= kIt; ++j) {
    auto it = r12.find(v3s[i] ^ v4s[j]);
    if (it != r12.end()) {
      cout << it->second.first << ' ' << it->second.second << ' ';
      cout << i << ' ' << j << '\n';
      exit(0);
    }
  }
#endif

  auto Solve = [&](auto a, auto b) {
    tri[0][0] = -1;
    tri[0][1] = -1;
    rep[0] = -1;
    int sz = 1;
    for (int j = 1; j <= kIt; ++j) {
      auto x = a[j];
      int g = 0;
      for (int i = n - 1; i >= 0; --i) {
        int bit = x >> i & 1;
        if (tri[g][bit] == -1) {
          tri[sz][0] = -1;
          tri[sz][1] = -1;
          rep[sz] = -1;
          tri[g][bit] = sz++;
        }
        g = tri[g][bit];
      }
      rep[g] = j;
    }
    vector<pair<uint64_t, pair<int, int>>> res;
    for (int j = 1; j <= kIt; ++j) {
      auto x = b[j];
      int g = 0;
      uint64_t y = 0;
      for (int i = n - 1; i >= 0; --i) {
        int bit = x >> i & 1;
        if (tri[g][bit ^ 1] != -1) {
          g = tri[g][bit ^ 1];
        } else {
          g = tri[g][bit];
          y ^= 1ULL << i;
        }
      }
      assert(rep[g] != -1);
      res.emplace_back(y, make_pair(rep[g], j));
    }
    return res;
  };

  auto x = Solve(v1s, v2s);
  auto y = Solve(v3s, v4s);
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  for (int i = 0, j = 0; i < x.size(); ++i) {
    while (j < y.size() && y[j].first < x[i].first) j++;
    if (j < y.size() && y[j].first == x[i].first) {
      assert((v1s[x[i].second.first] ^ v2s[x[i].second.second] ^ v3s[y[j].second.first] ^ v4s[y[j].second.second]) == 0);
      cout << x[i].second.first << " " << x[i].second.second << " " << y[j].second.first << " " << y[j].second.second << "\n";
      return 0;
    }
  }
}
