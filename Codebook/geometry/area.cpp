// point sort in counterclockwise
double ConvexPolygonArea(vector<P> &p) {
    double area = 0;
    for (int i = 1; i < p.size() - 1; i++) area += (p[i] - p[0]) ^ (p[i + 1] - p[0]);
    return area * 0.5;
}
