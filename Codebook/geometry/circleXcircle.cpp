#define sq(x) ((x) * (x))
vector<P> intersect(C a, C b) {
    if (a.r > b.r) swap(a, b);
    double d = (a.c - b.c).abs();
    vector<P> ps;
    if (same(a.r + b.r, d)) ps.push_back(a.c + (b.c - a.c).unit() * a.r);
    else if (a.r + b.r > d && d + a.r >= b.r) {
        double o = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d));
        P i = (b.c - a.c).unit();
        ps.push_back(a.c + i.spin(o) * a.r);
        ps.push_back(a.c + i.spin(-o) * a.r);
    }
    return ps;
}

double intersect_area(C a, C b) {
    if (a.r > b.r) swap(a, b);
    double d = (a.c - b.c).abs();
    if (d >= a.r + b.r - eps) return 0;
    if (d + a.r <= b.r + eps) return sq(a.r) * acos(-1);
    double p = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d));
    double q = acos((sq(b.r) + sq(d) - sq(a.r)) / (2 * b.r * d));
    return p * sq(a.r) + q * sq(b.r) - a.r * d * sin(p);
}
