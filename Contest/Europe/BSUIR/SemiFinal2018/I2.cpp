#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> ord(n);
  iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int i, int j) {
      if (a[i] != a[j]) return a[i] > a[j];
      return i < j;
  });
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && a[ord[i]] == a[ord[j]]) j++;
  }
  return 0;
}
