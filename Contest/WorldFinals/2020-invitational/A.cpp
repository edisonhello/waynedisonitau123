#include <bits/stdc++.h>
using namespace std;

int checked[55][55];

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> mp(n);
  for (int i = 0; i < n; ++i) cin >> mp[i];

  vector<vector<string>> move(n, vector<string>(m));

  auto locate = [&](int x, int y) -> set<pair<int, int>> {
    set<pair<int, int>> rt;
    auto dfs = [&](auto dfs, int x, int y) -> void {
      rt.insert(make_pair(x, y));

      static const vector<int> dx{1, 0, -1, 0};
      static const vector<int> dy{0, 1, 0, -1};

      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (mp[nx][ny] != mp[x][y]) continue;
        if (rt.count(make_pair(nx, ny))) continue;
        dfs(dfs, nx, ny);
      }
    };
    dfs(dfs, x, y);
    return rt;
  };

  stack<pair<int, string>> stk;

  while (true) {
    bool different = 0;
    for (int i = 0; i < m; ++i) {
      if (mp[0][i] != '.') {
        auto piece = locate(0, i);
        stk.emplace(i + 1, move[0][i]);
        move[0][i] = "";
        for (auto [x, y] : piece) mp[x][y] = '.';
        different = 1;
      }
    }

    memset(checked, 0, sizeof(checked));

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (checked[i][j]) continue;
        if (mp[i][j] != '.') {
          auto piece = locate(i, j);

          auto try_go = [&](set<pair<int, int>> &piece, int dir) {
            int dx, dy;
            if (dir == -1)
              dx = -1, dy = 0;
            else if (dir == 1)
              dx = 0, dy = 1;
            else
              dx = 0, dy = -1;

            bool ok = 1;
            for (auto [x, y] : piece) {
              int nx = x + dx, ny = y + dy;
              if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                ok = 0;
              else if (mp[nx][ny] == '.')
                ;
              else if (mp[nx][ny] != mp[x][y])
                ok = 0;
            }

            if (ok) {
              auto pos = *piece.begin();
              move[pos.first][pos.second] += dir == -1  ? 'D'
                                             : dir == 1 ? 'L'
                                                        : 'R';  // ?
              char chr = mp[pos.first][pos.second];
              for (auto [x, y] : piece) mp[x][y] = '.';
              set<pair<int, int>> nw;
              for (auto [x, y] : piece)
                nw.insert(make_pair(x + dx, y + dy));
              piece.swap(nw);
              for (auto [x, y] : piece) mp[x][y] = chr;
              swap(move[pos.first][pos.second],
                   move[pos.first + dx][pos.second + dy]);
              different = 1;
            }
          };

          try_go(piece, -1);
          if (move[piece.begin()->first][piece.begin()->second].size() &&
              move[piece.begin()->first][piece.begin()->second].back() ==
                  'R')
            ;
          else
            try_go(piece, 1);
          if (!(move[piece.begin()->first][piece.begin()->second].size() &&
                move[piece.begin()->first][piece.begin()->second].back() ==
                    'L'))
            try_go(piece, 2);

          for (auto [x, y] : piece) checked[x][y] = 1;
        }
      }
    }

    if (!different) break;

    cerr << "iteration" << endl;
    for (int i = 0; i < n; ++i) {
      cerr << mp[i] << endl;
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mp[i][j] != '.') {
        cout << -1 << endl;
        exit(0);
      }
    }
  }

  cout << stk.size() << endl;
  while (stk.size()) {
    auto p = stk.top();
    stk.pop();
    reverse(p.second.begin(), p.second.end());
    cout << p.first << ' ' << p.second << "S\n";
  }
}
