#include <bits/stdc++.h>
using namespace std;

#define data bitset<30>

bool cmp(const data &a, const data &b) {
  return a.to_ulong() < b.to_ulong();
}

int main() {
  int n, m; cin >> n >> m;

  auto id = [&](int x, int y) { return x * m + y; };

  data from, to;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < m; ++j) if (s[j] == 'O')
      from.set(id(i, j));
  }

  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    for (int j = 0; j < m; ++j) if (s[j] == 'O')
      to.set(id(i, j));
  }

  if (from == to) exit((cout << 1 << endl, 0));

  set<data, decltype(&cmp)> st(cmp);
  queue<data> q;
  st.insert(from);
  q.push(from);

  while (q.size()) {
    data now = q.front();
    q.pop();

    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (now[id(i, j)]) {
      data tmp = now;
      for (int i = 0; i < n; ++i) tmp.set(id(i, j));
      for (int j = 0; j < m; ++j) tmp.set(id(i, j));
      tmp.reset(id(i, j));
      
      if (tmp == to) exit((cout << 1 << endl, 0));
      if (st.count(tmp));
      else {
        st.insert(tmp);
        q.push(tmp);
      }
    }
  }

  cout << 0 << endl;


}
