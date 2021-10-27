#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

bitset<6005> skip[3005];
bitset<6005> er[3005];
bitset<6005> edl[3005], edr[3005];

short gdl[3005][6005], gdr[3005][6005], gd[3005][6005];

bitset<6005> added[3005];

vector<pair<short, short>> add_at[3005];

pair<short, short> zcor[3005][6005];

short bit[5005][5005];

void add(int x, int y, int v) {
  ++y;
  for (int yy = y; yy < 5005; yy += yy & -yy) {
    bit[x][yy] += v;
  }
}

int query(int x, int y) {
  ++y;
  // cout << "q " << x << ' ' << y << endl;
  int v = 0;
  for (; y; y -= y & -y) {
    v += bit[x][y];
  }
  return v;
}

int query(int x, int y1, int y2) {
  return query(x, y2) - query(x, y1 - 1);
}


long long solve(int r, int c, vector<string> &mp) {
  for (int i = 0; i < 3005; ++i) skip[i].reset();
  for (int i = 0; i < 3005; ++i) er[i].reset();
  for (int i = 0; i < 3005; ++i) edl[i].reset();
  for (int i = 0; i < 3005; ++i) edr[i].reset();
  memset(gdl, 0, sizeof(gdl));
  memset(gdr, 0, sizeof(gdr));
  memset(gd, 0, sizeof(gd));
  for (int i = 0; i < 3005; ++i) added[i].reset();
  for (int i = 0; i < r; ++i) add_at[i].clear();
  memset(bit, 0 ,sizeof(bit));

  for (int i = 0; i < r; ++i) {
    if (!(i & 1)) {
      for (int j = 0; j < c - 2; j += 2) {
        if (mp[i * 2][j * 2 + 2] == '-') {
          er[i][j] = 1;
          //cerr << "er " << i << ' ' << j << endl;
        }
      }
      if (i < r - 1) {
        for (int j = 0; j < c - 1; j += 2) {
          if (mp[i * 2 + 1][j * 2 + 1] == '\\') {
            edr[i][j] = 1;
            //cerr << "edr " << i << ' ' << j << endl;
          }
        }
        for (int j = 2; j < c; j += 2) {
          if (mp[i * 2 + 1][j * 2 - 1] == '/') {
            edl[i][j] = 1;
            //cerr << "edl " << i << ' ' << j << endl;
          }
        }
      }
      for (int j = 1; j < c; j += 2) skip[i][j] = 1;
    } else {
      for (int j = 1; j < c - 1; j += 2) {
        if (mp[i * 2][j * 2 + 2] == '-') {
          er[i][j] = 1;
          //cerr << "er " << i << ' ' << j << endl;
        }
      }
      if (i < r - 1) {
        for (int j = 1; j < c - 1; j += 2) {
          if (mp[i * 2 + 1][j * 2 + 1] == '\\') {
            edr[i][j] = 1;
            //cerr << "edr " << i << ' ' << j << endl;
          }
        }
        for (int j = 1; j < c; j += 2) {
          if (mp[i * 2 + 1][j * 2 - 1] == '/') {
            edl[i][j] = 1;
            //cerr << "edl " << i << ' ' << j << endl;
          }
        }
      }
      for (int j = 0; j < c; j += 2) skip[i][j] = 1;
    }
  }

  for (int i = r - 1; i >= 0; --i) {
    for (int j = 0; j < c; ++j) if (!skip[i][j]) {
      if (edl[i][j]) gdl[i][j] = gdl[i + 1][j - 1] + 1;
      if (edr[i][j]) gdr[i][j] = gdr[i + 1][j + 1] + 1;
      gd[i][j] = min(gdl[i][j], gdr[i][j]);
      //cerr << "gd " << i << ' ' << j << " = " << gd[i][j] << endl;
      if (gd[i][j]) {
        add_at[i + gd[i][j]].emplace_back(i, j);
      }

      zcor[i][j] = make_pair((i + j) / 2, (i - j + c) / 2);
    }
  }

  long long ans = 0;
  for (int i = r - 1; i >= 0; --i) {
    for (auto [x, y] : add_at[i]) {
      added[x][y] = 1;

      auto [zx, zy] = zcor[x][y];
      add(zx, zy, 1);
      //cerr << "Add " << zx << ' ' << zy << endl;
    }

    for (int j = 0; j < c; ++j) if (added[i][j]) {
      auto [zx, zy] = zcor[i][j];
      add(zx, zy, -1);
      //cerr << "Remove " << zx << ' ' << zy << endl;
    }

    for (int j = i & 1; j < c; ) {
      int jj = j;
      while (jj + 2 < c && er[i][jj]) jj += 2;

      // [j - jj]

      auto [zx1, zy1] = zcor[i][j];
      auto [zx2, zy2] = zcor[i][jj];
      
      //cerr << "query i j jj " << i << ' ' << j << ' ' << jj << endl;

      for (int jjj = j; jjj <= jj; jjj += 2) {
        auto [zx3, zy3] = zcor[i][jjj];
        ans += query(zx3, zy2, zy3);
      }
      // ans += query(min(zx1, zx2), min(zy1, zy2), max(zx1, zx2), max(zy1, zy2));

      j = jj + 2;
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int r, c; cin >> r >> c;
  cin.ignore();

  vector<string> mp(r * 2 - 1);
  for (int i = 0; i < r * 2 - 1; ++i) {
    getline(cin, mp[i]);
    mp[i].resize(2 * c - 1, ' ');
  }

  if (r % 2 == 0) {
    ++r;
    mp.push_back(string(2 * c - 1, ' '));
    mp.push_back(string(2 * c - 1, ' '));
    for (int i = 0; i < c; ++i) {
      mp.back()[i * 2] = 'x';
    }
  }

  long long ans = solve(r, c, mp);

  reverse(mp.begin(), mp.end());

  if (r % 2 == 0) {
    for (int i = 0; i < r * 2 - 1; ++i) {
      reverse(mp[i].begin(), mp[i].end());
    }
  } else {
    for (string &s : mp) {
      for (char &c : s) {
        if (c == '/') c = '\\';
        else if (c == '\\') c = '/';
      }
    }
  }

  ans += solve(r, c, mp);

  cout << ans << endl;
}

