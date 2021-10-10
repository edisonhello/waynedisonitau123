#include <bits/stdc++.h>
using namespace std;

int is_flush(vector<int> v) {
  sort(v.begin(), v.end());
  if (v == vector<int>{1, 2, 3, 4, 5}) return 1;
  for (int &i : v) if (i == 1) i = 14;
  sort(v.begin(), v.end());
  for (int i = 1; i < 5; ++i) if (v[i] != v[i - 1] + 1) return 0;
  return 2;
}

bool win(vector<string> c) {
  for (int i = 1; i < 5; ++i)
    if (c[i][0] != c[i - 1][0]) return false;
  vector<int> v;
  for (int i = 0; i < 5; ++i) {
    if (c[i][1] == 'T')
      v.push_back(10);
    else if (c[i][1] == 'J')
      v.push_back(11);
    else if (c[i][1] == 'Q')
      v.push_back(12);
    else if (c[i][1] == 'K')
      v.push_back(13);
    else if (c[i][1] == 'A')
      v.push_back(1);
    else
      v.push_back(c[i][1] - '0');
  }

  // cout << "v ";
  // for (int i : v) cout << i << ' '; cout << endl;

  vector<int> f{v[0], v[1]};
  sort(f.begin(), f.end());

  // cout << "f ";
  // for (int i : f) cout << i << ' '; cout << endl;

  int flush = is_flush(v);
  if (!flush) return false;
  if (flush == 1) { // 1 2 3 4 5
    if (f[0] == 1 && f[1] == 5) return true;
  } else {
    for (int &i : f) if (i == 1) i = 14;
    for (int &i : v) if (i == 1) i = 14;
    sort(v.begin(), v.end());

    int lar = v.back();
    if (f[0] == lar || f[1] == lar) return true;
    if (f[0] >= 10 || f[1] >= 10) return true;
  }

  return false;

}

int main() {
  int t;
  cin >> t;
  while (t--) {
    vector<string> c(5);
    for (int i = 0; i < 5; ++i) cin >> c[i], swap(c[i][0], c[i][1]);


    cout << (win(c) ? "allin" : "check") << '\n';
  }
}
