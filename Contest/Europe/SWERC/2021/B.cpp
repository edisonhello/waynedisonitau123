#include <bits/stdc++.h>
using namespace std;

int cnt[256][3];

int main() {
  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;

  for (char c : s1) ++cnt[c][0];
  for (char c : s2) ++cnt[c][1];
  for (char c : s3) ++cnt[c][2];

  int lim = min(min(s1.size(), s2.size()), s3.size());
  int now = 0;
  vector<string> ans;

  s1.clear();
  s2.clear();
  s3.clear();

  for (int i = 'A'; i <= 'Z'; ++i) {
    int a = cnt[i][0];
    int b = cnt[i][1];
    int c = cnt[i][2];
    int ab = (a + b - c + 1) / 2;
    int ac = (a + c - b) / 2;
    int bc = (b + c - a) / 2;

    if (a > b + c) {
      ab = b;
      ac = c;
      bc = 0;
    } else if (b > a + c) {
      ab = a;
      ac = 0;
      bc = c;
    } else if (c > a + b) {
      ab = 0;
      ac = a;
      bc = b;
    }

    // cout << "a b c ab ac bc " << a << ' ' << b<< ' ' << c << ' ' << ab << ' ' << ac << ' '<< bc << endl;

    a -= ab + ac;
    b -= ab + bc;
    c -= ac + bc;

    while (ab > 0 && now < lim) {
      string ts;
      ++now;
      --ab;
      --cnt[i][0];
      --cnt[i][1];
      ts += string(1, i) + '3';
      ans.push_back(ts);
    }

    while (ac > 0 && now < lim) {
      string ts;
      ++now;
      --ac;
      --cnt[i][0];
      --cnt[i][2];
      ts += string(1, i) + '2';
      ans.push_back(ts);
    }

    while (bc > 0 && now < lim) {
      string ts;
      ++now;
      --bc;
      --cnt[i][1];
      --cnt[i][2];
      ts += string(1, i) + '1';
      ans.push_back(ts);
    }

    a += ab + ac;
    b += ab + bc;
    c += ac + bc;

    while (a > 0) {
      --a;
      s1 += char(i);
    }

    while (b > 0) {
      --b;
      s2 += char(i);
    }

    while (c > 0) {
      --c;
      s3 += char(i);
    }
  }

  // cout << "s1 s2 s3 left " << s1 << ' ' << s2 << ' ' << s3 << endl;

  for (auto &s : ans) {
    if (s[1] == '1') {
      if (s1.size()) {
        s[1] = s1.back();
        s1.pop_back();
      } else {
        s[1] = 'Z';
      }
    } else if (s[1] == '2') {
      if (s2.size()) {
        s[1] = s2.back();
        s2.pop_back();
      } else {
        s[1] = 'Z';
      }
    } else if (s[1] == '3') {
      if (s3.size()) {
        s[1] = s3.back();
        s3.pop_back();
      } else {
        s[1] = 'Z';
      }
    }
  }

  if (s2.size() > s1.size()) swap(s1, s2);
  if (s3.size() > s1.size()) swap(s1, s3);
  // s1 longest

  if (s1.size() >= s2.size() + s3.size()) {
    while (s1.size()) {
      string ts;
      ts += s1.back();
      s1.pop_back();

      if (s2.size()) {
        ts += s2.back();
        s2.pop_back();
      } else if (s3.size()) {
        ts += s3.back();
        s3.pop_back();
      } else {
        ts += "Z";
      }

      ans.push_back(ts);
    }
  } else {
    if ((s1.size() + s2.size() + s3.size()) & 1) {
      s3 += 'A';
    }

    string s = s1 + s2 + s3;
    string t = s.substr(s.size() / 2);
    for (int i = 0; i < (int)t.size(); ++i) {
      string st;
      st += s[i];
      st += t[i];
      ans.push_back(st);
    }
  }

  cout << ans.size() << endl;
  for (auto s : ans) {
    cout << s << endl;
  }
}

