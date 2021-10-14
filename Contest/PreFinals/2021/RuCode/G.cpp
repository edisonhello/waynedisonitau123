#include <bits/stdc++.h>
using namespace std;

const int Z = 9;
const int ZZ = 1 << Z;
const int POLY = 3;

int m[ZZ + 45][ZZ + 45];

int mult(int x, int y) {
  int z = 0;
  for (int i = 0; i < Z; ++i) if (y & (1 << i)) z ^= x << i;
  for (int i = Z * 2; i >= Z; --i) if (z & (1 << i)) z ^= (1 << i) ^ (POLY << (i - Z));
  return z;
}

void gen() {
  for (int i = 2; i < ZZ; ++i) {
    for (int j = i; j < ZZ; ++j) {
      int v = mult(i, j);
      m[i][j] = m[j][i] = v;
    }
  }
}

int ap[ZZ + 45];
bool check() {
  for (int i = 1; i < ZZ; ++i) {
    for (int j = i + 1; j < ZZ; ++j) {
      memset(ap, 0, sizeof(ap));

      for (int k = 1; k < ZZ; ++k) {
        int v = m[i][k] ^ m[j][k];
        if (ap[v]) return false;
        ap[v] = 1;
      }
    }
  }
  return true;
}

int main() {
  for (int i = 1; i <= ZZ; ++i) m[1][i] = m[i][1] = i;

  // while (POLY > 0) {
  //   gen();
  //   // cerr << "POLY " << POLY << endl;
  //   // for (int i = 1; i < ZZ; ++i) {
  //   //   for (int j = 1; j < ZZ; ++j) {
  //   //     cerr << m[i][j] << ' ';
  //   //   }
  //   //   cerr << endl;
  //   // }
  //   if (!check()) {
  //     cerr << "POLY = " << POLY << " failed" << endl;
  //     --POLY;
  //   } else break;
  // }

  gen();
  assert(check() == 1);

  int N, M; cin >> N >> M;

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      // cout << m[i][j] << ' ';
      cout << (m[i][j] ^ m[i - 1][j] ^ m[i][j - 1] ^ m[i - 1][j - 1]) << ' ';
    }
    cout << '\n';
  }

  // cout << POLY << endl;

}
