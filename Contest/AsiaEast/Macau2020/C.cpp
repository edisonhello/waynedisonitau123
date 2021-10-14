#pragma GCC optimize("O3")
#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

constexpr int kN = 100'000;
constexpr int kB = 30;
int trie[kN * kB][2], subt[kN * kB][2];
int W[kN], color[kN];
vector<int> g[kN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;

    int ptr = 0;
    trie[ptr][0] = trie[ptr][1] = -1;
    subt[ptr][0] = subt[ptr][1] = -1;
    ptr++;
    for (int i = 0; i < N; ++i) cin >> W[i];

    auto Insert = [&](int p, int v) {
      int x = 0;
      for (int bit = kB - 1; bit >= 0; --bit) {
        if (trie[x][v >> bit & 1] == -1) {
          trie[x][v >> bit & 1] = ptr;
          trie[ptr][0] = trie[ptr][1] = subt[ptr][0] = subt[ptr][1] = -1;
          ptr++;
        }
        x = trie[x][v >> bit & 1];
        if (subt[x][0] == -1) {
          subt[x][0] = p;
        } else if (subt[x][1] == -1) {
          subt[x][1] = p;
        }
      }
    };

    for (int i = 0; i < N; ++i) Insert(i, W[i]);

    auto Check = [&](int t) {
      for (int i = 0; i < N; ++i) g[i].clear();
      for (int i = 0; i < N; ++i) {
        int x = 0, v = W[i];
        for (int bit = kB - 1; x != -1 && bit >= 0; --bit) {
          if (t >> bit & 1) {
            if (trie[x][v >> bit & 1] != -1) {
              int y = trie[x][v >> bit & 1];
              int cnt = 0;
              for (int j = 0; j < 2; ++j) {
                if (subt[y][j] != -1 && subt[y][j] != i) {
                  cnt++;
                  int u = subt[y][j];
                  g[i].push_back(u);
                  g[u].push_back(i);
                }
              }
              if (cnt > 1) return false;
            }
            x = trie[x][(v >> bit & 1) ^ 1];
          } else {
            x = trie[x][v >> bit & 1];
          }
        }
      }

      fill_n(color, N, -1);

      auto Dfs = [&](auto dfs, int x, int c = 0) -> bool {
        color[x] = c;
        for (auto u : g[x]) {
          if (color[u] == -1) {
            if (!dfs(dfs, u, c ^ 1)) return false;
          } else {
            if (color[u] != (c ^ 1)) return false;
          }
        }
        return true;
      };

      for (int i = 0; i < N; ++i) {
        if (color[i] != -1) continue;
        if (!Dfs(Dfs, i)) return false;
      }
      return true;
    };

    int ans = -1;
    for (int bit = kB - 1; bit >= 0; --bit) {
      if (Check(ans + (1 << bit))) ans += (1 << bit);
    }
    Check(ans);
    cout << ans << "\n";
    for (int i = 0; i < N; ++i) cout << color[i] + 1;
    cout << "\n";
  }
}
