#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i = 0; i < N; ++i) {
      cin >> A[i];
    }
    for (int i = 0; i < M; ++i) {
      cin >> B[i];
    }

    auto Build = [&](vector<int> v) {
      vector<tuple<int64_t, int, int, int>> vec;
      for (int i = 0; i < v.size(); ++i) {
        tuple<int64_t, int, int, int> k = {v[i], 1, i, i};
        while (!vec.empty() &&
               (get<0>(vec.back()) + get<0>(k)) * get<1>(vec.back()) >
                   get<0>(vec.back()) * (get<1>(vec.back()) + get<1>(k))) {
          get<0>(k) += get<0>(vec.back());
          get<1>(k) += get<1>(vec.back());
          get<2>(k) = get<2>(vec.back());
          vec.pop_back();
        }
        vec.push_back(k);
      }
      return vec;
    };

    auto sa = Build(A);
    auto sb = Build(B);
    int i = 0, j = 0;
    vector<int> ans;
    while (i < sa.size() && j < sb.size()) {
      if (get<0>(sa[i]) * get<1>(sb[j]) > get<0>(sb[j]) * get<1>(sa[i])) {
        for (int k = get<2>(sa[i]); k <= get<3>(sa[i]); ++k) {
          ans.push_back(A[k]);
        }
        i++;
      } else {
        for (int k = get<2>(sb[j]); k <= get<3>(sb[j]); ++k) {
          ans.push_back(B[k]);
        }
        j++;
      }
    }
    while (i < sa.size()) {
      for (int k = get<2>(sa[i]); k <= get<3>(sa[i]); ++k) {
        ans.push_back(A[k]);
      }
      i++;
    }
    while (j < sb.size()) {
      for (int k = get<2>(sb[j]); k <= get<3>(sb[j]); ++k) {
        ans.push_back(B[k]);
      }
      j++;
    }
    int64_t res = 0;
    for (int i = 0; i < N + M; ++i) {
      res += 1LL * (i + 1) * ans[i];
    }
    cout << "Case " << tc << ": " << res << "\n";
  }
  return 0;
}
