namespace schreier {
    int n;
    vector<vector<vector<int>>> bkts, binv;
    vector<vector<int>> lk;
    vector<int> operator*(const vector<int> &a, const vector<int> &b) {
        vector<int> res(a.size());
        for (int i = 0; i < (int)a.size(); ++i)
            res[i] = b[a[i]];
        return res;
    }
    vector<int> inv(const vector<int> &a) {
        vector<int> res(a.size());
        for (int i = 0; i < (int)a.size(); ++i)
            res[a[i]] = i;
        return res;
    }
    int filter(const vector<int> &g, bool add = true) {
        n = (int)bkts.size();
        vector<int> p = g;
        for (int i = 0; i < n; ++i) {
            assert(p[i] >= 0 && p[i] < (int)lk[i].size());
            int res = lk[i][p[i]];
            if (res == -1) {
                if (add) {
                    bkts[i].push_back(p);
                    binv[i].push_back(inv(p));
                    lk[i][p[i]] = (int)bkts[i].size() - 1;
                }
                return i;
            }
            p = p * binv[i][res];
        }
        return -1;
    }
    bool inside(const vector<int> &g) {
        return filter(g, false) == -1; 
    }
    void solve(const vector<vector<int>> &gen, int _n) {
        n = _n;
        bkts.clear(), bkts.resize(n);
        binv.clear(), binv.resize(n);
        lk.clear(), lk.resize(n);
        vector<int> iden(n);
        iota(iden.begin(), iden.end(), 0);
        for (int i = 0; i < n; ++i) {
            lk[i].resize(n, -1);
            bkts[i].push_back(iden);
            binv[i].push_back(iden);
            lk[i][i] = 0;
        }
        for (int i = 0; i < (int)gen.size(); ++i)
            filter(gen[i]);
        queue<pair<pair<int, int>, pair<int, int>>> upd;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                for (int k = 0; k < (int)bkts[i].size(); ++k) {
                    for (int l = 0; l < (int)bkts[j].size(); ++l)
                        upd.emplace(make_pair(i, k), make_pair(j, l));
                }
            }
        }
        while (!upd.empty()) {
            auto a = upd.front().first;
            auto b = upd.front().second;
            upd.pop();
            int res = filter(bkts[a.first][a.second] * bkts[b.first][b.second]);
            if (res == -1) continue;
            pair<int, int> pr = make_pair(res, (int)bkts[res].size() - 1);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < (int)bkts[i].size(); ++j) {
                    if (i <= res)
                        upd.emplace(make_pair(i, j), pr);
                    if (res <= i)
                        upd.emplace(pr, make_pair(i, j));
                }
            }
        }
    }
    long long size() {
        long long res = 1;
        for (int i = 0; i < n; ++i) 
            res = res * bkts[i].size();
        return res;
    }
}
