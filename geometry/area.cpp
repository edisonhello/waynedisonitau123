// point sort in counterclockwise
double ConvexPolygonArea(vector<Point> &p, int n) {
    double area = 0;
    for (int i = 1; i < p.size() - 1; i++) area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;
}
