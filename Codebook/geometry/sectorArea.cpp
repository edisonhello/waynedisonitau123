// calc area of sector which include a, b
double SectorArea(P a, P b, double r) {
    double o = atan2(a.y, a.x) - atan2(b.y, b.x);
    while (o <= 0) o += 2 * pi;
    while (o >= 2 * pi) o -= 2 * pi;
    o = min(o, 2 * pi - o);
    return r * r * o / 2;
}
