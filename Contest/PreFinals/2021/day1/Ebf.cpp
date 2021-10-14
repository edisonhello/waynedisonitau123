#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int h, w, k; cin >> h >> w >> k;
  int n = h * w;
  vector<int> put(n);
  for (int i = 0; i < n; ++i) cin >> put[i];

  vector<int> curh(w, 0);
  vector<vector<int>> board(w, vector<int>(h, 0));
  vector<vector<int>> putround(w, vector<int>(h, 0));

  int winner = 0;
  int winround = 10000000;

  auto update = [&] (int w, int r) {
    if (r < winround) {
      winner = w;
      winround = r;
    }
  };

  int turn = 1;
  for (int r = 0; r < n; ++r) {
    int i = put[r] - 1;
    int j = curh[i]++;

    board[i][j] = turn;
    putround[i][j] = r + 1;

    turn *= -1;
  }

  cerr << "board: " << endl;
  for (int j = h - 1; j >= 0; --j) {
    for (int i = 0; i < w; ++i) {
      cerr << board[i][j] << ' ';
    }
    cerr << endl;
  }
  cerr << "put round" << endl;
  for (int j = h - 1; j >= 0; --j) {
    for (int i = 0; i < w; ++i) {
      cerr << putround[i][j] << ' ';
    }
    cerr << endl;
  }

  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (i + k - 1 < w) {
        int su = 0;
        int mx = 0;
        for (int ii = i; ii <= i + k - 1; ++ii) su += board[ii][j], mx = max(mx, putround[ii][j]);
        if (abs(su) == k) update(board[i][j], mx);
      }
      if (i + k - 1 < w && j + k - 1 < h) {
        int su = 0;
        int mx = 0;
        for (int d = 0; d < k; ++d) su += board[i + d][j + d], mx = max(mx, putround[i + d][j + d]);
        if (abs(su) == k) update(board[i][j], mx);
      }
      if (j + k - 1 < h) {
        int su = 0;
        int mx = 0;
        for (int d = 0; d < k; ++d) su += board[i][j + d], mx = max(mx, putround[i][j + d]);
        if (abs(su) == k) update(board[i][j], mx);
      }
      if (i + k - 1 < w && j - k + 1 >= 0) {
        int su = 0;
        int mx = 0;
        for (int d = 0; d < k; ++d) su += board[i + d][j - d], mx = max(mx, putround[i + d][j - d]);
        if (abs(su) == k) update(board[i][j], mx);
      }
    }
  }

  if (winner == 0) {
    cout << "D" << endl;
  } else {
    cout << (winner == 1 ? "A" : "B") << ' ' << winround << endl;
  }
}
