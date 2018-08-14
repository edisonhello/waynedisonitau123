const double eps = 1e-9;

struct plane {
    // points t are in this plane if (q - t) ^ (p - t) >= 0
    point p, q;
    double ang;
    plane(point p, point q): p(p), q(q), ang(atan2(q.y - p.y, q.x - p.x)) {}
};

point inter(plane a, plane b) {
    if (fabs(a.q.x - a.p.x) < eps) {
        double mb = (b.q.y - b.p.y) / (b.q.x - b.p.x); 
        double kb = b.p.y - mb * b.p.x;
        return point(a.q.x, mb * a.q.x + kb);
    }
    if (fabs(b.q.x - b.p.x) < eps) {
        double ma = (a.q.y - a.p.y) / (a.q.x - a.p.x); 
        double ka = a.p.y - ma * a.p.x;
        return point(b.q.x, ma * b.q.x + ka);
    }
    double ma = (a.q.y - a.p.y) / (a.q.x - a.p.x); 
    double mb = (b.q.y - b.p.y) / (b.q.x - b.p.x); 
    double ka = a.p.y - ma * a.p.x;
    double kb = b.p.y - mb * b.p.x;
    double x = (kb - ka) / (ma - mb);
    double y = ma * x + ka;
    return point(x, y);
}

bool check(point p, plane l) {
    return ((l.q - p) ^ (l.p - p)) > eps || fabs((l.q - p) ^ (l.p - p)) < eps;
}

vector<point> hpi(vector<plane> l) {
    sort(l.begin(), l.end(), [](const plane &a, const plane &b) {
        if (fabs(a.ang - b.ang) > eps) return a.ang < b.ang;
        return ((a.q - a.p) ^ (b.q - a.p)) > eps;
    }); 
    vector<plane> tl;
    for (int i = 0; i < l.size(); ++i) {
        if (tl.size() && fabs(l[i].ang - tl.back().ang) < eps) continue;
        tl.push_back(l[i]);
    }
    for (int i = 0; i < tl.size(); ++i) debug(tl[i]);
    deque<plane> dq;
    for (int i = 0; i < tl.size(); ++i) {
        while (dq.size() >= 2 && !check(inter(dq[dq.size() - 1], dq[dq.size() - 2]), tl[i])) dq.pop_back();
        while (dq.size() >= 2 && !check(inter(dq[0], dq[1]), tl[i])) dq.pop_front();
        dq.push_back(tl[i]);
    }
    while (dq.size() >= 2 && !check(inter(dq[dq.size() - 1], dq[dq.size() - 2]), dq[0])) dq.pop_back();
    while (dq.size() >= 2 && !check(inter(dq[0], dq[1]), dq[dq.size() - 1])) dq.pop_front();
    for (int i = 0; i < dq.size(); ++i) debug(dq[i]);
    vector<point> res;
    for (int i = 0; i < dq.size(); ++i) res.push_back(inter(dq[i], dq[(i + 1) % dq.size()]));
    return res;
}
