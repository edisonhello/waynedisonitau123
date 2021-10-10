#include <bits/stdc++.h>
using namespace std;

#define fill jiofsdjiosfjiosf

int fill[1000006];
int cant[1000006];

void Bad() {
  cout << "conflict" << endl;
  exit(0);
}

void Block(int x) {
  if (fill[x]) Bad();
  cant[x] = 1;
}

void Fill(int x) {
  if (cant[x]) Bad();
  fill[x] = 1;
}

vector<int> incond[1000006];
int filled[1000006];
int leftcnt[1000006];

int main() {
  int n, m;
  cin >> m >> n;
  cin.ignore();

  vector<pair<vector<int>, int>> conds;

  while (m--) {
    string s;
    getline(cin, s);

    int dash = -1;
    for (int i = 0; i < (int)s.size(); ++i) {
      if (s[i] == '-') {
        assert(s[i + 1] == '>');
        dash = i;
      }
    }

    if (dash == -1) {
      if (s[0] == '!') {
        int x = stoi(s.substr(1));
        // cerr << "x = " << x << endl;
        Block(x);
      } else {
        int x = stoi(s);
        // cerr << "x = " << x << endl;
        Fill(x);
      }
    } else {
      string left = s.substr(0, dash), right = s.substr(dash + 3);

      stringstream lss(left);
      vector<int> list;
      int t;
      while (lss >> t) {
        list.push_back(t);
      }

      // for (int i : list) cerr << i << ' ';
      // cerr << "->";

      if (right[0] == '!') {
        int rx = stoi(right.substr(1));
        conds.emplace_back(list, -rx);
      } else {
        int rx = stoi(right);
        conds.emplace_back(list, rx);
      }
    }
  }

  queue<int> q;

  int nc = conds.size();
  for (int i = 0; i < nc; ++i) {
    for (int j : conds[i].first) {
      incond[j].push_back(i);
      if (fill[j]) ++filled[i];
      ++leftcnt[i];
    }

    if (filled[i] == leftcnt[i]) q.push(i);
  }

  while (q.size()) {
    int now = q.front();
    q.pop();
    int to = conds[now].second;
    if (to < 0) {
      to = -to;
      Block(to);
    } else {
      if (fill[to]) continue;
      Fill(to);
      for (int i : incond[to]) {
        ++filled[i];
        if (filled[i] == leftcnt[i]) q.push(i);
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (fill[i])
      cout << "T";
    else
      cout << "F";
  }
  cout << endl;
}
