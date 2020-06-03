#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[] = {0, 1, 0, -1, 1, -1, -1, 1};


string mp[1005];
int cntans[1000005];
int n, m, face_id;
int is_wall[1005][1005];
bool is_face[1005][1005];
int djs_id[1005][1005], djs[1000006];

int Find(int x) { return x == djs[x] ? djs[x] : djs[x] = Find(djs[x]); }
void Union(int x, int y) { djs[Find(x)] = Find(y); }

bool Inside(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < m;
}

void DfsWall(int x, int y) {
  is_wall[x][y] = 1;
  for (int d = 0; d < 8; ++d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (!Inside(nx, ny)) continue;
    if (is_wall[nx][ny]) continue;
    if (mp[nx][ny] == '.') continue;
    DfsWall(nx, ny);
  }
}

vector<pair<int, int>> cur_face;
void DfsFace(int x, int y) {
  is_face[x][y] = face_id;
  cur_face.emplace_back(x, y);
  for (int d = 0; d < 4; ++d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (!Inside(nx, ny)) continue;
    if (is_wall[nx][ny]) continue;
    // if (mp[x][y] == '.' && mp[nx][ny] == '.') 
    //   Union(djs_id[x][y], djs_id[nx][ny]);
    if (is_face[nx][ny]) continue;
    DfsFace(nx, ny);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cin >> m >> n;
  for (int i = 0; i < n; ++i) cin >> mp[i];

  for (int i = 1; i < n - 1; ++i) for (int j = 1; j < m - 1; ++j) {
    if (mp[i][j] == '#') {
      int ccc = 0;
      for (int d = 0; d < 8; ++d) ccc += mp[i + dx[d]][j + dy[d]] == '.';
      if (ccc == 8) mp[i][j] = '.';
    }
  }
  
  DfsWall(0, 0);

  // cerr << "is_wall" << endl;
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0 ; j < m; ++j) {
  //     cerr << is_wall[i][j];
  //   }
  //   cerr << endl;
  // }

  int totid = 0;
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    djs[totid] = totid;
    djs_id[i][j] = totid++;
  }

  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    if (is_wall[i][j]) continue;
    if (is_face[i][j]) continue;
    // cerr << "a face start " << i << ' ' << j << endl;
    cur_face.clear();
    ++face_id;
    DfsFace(i, j);

    for (auto p : cur_face) {
      int x, y; tie(x, y) = p;
      for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (is_face[nx][ny] == is_face[x][y] && mp[x][y] == '.' && mp[nx][ny] == '.') 
          Union(djs_id[nx][ny], djs_id[x][y]);
      }
    }

    int ccc = 0;
    for (auto p : cur_face) {
      if (mp[p.first][p.second] == '.' && Find(djs_id[p.first][p.second]) == djs_id[p.first][p.second]) {
        ++ccc;
        // cerr << "big white " << p.first << ' ' << p.second << endl;
      }
    }
    ccc = min(ccc, 3);
    ++cntans[ccc - 1];
    // cerr << "ccc = " << ccc << endl;

    // cerr << "n m " << n << ' ' << m << endl;
    // cerr << "is_face" << endl;
    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0 ; j < m; ++j) {
    //     cerr << is_face[i][j];
    //   }
    //   cerr << endl;
    // }
  }

  cout << cntans[1] << ' ' << cntans[2] << ' ' << cntans[0] << endl;
}
