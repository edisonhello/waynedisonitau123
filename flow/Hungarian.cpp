struct Hungarian {
    vector<vector<int>> w;
    bitset<maxn> s, t;
    vector<int> lx, ly, mx, my, slack, prv;
    int n, matched;
    Hungarian() {}
    Hungarian(int _n): n(_n) {
        w = vector<vector<int>>(n, vector<int>(n));
        lx.resize(n); ly.resize(n); mx.assign(n, -1); my.assign(n, -1);
        slack.resize(n); prv.resize(n);
    }
    void add_edge(int a, int b, int c) {
        w[a][b] = c;
    }
    void add(int x) {
        s[x] = true;
        for (int i = 0; i < n; ++i) {
            if (lx[x] + ly[i] - w[x][i] < slack[i]) {
                slack[i] = lx[x] + ly[i] - w[x][i];
                prv[i] = x;
            }
        }
    }
    void augment(int now) {
        int x = prv[now], y = now;
        ++matched;
        while (true) {
            int tmp = mx[x]; mx[x] = y; my[y] = x; y = tmp;
            if (y == -1) return;
            x = prv[y];
        }
    }
    void relabel() {
        int delta = inf;
        for (int i = 0; i < n; ++i) if (!t[i]) delta = min(delta, slack[i]);
        for (int i = 0; i < n; ++i) if (s[i]) lx[i] -= delta;
        for (int i = 0; i < n; ++i) {
            if (t[i]) ly[i] += delta;
            else slack[i] -= delta;
        }
    }
    void go() {
        s.reset(); t.reset();
        fill(slack.begin(), slack.end(), inf);
        int root = 0;
        for (; root < n && mx[root] != -1; ++root);
        add(root);
        while (true) {
            relabel();
            int y = 0;
            for (; y < n; ++y) if (!t[y] && slack[y] == 0) break;
            if (my[y] == -1) return augment(y), void();
            add(my[y]); t[y] = true;
        }
    }
    int matching() {
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) lx[i] = max(lx[i], w[i][j]);
        }
        for (int i = 0; i < n; ++i) go();
        for (int i = 0; i < n; ++i) ret += w[i][mx[i]];
        return ret;
    }
};

