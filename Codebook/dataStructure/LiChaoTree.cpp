namespace lichao {
struct line {
    long long a, b;
    line(): a(0), b(0) {}
    line(long long a, long long b): a(a), b(b) {}
    long long operator()(int x) const { return a * x + b; }
};
line st[maxc * 4];
int sz, lc[maxc * 4], rc[maxc * 4];
int gnode() {
    st[sz] = line(1e9, 1e9);
    lc[sz] = -1, rc[sz] = -1;
    return sz++;
}
void init() {
    sz = 0; 
}
void add(int l, int r, line tl, int o) {
    bool lcp = st[o](l) > tl(l);
    bool mcp = st[o]((l + r) / 2) > tl((l + r) / 2);
    if (mcp) swap(st[o], tl);
    if (r - l == 1) return;
    if (lcp != mcp) {
        if (lc[o] == -1) lc[o] = gnode();
        add(l, (l + r) / 2, tl, lc[o]);
    } else {
        if (rc[o] == -1) rc[o] = gnode();
        add((l + r) / 2, r, tl, rc[o]);
    }
}
long long query(int l, int r, int x, int o) {
    if (r - l == 1) return st[o](x);
    if (x < (l + r) / 2) {
        if (lc[o] == -1) return st[o](x);
        return min(st[o](x), query(l, (l + r) / 2, x, lc[o]));
    } else {
        if (rc[o] == -1) return st[o](x);
        return min(st[o](x), query((l + r) / 2, r, x, rc[o]));
    }
}}
