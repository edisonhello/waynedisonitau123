struct AC {
    int ptr, ql, qr, root;
    vector<int> cnt, q, ed, el, ch[sigma], f;
    void clear(int p) { for (int i = 0; i < sigma; ++i) ch[i][p] = 0; }
    int newnode() { clear(ptr); ed[ptr] = 0; return ptr++; }
    void init() { 
        ptr = 1; cnt.resize(maxn); q.resize(maxn);
        ed.resize(maxn); el.resize(maxn); f.resize(maxn);
        for (int i = 0; i < sigma; ++i) ch[i].resize(maxn);
        root = newnode();
    }
    int add(const string &s) {
        int now = root;
        for (int i = 0; i < s.length(); ++i) {
            if (ch[s[i]][now] == 0) ch[s[i]][now] = newnode();
            now = ch[s[i]][now];
        }
        ed[now] = 1;
        return now;
    }
    void build_fail() {
        ql = qr = 0; q[qr++] = root;
        while (ql < qr) {
            int now = q[ql++];
            for (int i = 0; i < sigma; ++i) if (ch[i][now]) {
                int p = ch[i][now], fp = f[now];
                while (fp && !ch[i][fp]) fp = f[fp];
                int pd = fp ? ch[i][fp] : root;
                f[p] = pd;
                el[p] = ed[pd] ? pd : el[pd];
                q[qr++] = p;
            }
        }
    }
    void build(const string &s) {
        build_fail();
        int now = 1;
        for (int i = 0; i < s.length(); ++i) {
            while (now && !ch[s[i]][now]) now = f[now];
            now = now ? ch[s[i]][now] : root;
            ++cnt[now];
        }
        for (int i = qr - 1; i >= 0; --i) cnt[f[q[i]]] += cnt[q[i]];
    }
};

