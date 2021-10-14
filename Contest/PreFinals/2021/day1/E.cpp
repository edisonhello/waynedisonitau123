#include <bits/stdc++.h>
using namespace std;

int sign(int x) { return x == 0 ? 0 : x > 0 ? 1 : -1; }

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int h, w, k; cin >> h >> w >> k;
  int n = h * w;
  vector<int> put(n);
  for (int i = 0; i < n; ++i) cin >> put[i];

  vector<int> curh(w, 0);
  vector<vector<int>> down(w, vector<int>(h, 0));
  vector<vector<int>> ld(w, vector<int>(h, 0));
  vector<vector<int>> rd(w, vector<int>(h, 0));
  
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

  int turn = 1;
  for (int r = 0; r < n; ++r) {
    int i = put[r] - 1;
    int j = curh[i]++;

    board[i][j] = turn;
    putround[i][j] = r;

    if (j) {
      if (sign(down[i][j - 1]) == turn) {
        down[i][j] = down[i][j - 1] + turn;
      } else {
        down[i][j] = turn;
      }

      if (i > 0) {
        if (sign(ld[i - 1][j - 1]) == turn) {
          ld[i][j] = ld[i - 1][j - 1] + turn;
        } else {
          ld[i][j] = turn;
        }
      }

      if (i < w - 1) {
        if (sign(rd[i + 1][j - 1]) == turn) {
          rd[i][j] = rd[i + 1][j - 1] + turn;
        } else {
          rd[i][j] = turn;
        }
      }
    } else {
      down[i][j] = turn;
      ld[i][j] = turn;
      rd[i][j] = turn;
    }

    if (down[i][j] == turn * k || ld[i][j] == turn * k || rd[i][j] == turn * k) {
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


  // row case
  
  deque<int> dq;
  for (int j = 0; j < h; ++j) {
    for (int i = 0, ii; i < w; i = ii) {
      for (ii = i; ii < w && board[ii][j] == board[i][j]; ++ii);
      // cerr << "j i ii " << j << ' ' << i << ' ' << ii << endl;
      if (ii - i >= k) {
        int l = i, r = ii;
        dq.clear();
        auto insert = [&] (int idx) {
          int v = putround[idx][j];
          while (dq.size() && v > putround[dq.back()][j]) dq.pop_back();
          dq.push_back(idx);
        };
        for (int i = l; i < l + k; ++i) {
          insert(i);
        }
        for (int i = l + k - 1; i < r; ++i) {
          update(board[l][j], putround[dq.front()][j] + 1);
          if (dq.front() == i - k + 1) dq.pop_front();
          if (i + 1 < r) insert(i + 1);
        }
      }
    }
  }

  if (winner == 0) {
    cout << "D" << endl;
  } else {
    cout << (winner == 1 ? "A" : "B") << ' ' << winround << endl;
  }
}
