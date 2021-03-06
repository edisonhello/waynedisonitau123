struct AC {
    static const int maxn = 1e5 + 5;
    int sz, ql, qr, root;
    int cnt[maxn], q[maxn], ed[maxn], el[maxn], ch[maxn][26], f[maxn];
    int gnode() {
        for (int i = 0; i < 26; ++i) ch[sz][i] = -1;
        f[sz] = -1;
        ed[sz] = 0;
        cnt[sz] = 0;
        return sz++;
    }
    void init() { 
        sz = 0;
        root = gnode();
    }
    int add(const string &s) {
        int now = root;
        for (int i = 0; i < s.length(); ++i) {
            if (ch[now][s[i] - 'a'] == -1) ch[now][s[i] - 'a'] = gnode();
            now = ch[now][s[i] - 'a'];
        }
        ed[now] = 1;
        return now;
    }
    void build_fail() {
        ql = qr = 0; q[qr++] = root;
        while (ql < qr) {
            int now = q[ql++];
            for (int i = 0; i < 26; ++i) if (ch[now][i] != -1) {
                int p = ch[now][i], fp = f[now];
                while (fp != -1 && ch[fp][i] == -1) fp = f[fp];
                int pd = fp != -1 ? ch[fp][i] : root;
                f[p] = pd;
                el[p] = ed[pd] ? pd : el[pd];
                q[qr++] = p;
            }
        }
    }
    void build(const string &s) {
        build_fail();
        int now = root;
        for (int i = 0; i < s.length(); ++i) {
            while (now != -1 && ch[now][s[i] - 'a'] == -1) now = f[now];
            now = now != -1 ? ch[now][s[i] - 'a'] : root;
            ++cnt[now];
        }
        for (int i = qr - 1; i >= 0; --i) cnt[f[q[i]]] += cnt[q[i]];
    }
    long long solve(int n) {
        build_fail();
        vector<vector<long long>> dp(sz, vector<long long>(n + 1, 0));
        for (int i = 0; i < sz; ++i) dp[i][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < sz; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (ch[j][k] != -1) {
                        if (!ed[ch[j][k]])
                            dp[j][i] += dp[ch[j][k]][i - 1];
                    } else {
                        int z = f[j];
                        while (z != root && ch[z][k] == -1) z = f[z];
                        int p = ch[z][k] == -1 ? root : ch[z][k];
                        if (ch[z][k] == -1 || !ed[ch[z][k]]) dp[j][i] += dp[p][i - 1];
                    }
                }
            }
        }
        return dp[0][n];
    }
};
