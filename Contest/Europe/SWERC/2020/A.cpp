#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, K;
  cin >> N >> K;
  cin.ignore();
  map<string, int> cnt, recent;
  for (int i = 0; i < 3 * N; ++i) {
    string s;
    getline(cin, s);
    cnt[s]++;
    recent[s] = i;
  }
  vector<tuple<int, int, string>> vec;
  for (auto iter : cnt) {
    vec.emplace_back(iter.second, recent[iter.first], iter.first);
  }
  sort(vec.rbegin(), vec.rend());
  for (int i = 0; i < min<int>(vec.size(), K); ++i) {
    cout << get<2>(vec[i]) << "\n";
  }
}
