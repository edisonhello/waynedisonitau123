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
};
