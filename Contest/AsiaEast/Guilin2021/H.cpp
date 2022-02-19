#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 500'000 + 123;
constexpr int kB = 30;
int jump[kB][kN][2];
int to[kN][2];
int64_t used[kB][kN][2];
int nxt[kN][2];
int fail[kN];
int l[kN], r[kN], pos[kN];
char buf[kN];
int64_t cnt[kN];

int Read() {
  char c = 0;
  while (c = getchar(), !isdigit(c));
  int x = c - '0';
  while (c = getchar(), isdigit(c)) {
    x = x * 10 + c - '0';
  }
  return x;
}

int main() {
  int N = Read();
  int Q = Read();

  for (int i = 0; i < N; ++i) {
    l[i] = Read();
    r[i] = Read();
  }

  memset(fail, -1, sizeof(fail));
  memset(nxt, -1, sizeof(nxt));

  int W = 1;

  auto Insert = [&]() {
    int x = 0;
    for (int i = 0; buf[i] != '\n'; ++i) {
      if (nxt[x][buf[i] - '0'] == -1) {
        nxt[x][buf[i] - '0'] = W++;
      }
      x = nxt[x][buf[i] - '0'];
    }
    return x;
  };

  for (int i = 0; i < Q; ++i) {
    fgets(buf, kN, stdin);
    pos[i] = Insert();
  }

  vector<int> que = {0};
  for (int it = 0; it < que.size(); ++it) {
    int x = que[it];
    for (int i = 0; i < 2; ++i) {
      if (nxt[x][i] != -1) {
        int p = nxt[x][i], fp = fail[x];
        while (fp != -1 && nxt[fp][i] == -1) {
          fp = fail[fp];
        }
        int pd = fp != -1 ? nxt[fp][i] : 0;
        fail[p] = pd;
        que.push_back(p);
      }
    }
  }

  // reverse(que.begin(), que.end());
  for (int i : que) {
    for (int j = 0; j < 2; ++j) {
      if (nxt[i][j] == -1) {
        nxt[i][j] = fail[i] == -1 ? 0 : nxt[fail[i]][j];
      }
      // nxt[i][j] = x;
    }
    jump[0][i][0] = nxt[i][0];
    jump[0][i][1] = nxt[i][1];
  }
  for (int bit = 1; bit < kB; ++bit) {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < 2; ++j) {
        jump[bit][i][j] = jump[bit - 1][jump[bit - 1][i][j]][j ^ 1];
      }
    }
  }
  auto Get = [&](int x) {
    return __builtin_popcount(x) % 2;
  };

  int x = 0;
  for (int i = 0; i < N; ++i) {
    r[i]++;
    while (l[i] < r[i]) {
      int low_bit = __builtin_ctz(l[i] & -l[i]);
      if (l[i] + (1 << low_bit) > r[i]) {
        break;
      }
      int b = Get(l[i]);
      used[low_bit][x][b]++;
      x = jump[low_bit][x][b];
      l[i] += (1 << low_bit);
    }
    while (l[i] < r[i]) {
      int low_bit = 31 - __builtin_clz(r[i] - l[i]);
      int b = Get(l[i]);
      used[low_bit][x][b]++;
      x = jump[low_bit][x][b];
      l[i] += (1 << low_bit);
    }
    assert(l[i] == r[i]);
  }
  for (int bit = kB - 2; bit >= 0; --bit) {
    for (int i = 0; i < W; ++i) {
      for (int j = 0; j < 2; ++j) {
        used[bit][i][j] += used[bit + 1][i][j];
        used[bit][jump[bit][i][j]][j ^ 1] += used[bit + 1][i][j];
      }
    }
  }
  // for (int i = 0; i < W; ++i) {
  //   used[kB - 1][i][0] = 0;
  // }
  for (int i = 0; i < W; ++i) {
    for (int j = 0; j < 2; ++j) {
      cnt[nxt[i][j]] += used[0][i][j];
      // used[kB - 1][nxt[i][j]][0] += used[0][i][j];
    }
  }
  reverse(que.begin(), que.end());
  for (int i : que) {
    if (fail[i] != -1) {
      cnt[fail[i]] += cnt[i];
      // used[kB - 1][fail[i]][0] += used[kB - 1][i][0];
    }
  }
  for (int i = 0; i < Q; ++i) {
    cout << cnt[pos[i]] << "\n";
    // cout << used[kB - 1][pos[i]][0] << "\n";
  }
  return 0;
}

