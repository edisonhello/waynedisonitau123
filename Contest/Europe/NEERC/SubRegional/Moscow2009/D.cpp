#include <bits/stdc++.h>
using namespace std;

void NO() {
  cout << "IMPOSSIBLE" << endl;
  exit(0);
}
void YES(string s) {
  cout << s << endl;
  exit(0);
}

int main() {
  freopen("delivery.in", "r", stdin);
  freopen("delivery.out", "w", stdout);

  int n, m, a = 1, b, c, d; cin >> n >> m >> b >> c >> d;
  char st; cin >> st;

  if (a == c && b == d) YES("");

  if (m == 1) {
    if (c == 1) {
      exit(0);
    } else if (st == 'F') {
      NO();
    } else if (st == 'T') {
      if (c == 2) cout << "F" << endl;
      else NO();
      exit(0);
    } else if (st == 'B') {
      if (c == 2) cout << "F" << endl;
      else if (c == 3) cout << "FF" << endl;
      else NO();
      exit(0);
    } else {
      for (int i = 0; i < c - 1; ++i) cout << "F";
      cout << endl;
      exit(0);
    }
  } else if (n == 1) {
    if (d == b) exit(0);
    else if (st == 'L') {
      if (d < b) NO();
      if (d == b + 1) YES("R");
      if (d == b + 2) YES("RR");
      NO();
    } else if (st == 'R') {
      if (d > b) NO();
      if (d == b - 1) YES("L");
      if (d == b - 2) YES("LL");
      NO();
    } else if (st == 'T') {
      if (d == b - 1) YES("L");
      if (d == b + 1) YES("R");
      NO();
    } else {
      if (d < b) {
        for (int i = 0; i < b - d; ++i) cout << "L";
        YES("");
      } else {
        for (int i = 0; i < d - b; ++i) cout << "R";
        YES("");
      }
    }
  } else if (st == 'F') {
    if (c != 1) NO();
    if (d == b) exit(0);
    else {
      if (d < b) {
        for (int i = 0; i < b - d; ++i) cout << "L";
        YES("");
      } else {
        for (int i = 0; i < d - b; ++i) cout << "R";
        YES("");
      }
    }
  } else if (st == 'L' && b == m) {
    if (d != m) NO();
    for (int i = 0; i < c - 1; ++i) cout << "F";
    cout << endl;
    exit(0);
  } else if (st == 'R' && b == 1) {
    if (d != 1) NO();
    for (int i = 0; i < c - 1; ++i) cout << "F";
    cout << endl;
    exit(0);
  } else if (c == 1) {
    if (st == 'T') {
      if (b > 1) cout << "LFRB", st = 'B';
      else if (b < m) cout << "RFLB", st = 'B';
    } else if (st == 'L') {
      assert(b < m);
      cout << "FRBL", st = 'B';
    } else if (st == 'R') {
      assert(b > 1);
      cout << "FLBR", st = 'B';
    }
    if (d < b) {
      for (int i = 0; i < b - d; ++i) cout << "L";
      YES("");
    } else {
      for (int i = 0; i < d - b; ++i) cout << "R";
      YES("");
    }
  } else if (st == 'T' || st == 'B') {
    if (st == 'B') {
      if (b > 1) cout << "FLBR", st = 'T';
      else cout << "FRBL", st = 'T';
    }
    if (b > 1) {
      cout << "L";
      --b;
      st = 'L';
      while (a < c - 1) ++a, cout << "F";
      cout << "RF";
      ++a, ++b;
      st = 'F';
    } else {
      cout << "R";
      ++b;
      st = 'R';
      while (a < c - 1) ++a, cout << "F";
      cout << "LF";
      ++a; --b;
      st = 'F';
    }
    if (d < b) {
      for (int i = 0; i < b - d; ++i) cout << "L";
      YES("");
    } else {
      for (int i = 0; i < d - b; ++i) cout << "R";
      YES("");
    }
  } else if (st == 'L') {
    while (a < c - 1) ++a, cout << "F";
    ++a, ++b; cout << "RF"; st = 'F';
    if (d < b) {
      for (int i = 0; i < b - d; ++i) cout << "L";
      YES("");
    } else {
      for (int i = 0; i < d - b; ++i) cout << "R";
      YES("");
    }
  } else if (st == 'R') {
    while (a < c - 1) ++a, cout << "F";
    cout << "LF"; ++a; --b; st = 'F';
    if (d < b) {
      for (int i = 0; i < b - d; ++i) cout << "L";
      YES("");
    } else {
      for (int i = 0; i < d - b; ++i) cout << "R";
      YES("");
    }
  }
}
