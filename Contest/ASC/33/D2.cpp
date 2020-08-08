#include <bits/stdc++.h>
using namespace std;

bool vis[255];
bool all_term[255];
bool go_nonempty[255];
vector<string> rules[255];

bool AllTerminals(string s) {
  for (char c : s) {
    if (c < 'a' || c > 'z') return false;
  }
  return true;
}

bool IsVariable(char c) {
  return 'A' <= c && c <= 'Z';
}

void dfs_term(int now) {
  if (vis[now]) return;
  vis[now] = 1;
  for (auto s : rules[now]) {
    if (AllTerminals(s)) {
      all_term[now] = 1;
      break;
    } else {
      bool ok = true;
      for (char i : s) if (IsVariable(i)) {
        if (vis[i] && !all_term[i]) {
          ok = false;
          break;
        } else if (!vis[i]) {
          dfs_term(i);
          if (!all_term[i]) 
            ok = false;
        }
      }
      if (ok) all_term[now] = 1;
    }
  }
}

void dfs_empty(int now) {
  if (vis[now]) return;
  vis[now] = 1;
  for (auto s : rules[now]) {
    bool ok = 1, bad = 0;
    for (char c : s) {
      if (IsVariable(c)) {
        if (!vis[c]) dfs_empty(c);

        if (!go_nonempty[c]) bad = 1;
        else ok = 1;
      } else ok = 1;
    }

    if (ok && !bad) go_nonempty[now] = 1;
  }
}

bool front_term[255], back_term[255];

void try_front(int now, int target, int non_empty) {
  vis[now] = 1;
  
  for (string s : rules[now]) {
    for (int i = 0; i < (int)s.size(); ++i) {
      if (IsVariable(s[i])) {
        if (s[i] == target) {
          if (non_empty)
            front_term[now] = 1;
        }

        if (!vis[s[i]]) {
          try_front(s[i], target, non_empty);
        }

        if (front_term[s[i]]) {
          front_term[now] = 1;
        }

        if (go_nonempty[s[i]]) {
          non_empty = 1;
        }

        if (!all_term[s[i]]) {
          break;
        }
      }
    }
  }
}

void try_back(int now, int target, int non_empty) {
  vis[now] = 1;
  
  for (string s : rules[now]) {
    for (int i = (int)s.size() - 1; i >= 0; --i) {
      if (IsVariable(s[i])) {
        if (s[i] == target) {
          if (non_empty)
            back_term[now] = 1;
        }

        if (!vis[s[i]]) {
          try_back(s[i], target, non_empty);
        }

        if (back_term[s[i]]) {
          back_term[now] = 1;
        }

        if (go_nonempty[s[i]]) {
          non_empty = 1;
        }

        if (!all_term[s[i]]) {
          break;
        }
      }
    }
  }
}

int main() {
  freopen("cyclic.in", "r", stdin);
  freopen("cyclic.out", "w", stdout);

  int n; cin >> n;
  vector<pair<char, string>> rule;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    rules[s[0]].push_back(s.substr(3, s.size() - 3));
  }

  for (int i = 'A'; i <= 'Z'; ++i) dfs_term(i);

  memset(vis, 0, sizeof(vis));
  for (int i = 'A'; i <= 'Z'; ++i) dfs_empty(i);

  // for (int i = 'A'; i <= 'Z'; ++i) {
  //   cerr << char(i) << " non_empty? " << go_nonempty[i] << endl;
  // }


  int ans = 0;
  memset(vis, 0, sizeof(vis));
  try_front('S', 'S', 0);
  ans += front_term['S'];

  memset(vis, 0, sizeof(vis));
  try_back('S', 'S', 0);
  ans += back_term['S'];


  if (ans) {
    cout << "infinite" << endl;
    exit(0);
  }

  cout << "finite" << endl;
}
