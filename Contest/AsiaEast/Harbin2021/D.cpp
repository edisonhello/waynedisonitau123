#include <bits/stdc++.h>
using namespace std;
#define i128 __int128

i128 parse(string s) {
  i128 v = 0;
  for (char c : s) {
    v = v * 10 + (c & 15);
  }
  return v;
}

string iparse(i128 v) {
  if (v == 0) return "0";
  stack<int> st;
  while (v > 0) {
    st.push(v % 10);
    v /= 10;
  }
  string s;
  while (st.size()) {
    s += char(st.top() + '0');
    st.pop();
  }
  return s;
}

void solve() {
  string s, t;
  cin >> s >> t;

  int n = s.size(), m = t.size();

  i128 sv = parse(s), tv = parse(t);

  i128 mins = sv;

  // erased
  for (int z = 0; z < (1 << n); ++z) {
    string ss;

    vector<int> ers(10, 0), ert(10, 0);
    for (int i = 0; i < n; ++i) {
      if (z & (1 << i))
        ers[s[i] & 15]++;
      else
        ss += s[i];
    }

    // empty str
    if (ss.empty()) continue;

    // cerr << "ss = " << ss << endl;

    i128 ssv = parse(ss);

    if (ssv == 0) continue;

    if (ssv * tv % sv) continue;
    i128 ttv = ssv * tv / sv;

    string tt = iparse(ttv);

    int cnt0 = t.length() + ss.length() - tt.length() - s.length();
    if (cnt0 > 0) 
      tt = string(cnt0, '0') + tt;

    int ti = 0;
    int bad = 0;
    for (char c : tt) {
      while (ti < m && t[ti] != c) {
        ert[t[ti] & 15]++;
        ++ti;
      }

      if (ti >= m || t[ti] != c) {
        bad = 1;
        break;
      }

      ++ti;
    }
    while (ti < m) {
      ert[t[ti] & 15]++;
      ++ti;
    }

    if (bad) continue;
    if (ers != ert) continue;

    mins = min(mins, ssv);
  }

  cout << iparse(mins) << ' ' << iparse(mins * tv / sv) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) solve();
}

