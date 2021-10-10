#include <bits/stdc++.h>
using namespace std;
#define int int64_t

const int g = 42;
const int M = 1'000'000'000'000'000'000 + 31;
const int a0 = 960'002'411'612'632'915;

int mul(int b, int n) {
  // int a = 0;
  // while (n) {
  //   if (n & 1) a = (a + b), a >= M ? a -= M : 0;
  //   b = (b + b) % M; n >>= 1;
  // }
  // return a;
}

int pw(int b, int n) {
  int a = 1;
  while (n) {
    if (n & 1) a = (__int128)a * b % M;
    b = (__int128)b * b % M; n >>= 1;
  }
  return a;
}

int32_t main() {
  int n; cin >> n;

  int x = 300;

  int nn = 1000000 - n;
  while (nn--) {
    x = pw(g, x);
    // cerr << nn << endl;
  }

  cout << x << endl;
  // vector<int> as = { a0 };
  // int a = pw(g, a0);
  // while (a != as[0]) {
  //   as.push_back(a);
  //   a = pw(g, a);
  //   if (as.size() % 10000 == 0) cout << as.size() << endl;
  //   // cout << a << endl;
  // }
}
