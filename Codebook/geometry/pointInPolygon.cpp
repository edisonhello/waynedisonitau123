int pip(vector<P> ps, P p) {
    int c = 0;
    for (int i = 0; i < ps.size(); ++i) {
        int a = i, b = (i + 1) % ps.size();
        L l(ps[a], ps[b]);
        P q = l.project(p);
        if ((p - q).abs() < eps && l.inside(q)) return 1;
        if (same(ps[a].y, ps[b].y) && same(ps[a].y, p.y)) continue;
        if (ps[a].y > ps[b].y) swap(a, b);
        if (ps[a].y <= p.y && p.y < ps[b].y && p.x <= ps[a].x + (ps[b].x - ps[a].x) / (ps[b].y - ps[a].y) * (p.y - ps[a].y)) ++c;
    }
    return (c & 1) * 2;
}
