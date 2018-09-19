struct SAM {
    static const int maxn = 5e5 + 5;
    int nxt[maxn][26], to[maxn], len[maxn];
    int root, last, sz;
    int gnode(int x) {
        for (int i = 0; i < 26; ++i) nxt[sz][i] = -1;
        to[sz] = -1;
        len[sz] = x;
        return sz++;
    }
    void init() {
        sz = 0;
        root = gnode(0);
        last = root;
    }
    void push(int c) {
        int cur = last;
        last = gnode(len[last] + 1);
        for (; ~cur && nxt[cur][c] == -1; cur = to[cur]) nxt[cur][c] = last;
        if (cur == -1) return to[last] = root, void();
        int link = nxt[cur][c];
        if (len[link] == len[cur] + 1) return to[last] = link, void();
        int tlink = gnode(len[cur] + 1);
        for (; ~cur && nxt[cur][c] == link; cur = to[cur]) nxt[cur][c] = tlink;
        for (int i = 0; i < 26; ++i) nxt[tlink][i] = nxt[link][i];
        to[tlink] = to[link];
        to[link] = tlink;
        to[last] = tlink;
    }
    void add(const string &s) {
        for (int i = 0; i < s.size(); ++i) push(s[i] - 'a');
    }
    bool find(const string &s) {
        int cur = root;
        for (int i = 0; i < s.size(); ++i) {
            cur = nxt[cur][s[i] - 'a'];
            if (cur == -1) return false;
        }
        return true;
    }
    int solve(const string &t) {
        int res = 0, cnt = 0;
        int cur = root;
        for (int i = 0; i < t.size(); ++i) {
            if (~nxt[cur][t[i] - 'a']) {
                ++cnt;
                cur = nxt[cur][t[i] - 'a'];
            } else {
                for (; ~cur && nxt[cur][t[i] - 'a'] == -1; cur = to[cur]);
                if (~cur) cnt = len[cur] + 1, cur = nxt[cur][t[i] - 'a'];
                else cnt = 0, cur = root;
            }
            res = max(res, cnt);
        }
        return res;
    }
};
