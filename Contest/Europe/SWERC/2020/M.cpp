#include <bits/stdc++.h>
using namespace std;

int n, m;
int djs[65 * 105];

#define id(x, y) (((x)*m + (y)))

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int vis[105][105];
int dis[105][105];
set<pair<int, int>> inst, adj;

void dfs(vector<string> &mp, int x, int y, int bord, int to) {
  vis[x][y] = 1;
  // cout << "x y to " << x << ' ' << y << ' ' << to << endl;

  for (int d = 0; d < 4; ++d) {
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    if (mp[nx][ny] == to) continue;
    if (vis[nx][ny]) continue;
    dfs(mp, nx, ny, bord, to);
  }

  if (x >= bord && y >= bord && x < n - bord && y < m - bord) {
    inst.insert(make_pair(x, y));
  }
}

int main() {
  cin >> m >> n;

  vector<string> s(n), t(n);

  for (int i = 0; i < n; ++i) cin >> s[i];
  for (int i = 0; i < n; ++i) cin >> t[i];

  for (auto &ss : s) {
    for (char &c : ss) {
      c = c == '#';
    }
  }

  for (auto &ss : t) {
    for (char &c : ss) {
      c = c == '#';
    }
  }

  auto os = s;

  int nn = n * m;
  for (int i = 0; i < nn; ++i) djs[i] = i;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i && s[i][j] == s[i - 1][j]) U(id(i, j), id(i - 1, j));
      if (j && s[i][j] == s[i][j - 1]) U(id(i, j), id(i, j - 1));
    }
  }

  int szs = 0;
  for (int i = 0; i < nn; ++i)
    if (F(i) == i) ++szs;

  for (int i = 0; i < nn; ++i) djs[i] = i;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i && t[i][j] == t[i - 1][j]) U(id(i, j), id(i - 1, j));
      if (j && t[i][j] == t[i][j - 1]) U(id(i, j), id(i, j - 1));
    }
  }

  int szt = 0;
  for (int i = 0; i < nn; ++i)
    if (F(i) == i) ++szt;

  if (szs != szt || s[0][0] != t[0][0]) {
    cout << "IMPOSSIBLE" << endl;
    exit(0);
  }

  // cout << "szs szt = " << szs << ' ' << szt << endl;

  vector<pair<int, int>> ans;
  for (int i = 0; i < szs - 1; ++i) {
    inst.clear();
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));

    queue<pair<int, int>> q;
    for (int x = i; x <= n - 1 - i; ++x) {
      for (int y = i; y <= m - 1 - i; ++y) {
        if (x == i || x == n - 1 - i || y == i || y == m - 1 - i) {
          q.emplace(x, y);
          vis[x][y] = 1;
        }
      }
    }

    while (q.size()) {
      auto [x, y] = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx <= i || ny <= i || nx >= n - 1 - i || ny >= m - 1 - i) 
          continue;
        if (vis[nx][ny]) continue;
        if (s[nx][ny] != s[x][y]) continue;
        dis[nx][ny] = dis[x][y] + 1;
        vis[nx][ny] = 1;
        q.emplace(nx, ny);
        inst.insert(make_pair(nx, ny));
      }
    }

    priority_queue<tuple<int, int, int>> adj;
    vector<pair<int, int>> dels;
    for (auto [u, v] : inst) {
      for (int d = 0; d < 4; ++d) {
        int nx = u + dx[d];
        int ny = v + dy[d];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        int dis = ::dis[u][v];
        if (s[nx][ny] == !s[i][i]) {
          adj.emplace(dis, u, v);
          dels.emplace_back(u, v);
          break;
        }
      }
    }
    for (auto p : dels) inst.erase(p);

    while (adj.size()) {
      auto [_d, u, v] = adj.top();
      adj.pop();
      s[u][v] = !s[i][i];
      ans.emplace_back(u, v);
      for (int d = 0; d < 4; ++d) {
        int nx = u + dx[d];
        int ny = v + dy[d];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        int dis = ::dis[nx][ny];
        if (inst.count(make_pair(nx, ny))) {
          adj.emplace(dis, nx, ny);
          inst.erase(make_pair(nx, ny));
        }
      }
    }
  }

  vector<pair<int, int>> ans2;

  for (int i = 0; i < szt - 1; ++i) {
    inst.clear();
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));

    queue<pair<int, int>> q;
    for (int x = i; x <= n - 1 - i; ++x) {
      for (int y = i; y <= m - 1 - i; ++y) {
        if (x == i || x == n - 1 - i || y == i || y == m - 1 - i) {
          q.emplace(x, y);
          vis[x][y] = 1;
        }
      }
    }

    while (q.size()) {
      auto [x, y] = q.front();
      q.pop();

      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx <= i || ny <= i || nx >= n - 1 - i || ny >= m - 1 - i) 
          continue;
        if (vis[nx][ny]) continue;
        if (t[nx][ny] != t[x][y]) continue;
        dis[nx][ny] = dis[x][y] + 1;
        vis[nx][ny] = 1;
        q.emplace(nx, ny);
        inst.insert(make_pair(nx, ny));
      }
    }

    priority_queue<tuple<int, int, int>> adj;
    vector<pair<int, int>> dels;
    for (auto [u, v] : inst) {
      for (int d = 0; d < 4; ++d) {
        int nx = u + dx[d];
        int ny = v + dy[d];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        int dis = ::dis[u][v];
        if (t[nx][ny] == !t[i][i]) {
          adj.emplace(dis, u, v);
          dels.emplace_back(u, v);
          break;
        }
      }
    }
    for (auto p : dels) inst.erase(p);

    while (adj.size()) {
      auto [_d, u, v] = adj.top();
      adj.pop();
      t[u][v] = !t[i][i];
      ans2.emplace_back(u, v);
      for (int d = 0; d < 4; ++d) {
        int nx = u + dx[d];
        int ny = v + dy[d];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        int dis = ::dis[nx][ny];
        if (inst.count(make_pair(nx, ny))) {
          adj.emplace(dis, nx, ny);
          inst.erase(make_pair(nx, ny));
        }
      }
    }
  }

  reverse(ans2.begin(), ans2.end());
  for (auto p : ans2) ans.push_back(p);

  for (auto [u, v] : ans) {
    cout << v << ' ' << u << '\n';
  }

  // cout << ans.size() << endl;

  // for (auto [u, v] : ans) {
  //   os[u][v] = !os[u][v];

  //   for (auto &ss : os) {
  //     for (char c : ss) {
  //       cout << int(c);
  //     }
  //     cout << endl;
  //   }
  //   cout << endl;
  // }
}

