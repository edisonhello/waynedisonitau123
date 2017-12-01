bool PointInConvexHull(Point p[], int res[], int chnum, Point x) {
    Point g = (p[res[0]] + p[res[chnum / 3]] + p[res[2 * chnum / 3]]) / 3.0;
    int l = 0, r = chnum, mid;
    while (l + 1 < r) {
        mid = (l + r) >> 1;
        if (epssgn(Cross(p[res[l]] - g, p[res[mid]] - g)) > 0) {
            if (epssgn(Cross(p[res[l]] - g, x - g)) >=0 && epssgn(Cross(p[res[mid]] - g ,x - g)) < 0) r = mid;
            else l = mid;
        } else {
            if (epssgn(Cross(p[res[l]] - g, x - g)) < 0 && epssgn(Cross(p[res[mid]] - g, x - g)) >=0 ) l = mid;
            else r = mid;
        }
    }
    r %= chnum;
    return epssgn(Cross(p[res[r]] - x, p[res[l]] - x)) == -1;
}
