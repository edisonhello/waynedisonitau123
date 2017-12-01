Point TriangleInnerCenter(Point a,Point b,Point c){
    Point res;
    double la=len(b-c);
    double lb=len(a-c);
    double lc=len(a-b);
    res.x=(la*a.x+lb*b.x+lc*c.x)/(la+lb+lc);
    res.y=(la*a.y+lb*b.y+lc*c.y)/(la+lb+lc);
}
