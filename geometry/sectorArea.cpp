// calc area of sector which include a,b
double SectorArea(Point a,Point b,double r){
    double theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while(theta<=0)theta+=2*pi;
    while(theta>=2*pi)theta-=2*pi;
    theta=min(theta,2*pi-theta);
    return r*r*theta/2;
}
