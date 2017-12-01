Point TriangleCircumCenter(Point a,Point b,Point c){
    Point res;
    double a1=atan2(b.y-a.y,b.x-a.x)+pi/2;
    double a2=atan2(c.y-b.y,c.x-b.x)+pi/2;
    double ax=(a.x+b.x)/2;
    double ay=(a.y+b.y)/2;
    double bx=(c.x+b.x)/2;
    double by=(c.y+b.y)/2;
    double r1=(sin(a2)*(ax-bx)+cos(a2)*(by-ay))/(sin(a1)*cos(a2)-sin(a2)*cos(a1));
    return Point(ax+r1*cos(a1),ay+r1*sin(a1));
}
