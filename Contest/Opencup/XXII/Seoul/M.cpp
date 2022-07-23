#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  cin >> N;
  vector<int> p(N), q(N);
  for (int i = 0; i < N; ++i) {
    cin >> p[i];
  }
  for (int i = 0; i < N; ++i) {
    cin >> q[i];
  }
  vector<int> x(N), y(N);
  vector<int> ds(N);
  for (int i = 0; i < N; ++i) {
    x[i] = p[i] + q[i];
    y[i] = p[i] - q[i];
    ds[i] = y[i];
  }
  vector<int> order(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return make_pair(x[i], y[i]) < make_pair(x[j], y[j]);
  });
  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

  const int M = ds.size();
  vector<tuple<int, int64_t, int64_t>> fw(M + 1);

  auto Update = [&](int p, int v, int w) {
    for (int i = p + 1; i <= M; i += i & -i) {
      get<0>(fw[i])++;
      get<1>(fw[i]) += v;
      get<2>(fw[i]) += w;
    }
  };

  auto Query = [&](int p) {
    tuple<int, int64_t, int64_t> res = {0, 0, 0};
    for (int i = p + 1; i > 0; i -= i & -i) {
      get<0>(res) += get<0>(fw[i]);
      get<1>(res) += get<1>(fw[i]);
      get<2>(res) += get<2>(fw[i]);
    }
    return res;
  };

  int64_t sum = 0, ps = 0;
  for (int i = 0; i < N; ++i) {
    int k = lower_bound(ds.begin(), ds.end(), y[order[i]]) - ds.begin();
    auto t = Query(k);
    sum += 1LL * get<0>(t) * (x[order[i]] + y[order[i]]) + get<1>(t);
    sum +=
        1LL * (i - get<0>(t)) * (x[order[i]] - y[order[i]]) + (ps - get<2>(t));
    Update(k, -x[order[i]] - y[order[i]], -x[order[i]] + y[order[i]]);
    ps += -x[order[i]] + y[order[i]];
  }

  sort(p.begin(), p.end());
  sort(q.begin(), q.end());
  int64_t ans = 0;
  int64_t xs = 0;
  for (int i = 0; i < N; ++i) {
    ans += 1LL * p[i] * i - xs;
    xs += p[i];
  }
  int64_t ys = 0;
  for (int i = 0; i < N; ++i) {
    ans += 1LL * q[i] * i - ys;
    ys += q[i];
  }

  cout << 2 * ans - sum << "\n";
  return 0;
}
