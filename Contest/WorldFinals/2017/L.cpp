#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<tuple<int, int, int, int>> event;
  vector<int> x1(N), y1(N), x2(N), y2(N);
  for (int i = 0; i < N; ++i) {
    cin >> x1[i] >> y1[i];
    event.emplace_back(x1[i], -1, y1[i], i);
  }
  for (int i = 0; i < N; ++i) {
    cin >> x2[i] >> y2[i];
    event.emplace_back(x2[i], 1, y2[i], i);
  }
  sort(event.begin(), event.end());

  multiset<pair<int, int>> st;
  vector<int> match(N);
  for (int i = 0; i < event.size(); ++i) {
    if (get<1>(event[i]) < 0) {
      st.insert(make_pair(get<2>(event[i]), get<3>(event[i]))); 
    } else {
      auto iter = st.upper_bound(make_pair(get<2>(event[i]), N));
      if (iter == st.begin()) {
        cout << "syntax error\n";
        return 0;
      }
      iter = prev(iter);
      match[iter->second] = get<3>(event[i]);
      // cout << iter->second + 1 << " " << get<3>(event[i]) + 1 << endl;
      st.erase(iter); 
    }
  }

  vector<tuple<int, int, int, int>> E;
  for (int i = 0; i < N; ++i) {
    // cout << "i = " << i << " match = " << match[i] << endl;
    // cout << "y1 = " << y1[i] << endl;
    E.emplace_back(x1[i], -1, y1[i], y2[match[i]]);
    E.emplace_back(x2[match[i]], 1, y1[i], y2[match[i]]);
  }

  sort(E.begin(), E.end(), [&](const auto& a, const auto& b) {
    if (get<0>(a) != get<0>(b)) {
      return get<0>(a) < get<0>(b);
    }
    if (get<1>(a) != get<1>(b)) {
      return get<1>(a) < get<1>(b);
    }

    if (get<2>(a) != get<2>(b)) {
      if (get<1>(a) == -1) return get<2>(a) > get<2>(b);
      else return get<2>(a) < get<2>(b);
    }
    if (get<1>(a) == -1) {
      return get<3>(a) < get<3>(b);
    } else {
      return get<3>(a) > get<3>(b);
    }
  });
  multiset<int> H;
  // cout << "here" << endl;
  for (int i = 0; i < E.size(); ++i) {
    // cout << get<0>(E[i]) << " " << get<1>(E[i]) << " " << get<2>(E[i]) << " " << get<3>(E[i]) << "\n";
    if (get<1>(E[i]) < 0) {
      auto iter = H.lower_bound(get<2>(E[i]));
      if (iter != H.end() && *iter <= get<3>(E[i])) {
        cout << "syntax error\n";
        return 0;
      } 
      H.insert(get<2>(E[i]));
      H.insert(get<3>(E[i]));
    } else {
      H.erase(H.find(get<2>(E[i])));
      H.erase(H.find(get<3>(E[i])));
      auto iter = H.lower_bound(get<2>(E[i]));
      if (iter != H.end() && *iter <= get<3>(E[i])) {
        cout << "syntax error\n";
        return 0;
      } 
    }
  }

  // auto Push = [&](int o) {
  //   for (int k = 1; k <= 2; ++k) {
  //     if (tag[o] == -1) {
  //       tree[o * 2 + k] = -1;
  //       tag[o * 2 + k] = -1;
  //     } else {
  //       tree[o * 2 + k] = max(tree[o * 2 + k], tag[o]);
  //       tag[o * 2 + k] = max(tag[o * 2 + k], tag[o]);
  //     }
  //   }
  //   tag[o] = 0;
  // };

  // auto Query = [&](int ql, int qr) {
  //   cout << "Query ql = " << ql << " qr = " << qr << endl;
  //   ql = lower_bound(ds.begin(), ds.end(), ql) - ds.begin();
  //   qr = lower_bound(ds.begin(), ds.end(), qr) - ds.begin();
  //   auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
  //     if (l >= qr || ql >= r) return 0;
  //     if (l >= ql && r <= qr) return tree[o];
  //     Push(o);
  //     int m = (l + r) >> 1;
  //     return max(dfs(dfs, l, m, o * 2 + 1), dfs(dfs, m, r, o * 2 + 2));
  //   };
  //   return dfs(dfs, 0, M);
  // };

  // auto Update = [&](int ql, int qr, int v) {
  //   cout << "Update ql = " << ql << " qr = " << qr << " v = " << v << endl;
  //   ql = lower_bound(ds.begin(), ds.end(), ql) - ds.begin();
  //   qr = lower_bound(ds.begin(), ds.end(), qr) - ds.begin();
  //   auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
  //     if (l >= qr || ql >= r) return;
  //     if (l >= ql && r <= qr) {
  //       tag[o] = max(tag[o], v);
  //       tree[o] = max(tree[o], v);
  //       return;
  //     }
  //     Push(o);
  //     int m = (l + r) >> 1;
  //     dfs(dfs, l, m, o * 2 + 1);
  //     dfs(dfs, m, r, o * 2 + 2);
  //     tree[o] = max(tree[o * 2 + 1], tree[o * 2 + 2]);
  //   };
  //   return dfs(dfs, 0, M);
  // };

  // auto Kill = [&](int ql, int qr) {
  //   ql = lower_bound(ds.begin(), ds.end(), ql) - ds.begin();
  //   qr = lower_bound(ds.begin(), ds.end(), qr) - ds.begin();
  //   auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
  //     if (l >= qr || ql >= r) return;
  //     if (l >= ql && r <= qr) {
  //       tag[o] = -1;
  //       tree[o] = -1;
  //       return;
  //     }
  //     Push(o);
  //     int m = (l + r) >> 1;
  //     dfs(dfs, l, m, o * 2 + 1);
  //     dfs(dfs, m, r, o * 2 + 2);
  //     tree[o] = max(tree[o * 2 + 1], tree[o * 2 + 2]);
  //   };
  //   return dfs(dfs, 0, M);
  // };

  // for (int i = 0; i < E.size(); ++i) {
  //   if (get<1>(E[i]) == 1) {
  //     cout << "query = " << Query(get<2>(E[i]), get<3>(E[i])) << endl;
  //     if (Query(get<2>(E[i]), get<3>(E[i])) >= get<0>(E[i])) {
  //       cout << "syntax error\n";
  //       return 0;
  //     }
  //     Update(get<2>(E[i]), get<3>(E[i]), get<0>(E[i]));
  //   } else {
  //     Kill(get<2>(E[i]), get<3>(E[i]));
  //   }
  // }

  for (int i = 0; i < N; ++i) {
    cout << match[i] + 1 << "\n";
  }
  return 0;
}

