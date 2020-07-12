#include <bits/stdc++.h>
using namespace std;

string Next(string s) {
  string t;
  for (int i = 0; i < (int)s.size();) {
    int j;
    for (j = i + 1; j < (int)s.size() && s[i] == s[j]; ++j);
    t += char(j - i + '0');
    t += s[i];
    i = j;
  }
  return t;
}

string Cut(string s, int m) {
  if (m > (int)s.size()) return s;
  return s.substr(s.size() - m, m);
}

void Test() {
  string s = "1";
  for (int i = 1; i <= 50; ++i) {
    cout << i << ' ' << s << endl;
    s = Next(s);
    s = Cut(s, 100);
  }
  exit(0);
}

int main() {
  // Test();

  long long n; cin >> n;
  int m; cin >> m;

  if (n <= 50) {
    string s = "1";
    for (int i = 2; i <= n; ++i) {
      // cout << i << ' ' << s << ' ' << s.size() << endl;
      s = Next(s);
    }

    cout << Cut(s, m) << endl;
  } else {
    string s;
    if (n % 4 == 0) s = "3211322211312113211";
    else if (n % 4 == 1) s = "3322113111221131221";
    else if (n % 4 == 2) s = "2211331222113112211";
    else if (n % 4 == 3) s = "2212311322113212221";

    for (int i = 0; i < 40; ++i) s = Next(s);

    cout << Cut(s, m) << endl;
  }

}
