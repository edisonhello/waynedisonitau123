#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<double> f(N + 1);
  vector<double> g(N + 1);
  g[1] = 1;
  for (int i = 2; i <= N; ++i) {
    for (int j = 1; j < i; ++j) {
      f[i] += g[j];
      g[i] += g[j];
    }
    f[i] /= (i - 1);
    g[i] /= i;
  }
  cout << fixed << setprecision(20) << f[N] << "\n";
}
