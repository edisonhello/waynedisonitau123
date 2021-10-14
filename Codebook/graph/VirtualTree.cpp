void VirtualTree(vector<int> v) {
  v.push_back(0);
  sort(v.begin(), v.end(), [&](int i, int j) { return dfn[i] < dfn[j]; });
  v.resize(unique(v.begin(), v.end()) - v.begin());
  vector<int> stk;
  for (int u : v) {
    if (stk.empty()) {
      stk.push_back(u);
      continue;
    }
    int p = GetLCA(u, stk.back());
    if (p != stk.back()) {
      while (stk.size() >= 2 && dep[p] <= dep[stk[stk.size() - 2]]) {
        int x = stk.back();
        stk.pop_back();
        AddEdge(x, stk.back());
      }
      if (stk.back() != p) {
        AddEdge(stk.back(), p);
        stk.pop_back();
        stk.push_back(p);
      }
    }
    stk.push_back(u);
  }
  for (int i = 0; i + 1 < stk.size(); ++i) AddEdge(stk[i], stk[i + 1]);
}
