#include <bits/stdc++.h>
using namespace std;

int main() {
  string a, b;
  cin >> a >> b;
  if (a == b) {
    cout << a + 'a' << endl;
    return 0;
  }
  int i = 0, j = a.size() - 1;
  while (i < a.size() && a[i] == b[i]) i++;
  while (j >= 0 && a[j] == b[j]) j--;
  int k = j - i + 1;
  if (a.substr(i, k - 1) == b.substr(i + 1, k - 1)) {
    cout << a.substr(0, i) + b[i] + a.substr(i, k) + a.substr(j + 1) << "\n";
  } else if (a.substr(i + 1, k - 1) == b.substr(i, k - 1)) {
    cout << b.substr(0, i) + a[i] + b.substr(i, k) + b.substr(j + 1) << "\n";
  } else {
    cout << "IMPOSSIBLE\n";
  }
}
