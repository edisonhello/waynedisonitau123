#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  map<string, int> cnt;
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    cnt[s]++;
  }
  for (auto it : cnt) {
    if (it.second > N - it.second) {
      cout << it.first << "\n";
      return 0;
    }
  }
  cout << "NONE\n";
}
