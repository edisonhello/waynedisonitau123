#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  vector<vector<char>> grid(N, vector<char>(M));
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> grid[i][j];
  bool swp = false;
  if (N > M) {
    vector<vector<char>> ngrid(M, vector<char>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) ngrid[j][i] = grid[i][j];
    }
    swap(N, M);
    swap(grid, ngrid);
    swp = true;
  }

  vector<vector<vector<bool>>> fp(N);
  vector<vector<uint8_t>> vec;

  auto Get = [&](int pr = -1) {
    vector<bool> parity(N);
    vector<bool> tp(N);
    if (pr != -1) {
      parity[pr] = true;
      tp[pr] = true;
    }

    for (int j = 1; j < M; ++j) {
      vector<bool> np(N);
      vector<bool> nt(N);
      for (int k = 0; k < N; ++k) {
        int t = parity[k];
        if (k > 0) t ^= tp[k - 1];
        if (k + 1 < N) t ^= tp[k + 1];
        char ch = t ? 'B' : 'W';
        if (ch != grid[k][j - 1]) nt[k] = np[k] = true;
        if (tp[k]) np[k] = !np[k];
      }
      parity = move(np);
      tp = move(nt);
    }
    vector<uint8_t> B(N);
    for (int j = 0; j < N; ++j) {
      B[j] = parity[j];
      if (j > 0 && tp[j - 1]) B[j] ^= 1;
      if (j + 1 < N && tp[j + 1]) B[j] ^= 1;
    }
    return B;
  };

  auto Debug = [&](const auto &B) {
    cout << "vec: ";
    for (int i = 0; i < N; ++i) cout << int(B[i]);
    cout << endl;
  };

  auto O = Get();
  // Debug(O);

  for (int i = 0; i < N; ++i) {
    auto B = Get(i);
    for (int j = 0; j < N; ++j) B[j] ^= O[j];
    // Debug(B);
    vec.push_back(B);
  }

  bitset<500> bs;
  vector<pair<vector<uint8_t>, bitset<500>>> basis;
  for (int i = 0; i < N; ++i) {
    auto &V = vec[i];
    bitset<500> bs;
    bs[i] = 1;
    for (int k = 0; k < basis.size(); ++k) {
      const auto &B = basis[k].first;
      int p = find(B.begin(), B.end(), 1) - B.begin();
      assert(p < N);
      if (V[p] == 1) {
        for (int i = 0; i < N; ++i) V[i] ^= B[i];
        bs ^= basis[k].second;
      }
    }
    if (any_of(V.begin(), V.end(), [&](uint8_t t) { return t; })) {
      basis.emplace_back(V, bs);
    }
  }

  vector<uint8_t> target(N);
  for (int i = 0; i < N; ++i) {
    target[i] = (grid[i][M - 1] == 'B');
  }

  for (int i = 0; i < N; ++i) target[i] ^= O[i];

  vector<int> idx;

  bitset<500> B;
  for (auto &[V, i] : basis) {
    int p = find(V.begin(), V.end(), 1) - V.begin();
    if (target[p] == 1) {
      for (int j = 0; j < N; ++j) target[j] ^= V[j];
      B ^= i;
    }
  }
  if (any_of(target.begin(), target.end(), [&](uint8_t t) { return t; })) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  vector<bool> parity(N);
  vector<vector<bool>> res(N, vector<bool>(M));
  for (int i = 0; i < N; ++i) if (B[i]) parity[i] = true;
  for (int i = 0; i < N; ++i) res[i][0] = parity[i];
  for (int i = 1; i < M; ++i) {
    vector<bool> np(N);
    for (int j = 0; j < N; ++j) {
      uint8_t t = parity[j];
      if (j > 0 && res[j - 1][i - 1]) t ^= 1;
      if (j + 1 < N && res[j + 1][i - 1]) t ^= 1;
      char ch = t ? 'B' : 'W';
      if (ch != grid[j][i - 1]) {
        np[j] = true;
        res[j][i] = true;
      }
      if (res[j][i - 1]) np[j] = !np[j];
    }
    parity = np;
  }
  if (M > 1) {
    for (int i = 0; i < N; ++i) {
      uint8_t t = parity[i];
      if (i > 0 && res[i - 1][M - 1]) t ^= 1;
      if (i + 1 < N && res[i + 1][M - 1]) t ^= 1;
      char ch = t ? 'B' : 'W';
      assert(ch == grid[i][M - 1]);
    }
  }
  if (swp) {
    vector<vector<bool>> nres(M, vector<bool>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) nres[j][i] = res[i][j];
    }
    swap(N, M);
    res = nres;
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cout << (res[i][j] ? 'P' : 'A') << " ";
    cout << "\n";
  }
  return 0;
}
