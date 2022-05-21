#include <bits/stdc++.h>
using namespace std;


int main() {
  int n; 
  cin >> n;
  string s;
  cin >> s;
  vector<int> match(n, -1);

  stack<int> le;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') le.push(i);
    else if (s[i] == ')') {
      int l = le.top();
      le.pop();
      match[l] = i;
      match[i] = l;
    }
  }

  assert(le.empty());

  vector<int> ord;

  auto dfs = [&](auto dfs, int now) -> void {
    if (now == n) return;
    if (s[now] == '(') {
      dfs(dfs, now + 1);
      ord.push_back(now);
      dfs(dfs, match[now] + 1);
    } else if (s[now] == ')') {
      ord.push_back(now);
      return;
    } else {
      ord.push_back(now);
      dfs(dfs, now + 1);
    }
  };

  dfs(dfs, 0);

  for (int i = 0; i < n; ++i) {
    cout << ord[i] + 1 << " \n"[i == n - 1];
  }

}

