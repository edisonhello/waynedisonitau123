#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  string s;
  cin >> s;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  vector<int> vec;
  for (int i = 0, j = 0; i < N; i = j) {
    int v = 0;
    while (j < N && s[i] == s[j]) {
      v = max(v, A[j++]);
    }
    vec.push_back(v);
  }
  if (vec.size() <= 2) {
    cout << "0\n";
    return 0;
  }
  vector<int> v(next(vec.begin()), prev(vec.end()));
  int64_t sum = 0;
  sort(v.rbegin(), v.rend());
  for (int i = 0; i < (v.size() + 1) / 2; ++i) {
    sum += v[i];
  }
  cout << sum << "\n";
  return 0;
}
