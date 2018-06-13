struct line {
    int m, y;
    int l, r;
    line(int m = 0,int y = 0, int l = -5, int r = 1000000009): m(m), y(y), l(l), r(r) {}
    int get(int x) const { return m * x + y; }
    int useful(line le) const {
        return (int)(get(l) >= le.get(l)) + (int)(get(r) >= le.get(r));
    }
};

int magic;
bool operator < (const line &a, const line &b) {
    if (magic) return a.m < b.m;
    return a.l < b.l;
}

set<line> st;

void addline(line l) {
    magic = 1;
    auto it = st.lower_bound(l);
    if (it != st.end() && it->useful(l) == 2) return;
    while (it != st.end() && it->useful(l) == 0) it = st.erase(it);
    if (it != st.end() && it->useful(l) == 1) {
        int L = it->l, R = it->r, M;
        while (R > L) {
            M = (L + R + 1) >> 1;
            if (it->get(M) >= l.get(M)) R = M - 1;
            else L = M;
        }
        line cp = *it;
        st.erase(it);
        cp.l = L + 1;
        if (cp.l <= cp.r) st.insert(cp);
        l.r = L;
    }
    else if (it != st.end()) l.r = it->l - 1;
    it = st.lower_bound(l);
    while (it != st.begin() && prev(it)->useful(l) == 0) it = st.erase(prev(it));
    if (it != st.begin() && prev(it)->useful(l) == 1) {
        --it;
        int L = it->l, R = it->r, M;
        while (R > L) {
            M = (L + R) >> 1;
            if (it->get(M) >= l.get(M)) L = M + 1;
            else R = M;
        }
        line cp = *it;
        st.erase(it);
        cp.r = L - 1;
        if (cp.l <= cp.r) st.insert(cp);
        l.l = L;
    }
    else if (it != st.begin()) l.l = prev(it)->r + 1;
    if (l.l <= l.r) st.insert(l);
}

int getval(int d) {
    magic = 0;
    return (--st.upper_bound(line(0, 0, d, 0)))->get(d);
}
