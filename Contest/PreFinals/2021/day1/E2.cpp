#include <bits/stdc++.h>
using namespace std;

int sign(int x) { return x == 0 ? 0 : x > 0 ? 1 : -1; }

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int h, w, k; cin >> h >> w >> k;
  int n = h * w;
  vector<int> put(n);
  for (int i = 0; i < n; ++i) cin >> put[i];

  if (k == 1) {
    cout << "A 1" << endl;
    exit(0);
  }

  vector<int> curh(w, 0);
  vector<int> ud(n);
  vector<int> lr(n);
  vector<int> pos(n);
  vector<int> neg(n);
  vector<int> udz(n);
  vector<int> lrz(n);
  vector<int> posz(n);
  vector<int> negz(n);

  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      ud[i * h + j] = i * h + j;
      lr[i * h + j] = i * h + j;
      pos[i * h + j] = i * h + j;
      neg[i * h + j] = i * h + j;

      udz[i * h + j] = 1;
      lrz[i * h + j] = 1;
      posz[i * h + j] = 1;
      negz[i * h + j] = 1;
    }
  }
  
  vector<vector<int>> board(w, vector<int>(h, 0));
  vector<vector<int>> putround(w, vector<int>(h, 0));

  int winner = 0;
  int winround = 10000000;

  auto update = [&] (int w, int r) {
    // cerr << "update w r " << w << ' ' << r << endl;
    if (r < winround) {
      winner = w;
      winround = r;
    }
  };

  auto find = [&] (auto find, vector<int> &djs, int x) -> int {
    return djs[x] == x ? x : find(find, djs, djs[x]);
  };

  auto merge = [&] (vector<int> &djs, vector<int> &sz, int a, int b) -> int{
    a = find(find, djs, a);
    b = find(find, djs, b);
    if (a == b) return 0;
    djs[a] = b;
    sz[b] += sz[a];
    if (sz[b] >= k) return 1;
    return 0;
  };

  auto pid = [&] (int x, int y) {
    return x * h + y;
  };

  int turn = 1;
  for (int r = 0; r < n; ++r) {
    int i = put[r] - 1;
    int j = curh[i]++;

    board[i][j] = turn;
    putround[i][j] = r;

    int sum = 0;
    if (i > 0) if (board[i][j] == board[i - 1][j]) sum += merge(lr, lrz, pid(i, j), pid(i - 1, j));
    if (i < w - 1) if (board[i][j] == board[i + 1][j]) sum += merge(lr, lrz, pid(i, j), pid(i + 1, j));
    if (j > 0) if (board[i][j] == board[i][j - 1]) sum += merge(ud, udz, pid(i, j), pid(i, j - 1));
    if (j < h - 1) if (board[i][j] == board[i][j + 1]) sum += merge(ud, udz, pid(i, j), pid(i, j + 1));
    if (i > 0 && j > 0) if (board[i][j] == board[i - 1][j - 1]) sum += merge(pos, posz, pid(i, j), pid(i - 1, j - 1));
    if (i < w - 1 && j < h - 1) if (board[i][j] == board[i + 1][j + 1]) sum += merge(pos, posz, pid(i, j), pid(i + 1, j + 1));
    if (i > 0 && j < h - 1) if (board[i][j] == board[i - 1][j + 1]) sum += merge(neg, negz, pid(i, j), pid(i - 1, j + 1));
    if (i < w - 1 && j > 0) if (board[i][j] == board[i + 1][j - 1]) sum += merge(neg, negz, pid(i, j), pid(i + 1, j - 1));

    if (sum) {
      update(turn, r + 1);
    }

    turn *= -1;
  }

  // cerr << "board: " << endl;
  // for (int j = h - 1; j >= 0; --j) {
  //   for (int i = 0; i < w; ++i) {
  //     cerr << board[i][j] << ' ';
  //   }
  //   cerr << endl;
  // }
  // cerr << "put round" << endl;
  // for (int j = h - 1; j >= 0; --j) {
  //   for (int i = 0; i < w; ++i) {
  //     cerr << putround[i][j] << ' ';
  //   }
  //   cerr << endl;
  // }


  if (winner == 0) {
    cout << "D" << endl;
  } else {
    cout << (winner == 1 ? "A" : "B") << ' ' << winround << endl;
  }
}
