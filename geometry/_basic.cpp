const double eps = 1e-8;
const double pi = acos(-1);

struct Point {
    double x, y;
    Point(double a = 0, double b = 0): x(a), y(b) {}
};

typedef Point Vector;

// L:ax+by+c=0
struct Line {
    double a, b, c, angle;
    Point p1, p2;
    Line() {}
    Line(Point s, Point e) {
        a = s.y - e.y, b = e.x - s.x;
        c = s.x * e.y - e.x * s.y;
        angle = atan2(e.y - s.y, e.x - s.x);
        p1 = s, p2 = e;
    }
};

struct Segment {
    Point s, e;
    Segment() {}
    Segment(Point a, Point b): s(a), e(b) {}
    Segment(double x1, double y1, double x2, double y2) {
        s = Point(x1, y1);
        e = Point(x2, y2);
    }
};

Vector operator+(Point a, Point b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator-(Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator*(Point a, double k) { return Vector(a.x * k, a.y * k); }
Vector operator/(Point a, double k) { return Vector(a.x / k, a.y / k); }
double len(Vector a) { return sqrt(a.x * a.x + a.y * a.y); }

// <0 when ep at opsp clockwise
double Cross(Point &sp, Point &ep, Point &op) { return (sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y); }
double Cross(Vector a, Vector b) { return a.x * b.y - b.x * a.y; }
double Dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

int epssgn(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

double dis(Point a, Point b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

bool Parallel(Line l1, Line l2) { return fabs(l1.a * l2.b - l2.a * l1.b) < eps; }
bool LineEqual(Line l1, Line l2) { return Parallel(l1, l2) && fabs(l1.a * l2.c - l2.a * l1.c) < eps && fabs(l1.b * l2.c - l2.b * l1.c) < eps; }

double PointToSegDist(Point A, Point B, Point C) {
    if (dis(A, B) < eps) return dis(B, C);
    if (epssgn(Dot(B - A, C - A)) < 0) return dis(A, C);
    if (epssgn(Dot(A - B, C - B)) < 0) return dis(B, C);
    return fabs(Cross(B - A, C - A)) / dis(B, A);
}

double TwoSegMinDist(Point A, Point B, Point C, Point D) { return min(min(PointToSegDist(A, B, C), PointToSegDist(A, B, D)), min(PointToSegDist(C, D, A), PointToSegDist(C, D, B))); }

Point SymPoint(Point p, Line l) {
    Point result;
    double a = l.p2.x - l.p1.x;
    double b = l.p2.y - l.p1.y;
    double t = ((p.x - l.p1.x) * a + (p.y - l.p1.y) * b) / (a * a + b * b);
    result.x = 2 * l.p1.x + 2 * a * t - p.x;
    result.y = 2 * l.p1.y + 2 * b * t - p.y;
    return result;
}

// without end points: <= -> <
bool IsSegmentIntersect(Point s1, Point e1, Point s2, Point e2) {
    if (min(s1.x, e1.x) <= max(s2.x, e2.x) &&
        min(s1.y, e1.y) <= max(s2.y, e2.y) &&
        min(s2.x, e2.x) <= max(s1.x, e1.x) &&
        min(s2.y, e2.y) <= max(s1.y, e1.y) &&
        Cross(s2, e2, s1) * Cross(s2, e2, e1) <= 0 &&
        Cross(s1, e1, s2) * Cross(s1, e1, e2) <= 0) return 1;
    return 0;
}

int IsLineIntersectSegment(Point p1, Point p2, Point s, Point e){ return !Cross(p1, p2, s) * Cross(p1, p2, e) > eps; }
int IsLineIntersectSegment(Line l1, Point s, Point e) { return !Cross(l1.p1, l1.p2, s) * Cross(l1.p1, l1.p2, e) > eps; }

Point GetIntersect(Line l1, Line l2) {
    Point res;
    res.x = (l1.b * l2.c - l2.b * l1.c) / (l1.a * l2.b - l2.a * l1.b);
    res.y = (l1.c * l2.a - l2.c * l1.a) / (l1.a * l2.b - l2.a * l1.b);
    return res;
}
