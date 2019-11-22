struct PalindromicTree {
    int link[kN], len[kN], dp[kN], nxt[kN][26], sz, sf;
    int gnode(int l, int fl = -1) {
        len[sz] = l;
        link[sz] = fl;
        fill(nxt[sz], nxt[sz] + 26, -1);
        return sz++;
    }
    void Init() {
        sz = 0;
        sf = 1;
        gnode(-1, 0);
        gnode(0, 0);
    }
    void Push(const string &s, int pos) {
        int cur = sf, z = s[pos] - 'a';
        while (pos - 1 - len[cur] < 0 || s[pos - 1 - len[cur]] != s[pos]) cur = link[cur];
        if (nxt[cur][z] != -1) {
            sf = nxt[cur][z];
        } else {
            int ch = gnode(len[cur] + 2);
            nxt[cur][z] = sf = ch;
            if (len[ch] == 1) {
                link[ch] = 1;
            } else {
                cur = link[cur];
                while (pos - 1 - len[cur] < 0 || s[pos - 1 - len[cur]] != s[pos]) cur = link[cur];
                link[ch] = nxt[cur][z];
            }
        }
        dp[sf] += 1;
    }
    long long Build(const string &s) {
        for (int i = 0; i < s.size(); ++i) Push(s, i);
        for (int i = sz - 1; i >= 0; --i) dp[link[i]] += dp[i];
        long long res = 0;
        for (int i = 0; i < sz; ++i) res = max(res, 1LL * dp[i] * len[i]);
        return res;
    }
} plt;
