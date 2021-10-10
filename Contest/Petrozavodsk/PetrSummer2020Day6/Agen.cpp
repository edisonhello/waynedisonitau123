#include <bits/stdc++.h>
using namespace std;

string gen(string m, string r) {
  string ans;
  for (char c : r) {
    if (c == '$') ans += m;
    else ans += c;
  }
  return ans;
}

int main() {
  srand(time(0) * clock());

  int n = rand() % 10 + 1;
  string os;
  for (int i = 0; i < n; ++i) os += char(rand() % 26 + 'a');
  cout << os << endl;

  string r;
  int m = rand() % 10 + 1;
  for (int i = 0; i < m; ++i) r += char(rand() % 26 + 'a');
  
  int $ = rand() % 3 + 1;
  $ = min($, m);
  while ($--) {
    r[rand() % m] = '$';
  }

  cout << r << endl;
  
  int k = rand() % 4 + 1;
  int q = rand() % 10 + 1;
  cout << k << ' ' << q << endl;

  while (k--) {
    os = gen(os, r);
  }

  int nn = os.size();

  while (q--) {
    int l = rand() % nn + 1;
    int r = rand() % nn + 1;
    if (r < l) swap(l, r);
    cout << l << ' ' << r << endl;
  }

}
