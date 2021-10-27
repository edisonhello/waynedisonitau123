#include <bits/stdc++.h>
using namespace std;

int deg[100005];



int main() {

  int n, m; cin >> n >> m;

  int totd  = m * 2;

  while (m--) {
    int u, v; cin >> u >> v;
    ++deg[u];
    ++deg[v];
  }

  vector<int> o(n);
  iota(o.begin(), o.end(), 0);

  sort(o.begin(), o.end(), [&] (const int a, const int b) { return deg[a] < deg[b]; });

  int it = o.size() - 1;
  int consis = n;
  while (true) {
    if (totd == (n - 1) * 2) break;

    if (totd - deg[o[it]] + 1 <= (n - 1) * 2) {
      deg[o[it]] -= totd - (n - 1) * 2;
      --consis;
      break;
    } else {
      totd = totd - deg[o[it]] + 1;
      deg[o[it]] = 1;
      --consis;
    }

    --it;
  }

  set<pair<int, int>> st; // deg, i

  for (int i = 0; i < n; ++i) st.insert(make_pair(deg[i], i));

  vector<pair<int, int>> edgs;
  while (st.size()) {
    // cerr << "st.size() = " << st.size() << endl;

    auto last = *st.begin();
    st.erase(last);

    assert(last.first == 1);

    auto first = *prev(st.end());
    st.erase(first);

    edgs.emplace_back(first.second, last.second);
    --first.first;
    if (first.first) {
      st.insert(first);
    }
  }




  cout << n - consis << endl;

  cout << n << ' ' << n - 1 << endl;
  for (auto [u, v] : edgs) cout << u << ' ' << v << endl;

}

