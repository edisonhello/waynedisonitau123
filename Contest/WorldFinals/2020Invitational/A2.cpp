#include <bits/stdc++.h>
using namespace std;

int checked[55][55];

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> omp(n);
  for (int i = 0; i < n; ++i) cin >> omp[i];

  int blkcnt = 0;
  vector<vector<int>> mp(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (omp[i][j] == '.')
        mp[i][j] = 0;
      else if (mp[i][j])
        continue;
      else {
        ++blkcnt;

        auto dfs = [&](auto dfs, int x, int y) -> void {
          if (mp[x][y]) return;
          mp[x][y] = blkcnt;

          static const vector<int> dx{1, 0, -1, 0};
          static const vector<int> dy{0, 1, 0, -1};

          for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (omp[nx][ny] == omp[x][y]) {
              dfs(dfs, nx, ny);
            }
          }
        };

        dfs(dfs, i, j);
      }
    }
  }

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
    // cerr << "iteration" << endl;
    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0; j < m; ++j) {
    //     cerr << mp[i][j] << ' ';
    //   }
    //   cerr << endl;
    // }

    bool different = 0;

    bool empty = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mp[i][j] != 0) {
          empty = 0;
          auto piece = locate(i, j);

          auto fi = *piece.begin();
          if (i != fi.first || j != fi.second) continue;

          memset(checked, 0, sizeof(checked));

          auto dfs = [&](auto dfs, auto &nowmp, auto &nowpiece,
                         string mv) -> bool {
            // cerr << "dfs" << endl;
            // for (int i = 0; i < n; ++i) {
            //   cerr << nowmp[i] << endl;
            // }

            auto can_go = [&](int dx, int dy) -> bool {
              for (auto [x, y] : nowpiece) {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                  return 0;
                else if (nowmp[nx][ny] == 0)
                  ;
                else if (nowmp[nx][ny] != nowmp[x][y])
                  return 0;
              }
              return 1;
            };

            auto go = [&](int dx, int dy) {
              auto pos = *nowpiece.begin();
              int chr = nowmp[pos.first][pos.second];
              for (auto [x, y] : nowpiece) nowmp[x][y] = 0;
              set<pair<int, int>> nw;
              for (auto [x, y] : nowpiece)
                nw.insert(make_pair(x + dx, y + dy));
              nowpiece.swap(nw);
              for (auto [x, y] : nowpiece) nowmp[x][y] = chr;
            };

            auto fi = *nowpiece.begin();
            if (fi.first == 0) {
              stk.emplace(fi.second + 1, mv);
              for (auto [x, y] : nowpiece) nowmp[x][y] = 0;
              mp = nowmp;
              different = 1;
              return true;
            }

            if (checked[fi.first][fi.second]) return false;
            checked[fi.first][fi.second] = 1;

            if (can_go(-1, 0)) {
              go(-1, 0);
              if (dfs(dfs, nowmp, nowpiece, mv + "D")) return true;
              go(1, 0);
            }

            if (mv.size() && mv.back() == 'R')
              ;
            else if (can_go(0, 1)) {
              go(0, 1);
              if (dfs(dfs, nowmp, nowpiece, mv + "L")) return true;
              go(0, -1);
            }

            if (mv.size() && mv.back() == 'L')
              ;
            else if (can_go(0, -1)) {
              go(0, -1);
              if (dfs(dfs, nowmp, nowpiece, mv + "R")) return true;
              go(0, 1);
            }

            return false;
          };

          dfs(dfs, mp, piece, "");
        }
      }
    }

    if (empty) break;
    if (!different) break;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mp[i][j] != 0) {
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

