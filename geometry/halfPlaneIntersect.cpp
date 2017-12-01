int cmp(const Line & l1,const Line & l2){
    int d=epssgn(l1.angle-l2.angle);
    if(!d)return (epssgn(Cross(l2.p1-l1.p1,l2.p2-l1.p1))>0);
    return d<0;
}

void QSort(Line L[],int l,int r){
    int i=l,j=r;
    Line swap,mid=L[(l+r)/2];
    while(i<=j){
        while(cmp(L[i],mid))++i;
        while(cmp(mid,L[j]))--j;
        if(i<=j){
            swap=L[i];
            L[i]=L[j];
            L[j]=swap;
            ++i, --j;
        }
    }
    if(i<r)QSort(L,i,r);
    if(l<j)QSort(L,l,j);
}

int IntersectionOutOfHalfPlane(Line &hpl,Line &l1,Line &l2){
     Point p=GetIntersect(l1,l2);
     return epssgn(Cross(hpl.p1-p,hpl.p2-p))<0;
}

// move hpl for dis
Line HalfPlaneMoveIn(Line &hpl,double &dis){
    double dx=hpl.p1.x-hpl.p2.x;
    double dy=hpl.p1.y-hpl.p2.y;
    double ll=len(hpl.p1-hpl.p2);
    Point pa=Point(dis*dy/ll+hpl.p1.x,hpl.p1.y-dis*dx/ll);
    Point pb=Point(dis*dy/ll+hpl.p2.x,hpl.p2.y-dis*dx/ll);
    return Line(pa,pb);
}

// get intersect of n halfplane l, intersect point in p
void HalfPlaneIntersect(Line l[],int n,Point p[],int &pn){
    int i,j;
    int dq[MaxN],top=1,bot=0;
    QSort(l,0,n-1);
    for(i=j=0;i<n;i++)if(epssgn(l[i].angle-l[j].angle)>0)l[++j]=l[i];
    n=j+1;
    dq[0]=0;
    dq[1]=1;
    for(i=2;i<n;i++){
        while(top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[top]],l[dq[top-1]]))--top;
        while(top>bot && IntersectionOutOfHalfPlane(l[i],l[dq[bot]],l[dq[bot+1]]))++bot;
        dq[++top]=i;
    }
    while(top>bot && IntersectionOutOfHalfPlane(l[dq[bot]],l[dq[top]],l[dq[top-1]]))--top;
    while(top>bot && IntersectionOutOfHalfPlane(l[dq[top]],l[dq[bot]],l[dq[bot+1]]))++bot;
    dq[++top]=dq[bot];
    for(pn=0,i=bot;i<top;++i,++pn)p[pn]=GetIntersect(l[dq[i+1]],l[dq[i]]);
}
