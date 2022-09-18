#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int64_t> vec(N);
  int64_t sum = 0;
  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;
    int x;
    cin >> x;
    if (s == "1") {
      vec[i] = -x;
      sum += x;
    } else {
      vec[i] = x;
    }
  }
  for (int i = 1; i < N; ++i) {
    vec[i] += vec[i - 1];
  }
  for (int i = 0; i < N; ++i) {
    cerr << vec[i] << " ";
  }
  cerr << endl;
  for (int i = 1; i < N; i += 2) {
    vec[i] = -vec[i];
  }
  vector<int64_t> ans(N + 1);
  int64_t total = 0;
  vector<int> nxt(N, -1), prv(N, -1);
  for (int i = 0; i < N; ++i) {
    if (i + 1 < N) nxt[i] = i + 1;
    if (i > 0) prv[i] = i - 1;
  }
  set<tuple<int64_t, int, int>> s;
  for (int i = 0; i < N - 1; ++i) {
    s.emplace(vec[i] + vec[i + 1], i, i + 1);
  }
  for (int i = 0; i < N; ++i) {
    total += vec[i];
  }
  ans[N] = total;
  for (int it = 0; it < N / 2; ++it) {
    auto [v, x, y] = *s.begin();
    s.erase(s.begin());
    assert(nxt[x] == y);
    total -= v;
    ans[N - (it + 1) * 2] = total;
    if (prv[x] != -1) {
      s.erase(make_tuple(vec[prv[x]] + vec[x], prv[x], x));
      nxt[prv[x]] = -1;
    }
    if (nxt[y] != -1) {
      s.erase(make_tuple(vec[y] + vec[nxt[y]], y, nxt[y]));
      prv[nxt[y]] = -1;
    }
    if (prv[x] != -1 && nxt[y] != -1) {
      s.insert(make_tuple(vec[prv[x]] + vec[nxt[y]], prv[x], nxt[y]));
      nxt[prv[x]] = nxt[y];
      prv[nxt[y]] = prv[x];
    }
  }
  int Q;
  cin >> Q;
  for (int i = 0; i <= N; ++i) {
    cerr << ans[i] << " ";
  }
  cerr << endl;
  while (Q--) {
    int k;
    cin >> k;
    cout << ans[k] + sum << "\n";
  }
}
