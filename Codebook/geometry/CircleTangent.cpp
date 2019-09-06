vector<L> tangent(C a, C b) {
#define Pij \
    P i = (b.c - a.c).unit() * a.r, j = P(i.y, -i.x);\
    z.emplace_back(a.c + i, a.c + i + j);
#define deo(I,J) \
    double d = (a.c - b.c).abs(), e = a.r I b.r, o = acos(e / d);\
    P i = (b.c - a.c).unit(), j = i.spin(o), k = i.spin(-o);\
    z.emplace_back(a.c + j * a.r, b.c J j * b.r);\
    z.emplace_back(a.c + k * a.r, b.c J k * b.r);
    if (a.r < b.r) swap(a, b);
    vector<L> z;
    if ((a.c - b.c).abs() + b.r < a.r) return z;
    else if (same((a.c - b.c).abs() + b.r, a.r)) { Pij; } 
    else {
        deo(-,+);
        if (same(d, a.r + b.r)) { Pij; } 
        else if (d > a.r + b.r) { deo(+,-); }
    }
    return z;
}

vector<L> tangent(C c, P p) {
    vector<L> z;
    double d = (p - c.c).abs();
    if (same(d, c.r)) {
        P i = (p - c.c).spin(pi / 2);
        z.emplace_back(p, p + i);
    } else if (d > c.r) {
        double o = acos(c.r / d);
        P i = (p - c.c).unit(), j = i.spin(o) * c.r, k = i.spin(-o) * c.r;
        z.emplace_back(c.c + j, p);
        z.emplace_back(c.c + k, p);
    }
    return z;
}
