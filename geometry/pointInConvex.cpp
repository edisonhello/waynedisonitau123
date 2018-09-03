bool on(point a, point b, point c) {
    if (a.x == b.x) {
        if (c.x != a.x) return false;
        if (c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y)) return true;
        return false;
    }
    if (((a - c) ^ (b - c)) != 0) return false;
    if (a.x > b.x) swap(a, b);
    if (c.x < min(a.x, b.x) || c.x > max(a.x, b.x)) return false;
    return ((a - b) ^ (a - c)) == 0;
}

int sgn(long long x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

bool in(const vector<point> &c, point p) {
    int last = -2;
    int n = c.size();
    for (int i = 0; i < c.size(); ++i) {
        if (on(c[i], c[(i + 1) % n], p)) return true;
        int g = sgn((c[i] - p) ^ (c[(i + 1) % n] - p));
        if (last == -2) last = g;
        else if (last != g) return false;
    }
    return true;
}

bool in(point a, point b, point c, point p) {
    return in({ a, b, c }, p);
}

bool inside(const vector<point> &ch, point t) {
    point p = ch[1] - ch[0];
    point q = t - ch[0];
    if ((p ^ q) < 0) return false;
    if ((p ^ q) == 0) {
        if (p * q < 0) return false;
        if (q.len() > p.len()) return false;
        return true;
    }
    p = ch[ch.size() - 1] - ch[0];
    if ((p ^ q) > 0) return false;
    if ((p ^ q) == 0) {
        if (p * q < 0) return false;
        if (q.len() > p.len()) return false;
        return true;
    }
    p = ch[1] - ch[0];
    double ang = acos(1.0 * (p * q) / p.len() / q.len());
    int d = 20, z = ch.size() - 1;
    while (d--) {
        if (z - (1 << d) < 1) continue;
        point p1 = ch[1] - ch[0];
        point p2 = ch[z - (1 << d)] - ch[0];
        double tang = acos(1.0 * (p1 * p2) / p1.len() / p2.len());
        if (tang >= ang) z -= (1 << d);
    }
    return in(ch[0], ch[z - 1], ch[z], t);
}
