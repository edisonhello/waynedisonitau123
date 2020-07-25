#include <bits/stdc++.h>
using namespace std;

int cnt[100005];

int pre[100005], suf[100005];

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
    ++cnt[v[i].first];
    --cnt[v[i].second];
  }

  for (int i = 2; i <= 100000; ++i) cnt[i] += cnt[i - 1];

  for (int i = 1; i <= 100000; ++i) pre[i] = suf[i] = cnt[i];
  for (int i = 2; i <= 100000; ++i) pre[i] = max(pre[i], pre[i - 1]);
  for (int i = 99999; i >= 1; --i) suf[i] = max(suf[i], suf[i + 1]);

  int mx = pre[100000];
  int le = -1, ri = -1;
  for (int i = 1; i <= 100000; ++i) if (cnt[i] == mx) ri = i;
  for (int i = 100000; i >= 1; --i) if (cnt[i] == mx) le = i;

  int mn = mx;
  for (int i = 0; i < n; ++i) {
    int l = v[i].first, r = v[i].second - 1;
    int tmx = max(pre[l - 1], suf[r + 1]);
    if (tmx == mx) continue;
    else mn = mx - 1;
  }


  cout << mn << '\n';

}
