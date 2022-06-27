#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M;
  cin >> N >> M;
  vector<int> cap(M);
  for (int i = 0; i < M; ++i) {
    cin >> cap[i];
  }
  vector<vector<int>> cust(N);
  vector<vector<int>> rest(M);
  cin.ignore();
  for (int i = 0; i < N; ++i) {
    string s;
    getline(cin, s);
    stringstream ss(s);
    int x;
    while (ss >> x) {
      cust[i].push_back(x - 1);
    }
  }
  vector<map<int, int>> rnk(N);
  for (int i = 0; i < M; ++i) {
    string s;
    getline(cin, s);
    stringstream ss(s);
    int x;
    int j = 0;
    while (ss >> x) {
      if (x == 0) {
        break;
      }
      rest[i].push_back(x - 1);
      rnk[x - 1][i] = j;
      j++;
    }
  }
  vector<int> que(N);
  iota(que.begin(), que.end(), 0);
  vector<int> iter(N);
  vector<int> ans(N, -1);
  vector<set<pair<int, int>>> cur(M);
  while (!que.empty()) {
    vector<int> vec;
    for (int x : que) {
      if (iter[x] >= cust[x].size()) {
        ans[x] = -1;
        continue;
      }
      int y = cust[x][iter[x]++];
      cur[y].insert(make_pair(rnk[x][y], x));
      vec.push_back(y);
      ans[x] = y;
    }
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    vector<int> nque;
    for (int y : vec) {
      while (cur[y].size() > cap[y]) {
        int x = cur[y].rbegin()->second;
        nque.push_back(x);
        cur[y].erase(make_pair(rnk[x][y], x));
      }
    }
    que.swap(nque);
  }
  vector<int> res;
  for (int i = 0; i < N; ++i) {
    if (ans[i] != -1) {
      res.push_back(i);
    }
  }
  sort(res.begin(), res.end());
  for (int u : res) {
    cout << u + 1 << "\n";
  }
  return 0;
}
