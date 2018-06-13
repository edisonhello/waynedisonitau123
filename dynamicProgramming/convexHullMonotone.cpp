struct line {
    double a, b;
    inline double operator()(const double &x) const { return a * x + b; }
    inline bool checkfront(const line &l, const double &x) const { return (*this)(x) < l(x); }
    inline double intersect(const line &l) const { return (l.b - b) / (a - l.a); }
    inline bool checkback(const line &l, const line &pivot) const { return pivot.intersect((*this)) <= pivot.intersect(l); }
};

void solve() {
    for (int i = 1; i < maxn; ++i) dp[0][i] = inf;
    for (int i = 1; i <= k; ++i) {
        deque<line> dq; dq.push_back((line){ 0.0, dp[i - 1][0] });
        for (int j = 1; j <= n; ++j) {
            while (dq.size() >= 2 && dq[1].checkfront(dq[0], invt[j])) dq.pop_front();
            dp[i][j] = st[j] + dq.front()(invt[j]);
            line nl = (line){ -s[j], dp[i - 1][j] - st[j] + s[j] * invt[j] };
            while (dq.size() >= 2 && nl.checkback(dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
            dq.push_back(nl);
        }
    }
}
