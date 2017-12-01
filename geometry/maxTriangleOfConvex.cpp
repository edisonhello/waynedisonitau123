double ConvexHullMaxTriangleArea(Point p[],int res[],int chnum) {
    double area=0,tmp;
    res[chnum]=res[0];
    for(int i=0,j=1,k=2;i<chnum;i++){
        while(fabs(Cross(p[res[j]]-p[res[i]],p[res[(k+1)%chnum]]-p[res[i]]))>fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]])))k=(k+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if(tmp>area)area=tmp;
        while(fabs(Cross(p[res[(j+1)%chnum]]-p[res[i]],p[res[k]]-p[res[i]]))>fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]])))j=(j+1)%chnum;
        tmp=fabs(Cross(p[res[j]]-p[res[i]],p[res[k]]-p[res[i]]));
        if(tmp>area)area=tmp;
    }
    return area/2;
}
