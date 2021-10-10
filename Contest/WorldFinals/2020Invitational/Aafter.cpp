#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int checked[2555];
int vis[55][55];

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> smp(n);
  for (int i = 0; i < n; ++i) cin >> smp[i];

  vector<vector<int>> mp(n, vector<int>(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mp[i][j] != -1) continue;
      if (smp[i][j] == '.')
        mp[i][j] = 0;
      else {
        static int z = 0;
        ++z;
        auto dfs = [&](auto dfs, int x, int y) -> void {
          mp[x][y] = z;

          for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                mp[nx][ny] == -1 && smp[nx][ny] == smp[x][y])
              dfs(dfs, nx, ny);
          }
        };
        dfs(dfs, i, j);
      }
    }
  }

  stack<pair<int, string>> ans;

  while (true) {
    bool same = 1;

    memset(checked, 0, sizeof(checked));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (mp[i][j] && !checked[mp[i][j]]) {
          checked[mp[i][j]] = 1;

          set<pair<int, int>> piece;

          auto get_piece = [&](auto dfs, int x, int y) -> void {
            piece.insert(make_pair(x, y));

            for (int d = 0; d < 4; ++d) {
              int nx = x + dx[d], ny = y + dy[d];
              if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                  !piece.count(make_pair(nx, ny)) &&
                  mp[x][y] == mp[nx][ny])
                dfs(dfs, nx, ny);
            }
          };

          get_piece(get_piece, i, j);

          memset(vis, 0, sizeof(vis));

          auto dfs = [&](auto dfs, string mv) -> bool {
            if (piece.begin()->first == 0) {
              for (auto [x, y] : piece) mp[x][y] = 0;
              reverse(mv.begin(), mv.end());
              ans.emplace(piece.begin()->second + 1, mv + "S");
              return true;
            }

            if (vis[piece.begin()->first][piece.begin()->second]) return false;
            vis[piece.begin()->first][piece.begin()->second] = 1;

            auto can_go = [&](int dx, int dy) -> bool {
              set<pair<int, int>> npc;
              for (auto [x, y] : piece) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                    (mp[nx][ny] == mp[x][y] || mp[nx][ny] == 0))
                  npc.insert(make_pair(nx, ny));
                else return 0;
              }
              int v = mp[piece.begin()->first][piece.begin()->second];
              for (auto [x, y] : piece) mp[x][y] = 0;
              for (auto [x, y] : npc) mp[x][y] = v;
              piece.swap(npc);
              return 1;
            };

            if (can_go(-1, 0)) {
              if (dfs(dfs, mv + "D")) return true;
              assert(can_go(1, 0));
            }
            if ((mv.empty() || mv.back() != 'L') && can_go(0, -1)) {
              if (dfs(dfs, mv + "R")) return true;
              assert(can_go(0, 1));
            }
            if ((mv.empty() || mv.back() != 'R') && can_go(0, 1)) {
              if (dfs(dfs, mv + "L")) return true;
              assert(can_go(0, -1));
            }
            return false;
          };

          if (dfs(dfs, "")) same = 0;
        }
      }
    }

    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0; j < m; ++j) {
    //     cout << mp[i][j] << ' ';
    //   }
    //   cout << endl;
    // }

    if (same) {
      break;
    }
  }

  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (mp[i][j]) {
      cout << -1 << endl;
      exit(0);
    }
  }

  cout << ans.size() << endl;

  while (ans.size()) {
    auto [of, mv] = ans.top();
    ans.pop();
    cout << of << ' ' << mv << '\n';
  }
}
