#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> pos, neg;
  for (int i = 0; i < N; ++i) {
    string s;
    int x;
    cin >> s >> x;
    if (s == "+") pos.push_back(x);
    else neg.push_back(x);
  }
  sort(pos.rbegin(), pos.rend());
  sort(neg.rbegin(), neg.rend());
  int64_t ans = 0;
  for (int i = 0, j = 0; i < neg.size(); ++i) {
    while (j < pos.size() && pos[j] > neg[i]) j++;
    ans += j;
  }
  cout << fixed << setprecision(20) << static_cast<double>(ans) / pos.size() / neg.size() << "\n";
}
