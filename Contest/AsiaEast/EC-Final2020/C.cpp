#include <iostream>
#include <vector>
using namespace std;

uint64_t Rand(uint64_t x) {
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  return x;
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N), pos(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    A[i]--;
    pos[A[i]] = i;
  }
  vector<int> value(N);
  for (int i = N - 1; i >= 0; --i) {
    int p = pos[i];
    value[i] = p;
    swap(pos[i], pos[A[i]]);
    swap(A[p], A[i]);
  }
  vector<vector<uint64_t>> mask(N + 1, vector<uint64_t>(64));
  for (int i = 0; i < 64; ++i) mask[0][i] = (1ULL << i);
  for (int i = 1; i <= N; ++i) {
    vector<uint64_t> cur = mask[i - 1];
    for (int j = 63; j >= 13; --j) {
      cur[j] ^= cur[j - 13];
    }
    for (int j = 0; j + 7 < 64; ++j) {
      cur[j] ^= cur[j + 7];
    }
    for (int j = 63; j >= 17; --j) {
      cur[j] ^= cur[j - 17];
    }
    mask[i] = cur;
  }
  vector<pair<uint64_t, uint8_t>> eqs;
  for (int i = 2; i <= N; ++i) {
    int B = -1;
    for (int bit = 30; bit >= 0; --bit) {
      if (i % (1 << bit) == 0) {
        B = bit;
        break;
      }
    }
    int r = value[i - 1] % (1 << B);

    for (int j = 0; j < B; ++j) {
      uint8_t v = r >> j & 1;
      eqs.emplace_back(mask[i][j], v);
    }
  }
  int row = 0;
  vector<bool> missing(64);
  vector<int> gbits;
  for (int bit = 0; bit < 64; ++bit) {
    int pivot = -1;
    for (int i = row; i < eqs.size(); ++i) {
      if (eqs[i].first >> bit & 1) {
        pivot = i;
        break;
      }
    }
    if (pivot == -1) {
      missing[bit] = true;
      continue;
    } else {
      gbits.push_back(bit);
    }
    swap(eqs[row], eqs[pivot]);
    for (int i = row + 1; i < eqs.size(); ++i) {
      if (eqs[i].first >> bit & 1) {
        eqs[i].first ^= eqs[row].first;
        eqs[i].second ^= eqs[row].second;
      }
    }
    row++;
  }
  vector<int> bits;
  for (int i = 0; i < 64; ++i) {
    if (missing[i]) bits.push_back(i);
  }
  if (bits.empty()) {
    uint64_t x = 0;
    for (int i = 63; i >= 0; --i) {
      uint8_t s = eqs[i].second;
      for (int j = i + 1; j < 64; ++j) {
        s ^= (x >> j & 1) * (eqs[i].first >> j & 1);
      }
      if (s) x ^= (1ULL << i);
    }
    cout << x << "\n";
    return 0;
  }
  const int M = bits.size();
  eqs.resize(row);
  vector<uint64_t> Eq(64);
  vector<uint8_t> Vl(64);
  for (int i = 0; i < row; ++i) {
    Eq[gbits[i]] = eqs[i].first;
    Vl[gbits[i]] = eqs[i].second;
  }

  auto Check = [&](uint64_t x) {
    for (int i = 0; i < N; ++i) {
      x = Rand(x);
      if (x % (i + 1) != value[i]) return false;
    }
    return true;
  };

  for (int s = 0; s < (1 << M); ++s) {
    for (int i = 0; i < M; ++i) {
      Eq[bits[i]] = (1ULL << bits[i]);
      Vl[bits[i]] = (s >> i & 1);
    }
    uint64_t x = 0;
    for (int i = 63; i >= 0; --i) {
      uint8_t y = __builtin_popcountll(x & Eq[i]) % 2;
      y ^= Vl[i];
      if (y) x ^= (1ULL << i);
    }
    if (Check(x)) {
      cout << x << "\n";
    }
  }
  return 0;
}
