// calc area intersect by circle with radius r and triangle OAB
double Calc(Point a,Point b,double r){
    Point p[2];
    int num=0;
    bool ina=epssgn(len(a)-r)<0,inb=epssgn(len(b)-r)<0;
    if(ina){
        if(inb)return fabs(Cross(a,b))/2.0; // triangle in circle
        else{ // a point inside and another outside: calc sector and triangle area
            CircleCrossLine(a,b,Point(0,0),r,p,num);
            return SectorArea(b,p[0],r)+fabs(Cross(a,p[0]))/2.0;
        }
    }
    else{
        CircleCrossLine(a,b,Point(0,0),r,p,num);
        if(inb)return SectorArea(p[0],a,r)+fabs(Cross(p[0],b))/2.0;
        else{
            if(num==2)return SectorArea(a,p[0],r)+SectorArea(p[1],b,r)+fabs(Cross(p[0],p[1]))/2.0; // segment ab has 2 point intersect with circle
            else return SectorArea(a,b,r); // segment has no intersect point with circle
        }
    }
}
