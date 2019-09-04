bool pip(vector<P> ps, P p) {
    int c = 0;
    for (int i = 0; i < ps.size(); ++i) {
        int a = i;
        int b = (i + 1) % ps.size();
        if (same(ps[a].y, ps[b].y) && same(ps[a].y, p.y)) continue;
        if (ps[a].y > ps[b].y) swap(x, y);
        if (ps[a].y <= p.y && p.y < ps[b].y && p.x <= ps[a].x + (ps[b].x - ps[a].x) / (ps[b].y - ps[a].y) * (p.y - ps[a].y)) ++c;
    }
    return c & 1;
}
