#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, a, b;
  cin >> n >> a >> b;

  vector<int> h(n);
  for (int i = 0; i < n; ++i) cin >> h[i];

  vector<int> va(n), vb(n);
  for (int i = 0; i < n; ++i) {
    va[i] = h[i] / b + !!(h[i] % b);

    int s = h[i] % b;
    int dv = h[i] / b;
    if (s == 0) s = b, --dv;
    vb[i] = dv - s / a - !!(s % a);
  }

  // for (int i = 0; i < n; ++i) cout << va[i] << ' ';
  // cout << endl;
  // for (int i = 0; i < n; ++i) cout << vb[i] << ' ';
  // cout << endl;

  int cnt = 0;
  priority_queue<int, vector<int>, less<int>> pq;
  int64_t pfx = 0;

  for (int i = 0; i < n; ++i) {
    ++cnt;
    pfx += vb[i];
    pq.push(va[i] - vb[i]);

    while (pfx < -1) {
      assert(pq.size());

      --cnt;
      pfx += pq.top();
      pq.pop();
    }
  }

  cout << cnt << endl;

}

