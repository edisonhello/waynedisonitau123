void VirtualTree(vector<int> v) {
    static int stk[kN];
    int sz = 0;
    sort(v.begin(), v.end(), [&](int i, int j) { return dfn[i] < dfn[j]; });
    stk[sz++] = 0;
    for (int u : v) {
        if (u == 0) continue;
        int p = LCA(u, stk[sz - 1]);
        if (p != stk[sz - 1]) {
            while (sz >= 2 && dfn[p] < dfn[stk[sz - 2]]) {
                AddEdge(stk[sz - 2], stk[sz - 1]);
                --sz;
            }
            if (sz >= 2 && dfn[p] > dfn[stk[sz - 2]]) {
                AddEdge(p, stk[sz - 1]);
                stk[sz - 1] = p;
            } else {
                AddEdge(p, stk[--sz]);
            }
        }
        stk[sz++] = u;
    }
    for (int i = 0; i < sz - 1; ++i) AddEdge(stk[i], stk[i + 1]);
}
