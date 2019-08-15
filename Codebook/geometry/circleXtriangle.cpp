// calc area intersect by circle with radius r and triangle OAB
double AreaOfCircleTriangle(P a, P b, double r) {
    bool ina = a.abs() - r < 0, inb = b.abs() - r < 0;
    if (ina) {
        if (inb) return abs(a ^ b) / 2; // triangle in circle
        else { // a point inside and another outside: calc sector and triangle area
            vector<P> p = CircleCrossLine(a, b, P(0, 0), r);
            return SectorArea(b, p[0], r) + abs(a ^ p[0]) / 2.0;
        }
    } else {
        vector<P> p = CircleCrossLine(a, b, P(0, 0), r);
        if (inb) return SectorArea(p[0], a, r) + abs(p[0] ^ b) / 2.0;
        else {
            if (p.size() == 2u) return SectorArea(a, p[0], r) + SectorArea(p[1], b, r) + abs(p[0] ^ p[1]) / 2.0; // segment ab has 2 point intersect with circle
            else return SectorArea(a, b, r); // segment has no intersect point with circle
        }
    }
}
// for any triangle
double AreaOfCircleTriangle(vector<P> ps, double r) {
    double ans = 0;
    for (int i = 0; i < 3; ++i) {
        int j = (i + 1) % 3;
        double o = atan2(ps[i].y, ps[i].x) - atan2(ps[j].y, ps[j].x);
        if (o >= pi) o = o - 2 * pi;
        if (o <= -pi) o = o + 2 * pi;
        ans += AreaOfCircleTriangle(ps[i], ps[j], r) * (o >= 0 ? 1 : -1);
    }
    return abs(ans);
}
