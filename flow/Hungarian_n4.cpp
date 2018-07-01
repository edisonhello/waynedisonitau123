struct hungarian {
    static const int inf = 1e9;
    int lx[maxn], ly[maxn], w[maxn][maxn];
    int match[maxn];
    bool vx[maxn], vy[maxn];
    void init() {
        for (int i = 0; i < maxn; ++i) for (int j = 0; j < maxn; ++j) w[i][j] = -inf;
        for (int i = 0; i < maxn; ++i) w[i][i] = 0;
    }
    void add_edge(int a, int b, int c) {
        w[a][b] = max(w[a][b], c);
    }
    bool dfs(int now) {
        vx[now] = true;
        for (int i = 0; i < maxn; ++i) if (lx[now] + ly[i] == w[now][i] && !vy[i]) {
            vy[i] = true;
            if (!match[i] || dfs(match[i])) {
                match[i] = now;
                return true;
            }
        }
        return false;
    }
    void relabel() {
        int dlt = inf;
        for (int i = 0; i < maxn; ++i) if (vx[i]) {
            for (int j = 0; j < maxn; ++j) if (!vy[j]) dlt = min(dlt, lx[i] + ly[j] - w[i][j]);
        }
        for (int i = 0; i < maxn; ++i) if (vx[i]) lx[i] -= dlt;
        for (int i = 0; i < maxn; ++i) if (vy[i]) ly[i] += dlt;
    }
    int operator()() {
        fill(lx, lx + maxn, -inf); fill(ly, ly + maxn, 0);
        for (int i = 0; i < maxn; ++i) {
            for (int j = 0; j < maxn; ++j) lx[i] = max(lx[i], w[i][j]);
        }
        memset(match, 0, sizeof(match));
        for (int i = 0; i < maxn; ++i) {
            while (true) {
                memset(vx, false, sizeof(vx));
                memset(vy, false, sizeof(vy));
                if (dfs(i)) break;
                relabel();
            }
        }
        int r = 0;
        for (int i = 0; i < maxn; ++i) if (w[match[i]][i] > 0) r += w[match[i]][i];
        return r;
    }
};

