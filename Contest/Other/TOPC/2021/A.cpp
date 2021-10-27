#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<tuple<int, int, int, string>> vec;
  for (int i = 0; i < N; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    cin.ignore();
    string s;
    getline(cin, s);
    vec.emplace_back(a, b, c, s);
  }
  sort(vec.rbegin(), vec.rend());
  cout << get<3>(vec[0]) << "\n";
}
