  #include <bits/stdc++.h>
  using namespace std;
   
  const int kN = 1'000'000 + 5;
  int nd[kN][4];
  vector<int> ch[kN];
   
  int Node() {
      static int sz = 0;
      for (int i = 0; i < 4; ++i) nd[sz][i] = -1;
      return sz++;
  }
   
  int Parse(char c) {
      if (c == 'A') return 0;
      if (c == 'C') return 1;
      if (c == 'G') return 2;
      if (c == 'T') return 3;
  }
   
  void Insert(const string &s, int r, int id) {
      for (int i = 0; i < s.size(); ++i) {
          int j = Parse(s[i]);
          if (nd[r][j] == -1) nd[r][j] = Node();
          r = nd[r][j];
      }
      ch[r].push_back(id);
  }
   
  vector<pair<int, int>> z;
  long long ans;
   
  void Dfs(int x, int d = 0) {
      for (int i = 0; i < 4; ++i) {
          if (nd[x][i] != -1) {
              Dfs(nd[x][i], d + 1);
              move(ch[nd[x][i]].begin(), ch[nd[x][i]].end(), back_inserter(ch[x]));
          }
      }
      while (ch[x].size() >= 2) {
          int a = ch[x].back(); ch[x].pop_back();
          int b = ch[x].back(); ch[x].pop_back();
          z.emplace_back(a, b);
          ans += d;
      }
  }
   
  int main() {
      ios_base::sync_with_stdio(0); cin.tie(0);
      int n; cin >> n;
      int rt = Node();
      for (int i = 0; i < n; ++i) {
          string s; cin >> s;
          Insert(s, rt, i);
      }
      Dfs(rt);
      cout << ans << '\n';
      for (auto &v : z) cout << v.first + 1 << ' ' << v.second + 1 << '\n';
  }
