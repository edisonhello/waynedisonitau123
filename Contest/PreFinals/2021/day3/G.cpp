#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 1, 1, 0, -1, -1};
const int dy[] = {1, 0, -1, -1, 0, 1};

unordered_map<int64_t, int64_t> djs;
unordered_map<int64_t, int64_t> sz;

const int64_t id(int x, int y) {
  return x * 2000000000ll + y;
}

void init(int64_t z) {
  djs[z] = z;
  sz[z] = 0;
}

int64_t find(int64_t z) {
  return z == djs[z] ? z : djs[z] = find(djs[z]);
}

void merge(int64_t a, int64_t b) {
  a = find(a);
  b = find(b);
  if (a == b) return;
  djs[a] = b;
  sz[b] += sz[a];
}

void add(int x, int y) {
  init(id(x, y));

  int alr = 0;
  for (int d = 0; d < 6; ++d) {
    int nx = x + dx[d];
    int ny = y + dy[d];

    if (djs.find(id(nx, ny)) != djs.end()) {
      ++alr;
      merge(id(x, y), id(nx, ny));
    }
  }

  int dans = 6 - alr * 2;
  sz[find(id(x, y))] += dans;
}

int64_t query(int x, int y) {
  int64_t z = find(id(x, y));
  return sz[z];
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n; while (n--) {
    int op, x, y; cin >> op >> x >> y;
    if (op == 1) {
      add(x, y);
    } else {
      cout << query(x, y) << '\n';
    }
  }
}
