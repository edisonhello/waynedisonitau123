vector<L> tangent(C c1, C c2) {
#define Pij \
    P i = (c2.c - c1.c).unit() * c1.r, j = P(i.y, -i.x);\
    res.emplace_back(c1.c + i, c1.c + i + j);
#define deo(I,J) \
    double d = (c1.c - c2.c).abs(), e = c1.r I c2.r, o = acos(e / d);\
    P i = (c2.c - c1.c).unit(), j = i.spin(o), k = i.spin(-o);\
    res.emplace_back(c1.c + j * c1.r, c2.c J j * c2.r);\
    res.emplace_back(c1.c + k * c1.r, c2.c J k * c2.r);
    if (c1.r < c2.r) swap(c1, c2);
    vector<L> res;
    if ((c1.c - c2.c).abs() + c2.r < c1.r) return res;
    else if (same((c1.c - c2.c).abs() + c2.r, c1.r)) { Pij; } 
    else {
        deo(-,+);
        if (same(d, c1.r + c2.r)) { Pij; } 
        else if (d > c1.r + c2.r) { deo(+,-); }
    }
    return res;
}
