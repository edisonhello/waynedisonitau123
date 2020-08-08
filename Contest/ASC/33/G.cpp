#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("nimfor3.in", "r", stdin);
  freopen("nimfor3.out", "w", stdout);
  string s;
  cin >> s;
  bool w = false;
  if (s[0] > s[1]) {
    swap(s[0], s[1]);
    w = true;
  }

  auto Print = [&](vector<int> a, vector<int> b) {
    cout << "YES\n";
    if (w) {
      swap(a, b);
    }
    for (int u : a) cout << u << " ";
    cout << "\n";
    for (int u : b) cout << u << " ";
    cout << "\n";
    exit(0);
  };

  string t = s.substr(0, 2);
  if (t == "NN") {
    if (s[2] == 'Q') {
      Print({2}, {2});
    }
    if (s[2] == 'O') {
      Print({1}, {1});
    }
    if (s[2] == 'N') {
      Print({1, 1, 2}, {1});
    }
  }
  if (t == "NO") {
    if (s[2] == 'Q') {
      Print({1, 1, 2}, {1, 1});
    }
    if (s[2] == 'N') {
      Print({2}, {1, 1});
    }
    if (s[2] == 'P') {
      Print({1}, {1, 1});
    }
  }
  if (t == "NP") {
    if (s[2] == 'N') {
      Print({1}, {0});
    }
  }
  if (t == "NQ") {
    if (s[2] == 'Q') {
      Print({1}, {2, 2});
    }
    if (s[2] == 'N') {
      Print({1}, {1, 2});
    }
  }
  if (t == "OO") {
    if (s[2] == 'N') {
      Print({1, 1}, {1, 1});
    }
  }
  if (t == "OP") {
    if (s[2] == 'O') {
      Print({1, 1}, {0});
    }
  }
  if (t == "OQ") {
    if (s[2] == 'Q') {
      Print({1, 1}, {2, 2});
    }
    if (s[2] == 'N') {
      Print({1, 1}, {1, 2});
    }
  }
  if (t == "PP") {
    if (s[2] == 'P') {
      Print({0}, {0});
    }
  }
  if (t == "PQ") {
    if (s[2] == 'Q') {
      Print({0}, {2, 2});
    }
  }
  if (t == "QQ") {
    if (s[2] == 'Q') {
      Print({2, 2}, {2, 2});
    }
  }
  cout << "NO\n";
}
