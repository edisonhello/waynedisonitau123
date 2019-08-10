void solve(int n) {
    init();
    vector<int> v(n), ds;
    for (int i = 0; i < n; ++i) {
        v[i] = i;
        ds.push_back(x[i] - y[i]);
    }
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    sort(v.begin(), v.end(), [&](int i, int j) { return x[i] == x[j] ? y[i] > y[j] : x[i] > x[j]; });
    int j = 0;
    for (int i = 0; i < n; ++i) {
        int p = lower_bound(ds.begin(), ds.end(), x[v[i]] - y[v[i]]) - ds.begin() + 1;
        pair<int, int> q = query(p);
        // query return prefix minimum
        if (~q.second) add_edge(v[i], q.second);
        add(p, make_pair(x[v[i]] + y[v[i]], v[i]));
    }
}

void make_graph() {
    solve(n);
    for (int i = 0; i < n; ++i) swap(x[i], y[i]);
    solve(n);
    for (int i = 0; i < n; ++i) x[i] = -x[i];
    solve(n);
    for (int i = 0; i < n; ++i) swap(x[i], y[i]);
    solve(n);
}
