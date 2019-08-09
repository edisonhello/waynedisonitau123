bool same(const double a,const double b){ return abs(a-b)<1e-9; }

struct Point{
    double x,y;
    Point():x(0),y(0){}
    Point(double x,double y):x(x),y(y){}
};
Point operator+(const Point a,const Point b){ return Point(a.x+b.x,a.y+b.y); }
Point operator-(const Point a,const Point b){ return Point(a.x-b.x,a.y-b.y); }
Point operator*(const Point a,const double b){ return Point(a.x*b,a.y*b); }
Point operator/(const Point a,const double b){ return Point(a.x/b,a.y/b); }
double operator^(const Point a,const Point b){ return a.x*b.y-a.y*b.x; }
double abs(const Point a){ return sqrt(a.x*a.x+a.y*a.y); }


struct Line{
    // ax+by+c=0
    double a,b,c;
    double angle;
    Point pa,pb;
    Line():a(0),b(0),c(0),angle(0),pa(),pb(){}
    Line(Point pa,Point pb):a(pa.y-pb.y),b(pb.x-pa.x),c(pa^pb),angle(atan2(-a,b)),pa(pa),pb(pb){}
};

Point intersect(Line la,Line lb){
    if(same(la.a*lb.b,la.b*lb.a))return Point(7122,7122);
    double bot=-la.a*lb.b+la.b*lb.a;
    return Point(-la.b*lb.c+la.c*lb.b,la.a*lb.c-la.c*lb.a)/bot;
}

bool intersect(Point p1, Point p2, Point p3, Point p4) {
    if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
    if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
    return sign((p3 - p1) % (p4 - p1)) * sign((p3 - p2) % (p4 - p2)) <= 0 &&
           sign((p1 - p3) % (p2 - p3)) * sign((p1 - p4) % (p2 - p4)) <= 0;
}

int contain(const vector<Point> &ps, Point p) {
    // ps is not necessarily convex.
    int n = (int)ps.size();
    for (int i = 0; i < n; ++i) {
        Point a = ps[i], b = ps[(i + 1) % n];
        // on segment
        if ((p - a) * (b - a) >= 0 && (p - b) * (a - b) >= 0 && (p - a) % (b - a) == 0) return 1;
    }
    // infinity
    Point q = Point(1000000000, p.y);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        Point a = ps[i], b = ps[(i + 1) % n];
        if (intersect(a, b, p, q) && p.y >= min(a.y, b.y) && p.y < max(a.y, b.y)) res ^= 1;
    }
    // ps contains p.
    if (res == 1) return 2;
    return 0;
}
