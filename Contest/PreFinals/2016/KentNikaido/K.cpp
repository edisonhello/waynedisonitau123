#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int s = accumulate(a.begin(), a.end(), 0);
  int g = *min_element(a.begin(), a.end());
  if (n % 2 == 1) {
    if (s % 2 == 1) cout << "Iori" << endl;
    else cout << "Yayoi" << endl;
  } else {
    if (g % 2 == 1) cout << "Iori" << endl;
    else if ((g + s) % 2 == 1) cout << "Iori" << endl;
    else cout << "Yayoi" << endl;
  }
}
