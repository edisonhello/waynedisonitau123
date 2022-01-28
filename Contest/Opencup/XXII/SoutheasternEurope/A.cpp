#include <bits/stdc++.h>
using namespace std;

void NO() {
  cout << "NO" << endl;
  exit(0);
}

int main() {
  int n;
  cin >> n;
  n *= 2;

  string s;
  cin >> s;

  vector<pair<int, int>> anss;
  int cnt[3] = {0};

  for (int i = 0; i < n; ++i) {
    char c = s[i];
    int x = c - 'A';
    ++cnt[x];
  }

  int A = cnt[0];
  int B = cnt[1];
  int C = cnt[2];
  if (A > n / 2 || C > n / 2)
    NO();

  int t = A - C;

  int x = (t + B) / 2;
  int y = B - x;

  vector<int> used(n, 0);
  deque<int> xb, yb;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'B') {
      if (yb.size() == y) {
        xb.push_back(i);
      } else {
        yb.push_back(i);
      }
    }
  }

  for (int i = n - 1; i >= 0; --i) {
    if (s[i] == 'A') {
      if (xb.size() && i < xb.back()) {
        anss.emplace_back(i, xb.back());
        used[i] = used[xb.back()] = 1;
        xb.pop_back();
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'C') {
      if (yb.empty() || i < yb.front()) {
      } else {
        anss.emplace_back(yb.front(), i);
        used[i] = used[yb.front()] = 1;
        yb.pop_front();
      }
    }
  }


  vector<int> as;
  for (int i = 0; i < n; ++i) {
    if (used[i]) continue;
    if (s[i] == 'A') as.emplace_back(i);
    else if (s[i] == 'C') {
      if (as.empty()) NO();
      anss.emplace_back(as.back(), i);
      as.pop_back();
    }

  }


  if (anss.size() == n / 2) {
    cout << "YES" << endl;
    for (auto [u, v] : anss) {
      cout << u + 1 << ' ' << v + 1 << '\n';
    }
  } else {
    cout << "NO" << endl;
  }

}

