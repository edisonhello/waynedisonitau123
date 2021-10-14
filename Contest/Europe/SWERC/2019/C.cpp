#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; cin >> n;
  set<long long> st;
  for (int i = 0; i < n; ++i) {
    string s; cin >> s;
    if (s.size() >= 9) continue;
    if (s[0] == '-') continue;
    long long v = atoi(s.c_str());
    st.insert(v);
  }

  for (int i = 0; ; ++i) {
    if (st.count(i) == 0) {
      cout << i << endl;
      exit(0);
    }
  }
}
