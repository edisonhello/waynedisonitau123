#include <bits/stdc++.h>
using namespace std;

string board[22];

void Answer(vector<tuple<char, int, int>> ans, int w, int n) {
  cout << ans.size() << endl;
  for (auto [b, r, p] : ans) {
    cout << b << ' ' << r << ' ' << p << '\n';
  }
}

int main() {
  int w, n;
  cin >> w >> n;
  for (int i = 0; i < n; ++i) cin >> board[i];

  if (w == 4) {
    cout << "1" << endl;
    cout << "I 1 1" << endl;
    return 0;
  }

  vector<tuple<char, int, int>> ans;
  for (int i = 1; i + 2 <= w; ++i) {
    if (board[0][i - 1] == '#' || board[0][i + 1] == '#' ||
        board[0][i] == '#') {
      bool lut = 0, rut = 0;
      ans.emplace_back('T', 2, i);
      for (int Z = i + 2; Z <= w - 2; Z += 2) {
        ans.emplace_back('Z', 0, Z);
      }
      for (int S = i - 2; S >= 1; S -= 2) {
        ans.emplace_back('S', 0, S);
      }
      ans.emplace_back('T', 3, 1);
      ans.emplace_back('T', 1, w - 1);
      if ((i - 1) % 2 == 0) {
        lut = 1;
      }
      if ((w - i) % 2 == 0) {
        rut = 1;
      }

      // cout << "lut rut " << lut << ' ' << rut << endl;

      int st = lut ? 2 : 1;
      int ed = rut ? w - 5 : w - 4;
      for (int Z = st; Z <= ed; Z += 2) {
        ans.emplace_back('Z', 0, Z);
      }

      ans.emplace_back('T', 0, ed + 2);

      // ans.emplace_back('I', 1, I);
      // for (int S = I - 2; S >= 1; S -= 2) {
      //   ans.emplace_back('S', 0, S);
      // }
      // for (int Z = I + 3; Z <= w - 2; Z += 2) {
      //   ans.emplace_back('Z', 0, Z);
      // }
      // if (I % 2 == 0) {
      //   ans.emplace_back('T', 3, 1);
      // }
      // if ((w - I) % 2 == 0) {
      //   ans.emplace_back('T', 1, w - 1);
      // }

      // ans.emplace_back('S', 0, I + 1);

      // bool lut = 0, rut = 0;
      // if (I % 2 == 1) {
      //   lut = 1;
      //   ans.emplace_back('T', 3, 1);
      // }
      // if ((w - I) % 2 == 1) {
      //   rut = 1;
      //   ans.emplace_back('T', 1, w - 1);
      // }
      // for (int Z = lut ? 2 : 1; Z < I; Z += 2) {
      //   ans.emplace_back('Z', 0, Z);
      // }
      // for (int S = rut ? w - 3 : w - 2; S >= I + 4; S -= 2) {
      //   ans.emplace_back('S', 0, S);
      // }

      // ans.emplace_back('I', 1, I + 1);

      Answer(ans, w, n);

      return 0;
    }
  }
}

