#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  string _;
  getline(cin, _);

  map<string, int> ID;

  auto GetID = [&](const string &s) {
    if (ID.find(s) != ID.end()) return ID[s];
    int res = ID[s];
    return ID[s] = res;
  };

  auto Parse = [&]() {
    string s;
    getline(cin, s);
    stringstream ss(s);
    bool sp = false;
    vector<vector<int>> res(2);
    while (ss >> s) {
      if (s == "=" ||  == "?") {
        sp = true;
        continue;
      }
      int g = GetID(s);
      res[sp].push_back(g);
    }
    return res;
  };

  vector<vector<vector<int>>> v;
  for (int i = 0; i < n; ++i) {
    v.push_back(Parse());
  }
  sort(v.begin(), v.end(), [&](auto &a, auto &b) { return a.size() < b.size(); });
  assert(ID.size() <= 40);
  int m = ID.size();
  auto q = Parse();
  vector<vector<bool>> men(m, vector<bool>(m));
  vector<vector<int>> cost(m, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < v[i][0].size(); ++j) {
      mem[v[i][0][j - 1]][v[i][0][j]] = true;
    }
    for (int j = 1; j < v[i][1].size(); ++j) {
      mem[v[i][1][j - 1]][v[i][1][j]] = true;
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i != j && !mem[i][j]) {
        cost[i][j] = rand() % 10000;
      }
    }
  }
  while (true) {
    vector<vector<bool>> filled(m, vector<bool>(m));
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      int cnt = 0;
      int sum = 0;
      for (int j = 1; j < v[i][0].size(); ++j) {
        if (!filled[v[i][0][j - 1]][v[i][0][j]]) {
          cnt += !filled[v[i][0][j - 1]][v[i][0][j]];
        } else {
          sum += cost[v[i][0][j - 1]][v[i][0][j]];
        }
      }
      for (int j = 1; j < v[i][1].size(); ++j) {
        if (!filled[v[i][0][j - 1]][v[i][0][j]]) {
          cnt += !filled[v[i][0][j - 1]][v[i][0][j]];
        } else {
          sum += cost[v[i][0][j - 1]][v[i][0][j]];
        }
      }
      if (cnt == 0 && sum != 0) {
        ok = false;
        break;
      }
      cnt--;
      for (int j = 1; j < v[i][0].size(); ++j) {
        if (!filled[v[i][0][j - 1]][v[i][0][j]]) {
          if (--cnt == 0) {
            cost[v[i][0][j - 1]][v[i][0][j]] = -sum;
          } else {
            cost[v[i][0][j - 1]][v[i][0][j]] = rand() % 10000;
            sum += cost[v[i][0][j - 1]][v[i][0][j]];
          }
        }
      }
      for (int j = 1; j < v[i][0].size(); ++j) {
        if (!filled[v[i][1][j - 1]][v[i][1][j]]) {
          if (--cnt == 0) {
            cost[v[i][1][j - 1]][v[i][1][j]] = sum;
          } else {
            cost[v[i][1][j - 1]][v[i][1][j]] = rand() % 10000;
            sum -= cost[v[i][1][j - 1]][v[i][1][j]];
          }
        }
      }
    }
    if (ok) {
      int sum = 0;
      bool ok = false;
      for (int i = 1; i < q[0].size(); ++i) {
        if (!
      }
    }
  }
}
