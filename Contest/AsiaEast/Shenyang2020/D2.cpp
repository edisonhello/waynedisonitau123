#include <bits/stdc++.h>
using namespace std;

vector<string> all;
int64_t _C[305][305];

void init() {
  _C[0][0] = 1;
  for (int i = 1; i <= 300; ++i) {
    for (int j = 0; j <= i; ++j) {
      _C[i][j] += _C[i - 1][j];
      if (j) _C[i][j] += _C[i - 1][j - 1];

      if (_C[i][j] >= 1000) _C[i][j] = 10000;
    }
  }
}

int C(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x;
  if (x >= 100) return 10000;
  return _C[x][y];
}

void add(vector<int> &pfx) {
  string s;
  for (int i = 1; i < (int)pfx.size(); ++i) {
    if (pfx[i - 1] == pfx[i]) {
      s += "b";
    } else s += "r";
  }
  all.push_back(s);
}

void dfs(vector<int> &pfx, int curn, int c0, int c1, int pcnt) {
  assert(c0 >= 0 && c1 >= 0);
  if (pcnt <= 0) return;
  if (c0 == 0 && c1 == 0) { add(pfx); return; }
  if (c0 == 0) {
    pfx.push_back(1);
    dfs(pfx, curn ^ 1, c0, c1 - 1, pcnt);
    pfx.pop_back();
    return;
  }
  if (c1 == 0) {
    pfx.push_back(0);
    dfs(pfx, curn, c0 - 1, c1, pcnt);
    pfx.pop_back();
    return;
  }

  if (pfx.back() == 0) {
    // put 0 first
    int CC = C(c0 + c1 - 1, c0 - 1);
    if (CC >= pcnt) {
      pfx.push_back(0);
      dfs(pfx, 0, c0 - 1, c1, pcnt);
      pfx.pop_back();
    } else {
      pfx.push_back(0);
      dfs(pfx, 0, c0 - 1, c1, CC);
      pfx.back() = 1;
      dfs(pfx, 1, c0, c1 - 1, pcnt - CC);
      pfx.pop_back();
    }
  } else {
    // put 1 first
    int CC = C(c0 + c1 - 1, c1 - 1);
    if (CC >= pcnt) {
      pfx.push_back(1);
      dfs(pfx, 0, c0, c1 - 1, pcnt);
      pfx.pop_back();
    } else {
      pfx.push_back(1);
      dfs(pfx, 0, c0, c1 - 1, CC);
      pfx.back() = 0;
      dfs(pfx, 1, c0 - 1, c1, pcnt - CC);
      pfx.pop_back();
    }
  }
}

void get100(int c0, int c1) {
  if (c0 == 0) return;
  vector<int> pfx = {0};
  dfs(pfx, 0, c0 - 1, c1, 200);
}

int main() {
  init();

  int n; cin >> n;

  if (n == 1) {
    cout << 1 << endl;
    cout << "r" << endl;
    exit(0);
  }

  if (n % 2 == 0) {
    vector<string> tmpall;
    get100(n / 2, n / 2 + 1);
    tmpall.swap(all);
    get100(n / 2 + 1, n / 2);
    vector<string> tmp;
    reverse(tmpall.begin(), tmpall.end());
    reverse(all.begin(), all.end());

    while (tmpall.size() || all.size()) {
      if (tmpall.empty()) {
        tmp.push_back(all.back());
        all.pop_back();
      } else if (all.empty()) {
        tmp.push_back(tmpall.back());
        tmpall.pop_back();
      } else if (all.back() < tmpall.back()) {
        tmp.push_back(all.back());
        all.pop_back();
      } else {
        tmp.push_back(tmpall.back());
        tmpall.pop_back();
      }
    }

    tmp.swap(all);
  }
  else get100(n / 2 + 1, n / 2 + 1);

  // sort(all.begin(), all.end());

  if (all.size() > 100u) all.resize(100);
  
  cout << ((n + 1) / 2) * 1ll * ((n + 2) / 2) << endl;
  for (string s : all) cout << s << '\n';
}
