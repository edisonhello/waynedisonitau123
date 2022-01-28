#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  string s;
  cin >> s;

  if (count(s.begin(), s.end(), 'A') == N && count(s.begin(), s.end(), 'B') == N && count(s.begin(), s.end(), 'C') == N) {
    cout << "0\n";
    return 0;
  }

  vector<vector<int>> pref(3 * N + 1, vector<int>(3));
  for (int i = 0; i < 3 * N; ++i) {
    for (int j = 0; j < 3; ++j) {
      pref[i + 1][j] = pref[i][j];
    }
    pref[i + 1][s[i] - 'A']++;
  }

  vector<unordered_map<int, int>> prv(3);
  for (int c = 0; c < 3; ++c) {
    prv[c][0] = 0;
  }
  for (int r = 1; r <= 3 * N; ++r) {
    for (int c = 0; c < 3; ++c) {
      int x = pref[3 * N][c] - pref[r][c];
      if (prv[c].find(N - x - r) != prv[c].end()) {
        int l = prv[c][N - x - r];
        assert(pref[l][c] + pref[3 * N][c] - pref[r][c] + (r - l) == N);
        bool ok = true;
        for (int d = 0; d < 3; ++d) {
          if (d == c) {
            continue;
          }
          if (pref[l][d] + pref[3 * N][d] - pref[r][d] != N) {
            ok = false;
          }
        }
        if (ok) {
          cout << "1\n";
          cout << l + 1 << " " << r << " " << static_cast<char>(c + 'A') << "\n";
          return 0;
        }
      }
      prv[c][pref[r][c] - r] = r;
    }
  }

  vector<int> cnt(3);
  for (int i = 0; i < 3 * N; ++i) {
    if (++cnt[s[i] - 'A'] == N) {
      cout << 2 << "\n";
      char B = (s[i] - 'A' + 1) % 3 + 'A';
      char C = (s[i] - 'A' + 2) % 3 + 'A';
      cout << i + 2 << " " << 3 * N << " " << B << "\n";
      int cnt_b = pref[i + 1][B - 'A'];
      assert(cnt_b < N);
      cout << i + 2 << " " << 3 * N - (N - cnt_b) << " " << C << "\n";
      return 0;
    }
  }

  assert(false);
}

