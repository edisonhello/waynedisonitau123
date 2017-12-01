// remove second level if to get points for line (defalut: segment)
void CircleCrossLine(Point a,Point b,Point o,double r,Point ret[],int &num){
    double x0=o.x,y0=o.y;
    double x1=a.x,y1=a.y;
    double x2=b.x,y2=b.y;
    double dx=x2-x1,dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0)+2*dy*(y1-y0);
    double C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    double delta=B*B-4*A*C;
    num=0;
    if(epssgn(delta)>=0){
        double t1=(-B-sqrt(fabs(delta)))/(2*A);
        double t2=(-B+sqrt(fabs(delta)))/(2*A);
        if(epssgn(t1-1.0)<=0 && epssgn(t1)>=0)ret[num++]=Point(x1+t1*dx,y1+t1*dy);
        if(epssgn(t2-1.0)<=0 && epssgn(t2)>=0)ret[num++]=Point(x1+t2*dx,y1+t2*dy);
    }
}

vector<Point> CircleCrossLine(Point a,Point b,Point o,double r){
    double x0=o.x,y0=o.y;
    double x1=a.x,y1=a.y;
    double x2=b.x,y2=b.y;
    double dx=x2-x1,dy=y2-y1;
    double A=dx*dx+dy*dy;
    double B=2*dx*(x1-x0)+2*dy*(y1-y0);
    double C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    double delta=B*B-4*A*C;
    vector<Point> ret;
    if(epssgn(delta)>=0){
        double t1=(-B-sqrt(fabs(delta)))/(2*A);
        double t2=(-B+sqrt(fabs(delta)))/(2*A);
        if(epssgn(t1-1.0)<=0 && epssgn(t1)>=0)ret.emplace_back(x1+t1*dx,y1+t1*dy);
        if(epssgn(t2-1.0)<=0 && epssgn(t2)>=0)ret.emplace_back(x1+t2*dx,y1+t2*dy);
    }
	return ret;
}
