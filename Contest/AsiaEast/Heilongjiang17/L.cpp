#include <bits/stdc++.h>
using namespace std;

pair<string, int> Rotate(const string& s) {
  int n = s.size();
  string t = s + s;
  int i = 0, j = 1;
  while (i < n && j < n) {
    int k = 0;
    while (k < n && t[i + k] == t[j + k]) {
      k++;
    }
    if (t[i + k] <= t[j + k]) {
      j += k + 1;
    } else {
      i += k + 1;
    }
    if (i == j) {
      j++;
    }
  }
  int pos = (i < n ? i : j);
  return make_pair(t.substr(pos, n), pos);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  constexpr int kP = 1'000'000'000 + 123;
  constexpr int kQ = 7122;

  int T;
  cin >> T;
  while (T--) {
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int l1, l2;
    cin >> l1 >> l2;

    auto Check = [&](string s, string t) {
      auto [sa, ra] = Rotate(s);
      auto [sb, rb] = Rotate(t);
      if (sa != sb) {
        return false;
      }
      int diff = (ra - rb + n) % n;
      vector<int> ht(n);
      vector<int> pw(n + 1, 1);
      ht[0] = t[0];
      for (int i = 1; i < n; ++i) {
        ht[i] = (1LL * ht[i - 1] * kQ + t[i]) % kP;
      }
      for (int i = 1; i <= n; ++i) {
        pw[i] = 1LL * pw[i - 1] * kQ % kP;
      }

      auto Query = [&](int l, int r) -> int {
        if (l == 0) {
          return ht[r];
        } else {
          return (ht[r] + kP - 1LL * pw[r - l + 1] * ht[l - 1] % kP) % kP;
        }
      };

      int rot = -1;
      for (int l = 1; l <= n; ++l) {
        if (n % l == 0) {
          int h = Query(0, l - 1);
          bool failed = false;
          for (int i = l; i < n; i += l) {
            if (Query(i, i + l - 1) != h) {
              failed = true;
              break;
            }
          }
          if (!failed) {
            rot = l;
            break;
          }
        }
      }
      assert(rot != -1);
      int g = __gcd(abs(l1 - l2), n);
      if (diff % __gcd(rot, g) == 0) {
        return true;
      } else {
        return false;
      }
    };

    if (Check(s, t)) {
      cout << "yes\n";
      continue;
    }

    string a = s.substr(0, l1);
    string b = s.substr(l1);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    if (Check(a + b, t)) {
      cout << "yes\n";
      continue;
    }

    a = s.substr(0, l2);
    b = s.substr(l2);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    if (Check(a + b, t)) {
      cout << "yes\n";
      continue;
    }

    cout << "no\n";
  }
  return 0;
}
