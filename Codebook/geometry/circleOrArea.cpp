vector<pair<double, double>> cover_segment(C &a, C &b) {
    double d = (a.c - b.c).abs();
    vector<pair<double, double>> ps;
    if (same(a.r + b.r, d)) ;
    else if (d <= abs(a.r - b.r) + eps) {
        if (a.r < b.r) ps.emplace_back(0, 2 * pi);
    } else if (d < abs(a.r + b.r) - eps) {
        double o = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d)), z = atan2(b.c.y - a.c.y, b.c.x - a.c.x);
        if (z < 0) z += 2 * pi;
        double l = z - o, r = z + o;
        if (l < 0) l += 2 * pi;
        if (r > 2 * pi) r -= 2 * pi;
        if (l > r) ps.emplace_back(l, 2 * pi), ps.emplace_back(0, r);
        else ps.emplace_back(l, r);
    }
    return ps;
}
// circles should not same
double coa(vector<C> cs) {
    int n = cs.size();
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<pair<double, double>> seg = {{2 * pi, 2 * pi}}, ps;
        for (int j = 0; j < n; ++j) if (i != j) {
            ps = cover_segment(cs[i], cs[j]);
            for (auto &e : ps) seg.push_back(e);
        }
        double now = 0;
        sort(seg.begin(), seg.end());
        for (auto &e : seg) {
            if (e.first > now) {
                ans += sq(cs[i].r) * (e.first - now - sin(e.first - now));
                ans += (cs[i].c + P(cos(now), sin(now)) * cs[i].r) ^ (cs[i].c + P(cos(e.first), sin(e.first)) * cs[i].r);
            }
            now = max(now, e.second);
        }
    }
    return ans * 0.5;
}
