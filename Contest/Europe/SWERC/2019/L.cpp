#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
  int n; cin >> n;
  vector<string> mp(n);
  for (int i = 0; i < n; ++i) cin >> mp[i];

  auto saveget = [&] (int x, int y) -> char {
    if (x < 0 || y < 0 || x >= n || y >= n) return char(1);
    return mp[x][y];
  };

  vector<int> djs(n * n); iota(djs.begin(), djs.end(), 0);
  function<int(int)> F = [&] (int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); };
  auto U = [&] (int x, int y) { return djs[F(x)] = F(y); };

  vector<vector<int>> g(n * n);

  auto getid = [&] (int x, int y) {
    return x * n + y;
  };

  auto addedge = [&] (int x, int y) {
    g[x].push_back(y);
    g[y].push_back(x);
    U(x, y);
  };

  auto canput = [&] (int x, int y) -> int {
    if (saveget(x - 1, y) == '*') return F(getid(x - 1, y));
    if (saveget(x + 1, y) == '*') return F(getid(x + 1, y));
    if (saveget(x, y - 1) == '*') return F(getid(x, y - 1));
    if (saveget(x, y + 1) == '*') return F(getid(x, y + 1));
    return -1;
  };


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mp[i][j] == '*') {
        if (i && mp[i - 1][j] == '*') U(getid(i, j), getid(i - 1, j));
        if (j && mp[i][j - 1] == '*') U(getid(i, j), getid(i, j - 1));
      }
    }
  }

  vector<vector<int>> canputr(n, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mp[i][j] == '.' && canput(i, j) != -1) {
        canputr[i][j] = canput(i, j);
        if (i && canputr[i - 1][j] == canputr[i][j]) {
          addedge(getid(i - 1, j), getid(i, j));
        }
        if (j && canputr[i][j - 1] == canputr[i][j]) {
          addedge(getid(i, j - 1), getid(i, j));
        }
      }
    }
  }

  vector<int> compec(n * n, 0);
  vector<int> compsz(n * n, 0);
  vector<int> deg(n * n, 0);
  vector<vector<int>> memb(n * n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      memb[F(getid(i, j))].push_back(getid(i, j));
      if (canputr[i][j] != -1) {
        if (i && canputr[i - 1][j] == canputr[i][j]) {
          compec[F(getid(i, j))] += 1;
          ++deg[getid(i, j)];
          ++deg[getid(i - 1, j)];
        }
        if (j && canputr[i][j - 1] == canputr[i][j]) {
          compec[F(getid(i, j))] += 1;
          ++deg[getid(i, j)];
          ++deg[getid(i, j - 1)];
        }

        compsz[F(getid(i, j))]++;
      }
    }
  }

  vector<int> SGr(105, 0);
  SGr[0] = 0;
  SGr[1] = 1;
  for (int i = 2; i <= 100; ++i) {
    set<int> gos;
    for (int j = 1; j <= i; ++j) {
      int z = 0;
      z ^= SGr[max(0, j - 2)];
      z ^= SGr[max(0, i - j - 1)];
      gos.insert(z);
    }
    for (int j = 0; ; ++j) if (gos.count(j) == 0) {
      SGr[i] = j;
      break;
    }
  }

  int val = 0;
  for (int i = 0; i < n * n; ++i) {
    if (F(i) == i && mp[i / n][i % n] == '.' && canputr[i / n][i % n] != -1) {


      vector<pair<int, int>> pos;
      map<pair<int, int>, int> toid;
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          if (F(getid(x, y)) == F(i)) {
            toid[make_pair(x, y)] = pos.size();
            pos.emplace_back(x, y);
          }
        }
      }

      int nn = pos.size();

      vector<int> dp(1 << nn, 0);
      for (int z = 1; z < (1 << nn); ++z) {
        set<int> tos;
        for (int i = 0; i < nn; ++i) if (z & (1 << i)) {
          int zz = z ^ (1 << i);
          int ix = pos[i].first;
          int iy = pos[i].second;

          for (int d = 0; d < 4; ++d) {
            int nx = ix + dx[d];
            int ny = iy + dy[d];
            auto it = toid.find(make_pair(nx, ny));
            if (it != toid.end()) {
              if (zz & (1 << it->second))
                zz ^= 1 << it->second;
            }
          }

          tos.insert(dp[zz]);
        }

        for (int i = 0; ; ++i) if (tos.count(i) == 0) {
          dp[z] = i;
          break;
        }
      }

      val ^= dp[(1 << nn) - 1];
    }

  }

  if (val == 0) {
    cout << "Second player will win" << endl;
  } else {
    cout << "First player will win" << endl;

  }

}
