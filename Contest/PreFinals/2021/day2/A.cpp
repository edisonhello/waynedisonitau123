#include <bits/stdc++.h>
using namespace std;

int v[200005];
int up[200005];
int down[200005];

int main() {
  int n, u, l, d; cin >> n >> u >> l >> d;
  int cnt = 0;
  bool al = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> v[i];
    if (v[i] >= u) up[i] = 1;
    if (v[i] <= l) down[i] = 1;
    up[i] += up[i - 1];
    down[i] += down[i - 1];
  }

  for (int i = d; i <= n; ++i) {
    int p = i - d;
    if (al) {
      if (down[i] - down[p] == d) al = 0;
    } else {
      if (up[i] - up[p] == d) al = 1, ++cnt;
    }
  }

  cout << cnt << endl;
}
