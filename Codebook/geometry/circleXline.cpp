// remove second level if to get points for line (defalut: segment)
vector<P> CircleCrossLine(P a, P b, P o, double r) {
    double x0 = o.x, y0 = o.y;
    double x1 = a.x, y1 = a.y;
    double x2 = b.x, y2 = b.y;
    double dx = x2 - x1, dy = y2 - y1;
    double A = dx * dx + dy * dy;
    double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
    double C = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r;
    double delta = B * B - 4 * A * C;
    vector<P> ret;
    if (delta >= -eps) {
        double t1 = (-B - sqrt(abs(delta))) / (2 * A);
        double t2 = (-B + sqrt(abs(delta))) / (2 * A);
        if (t1 - 1.0 <= eps && t1 >= -eps) ret.emplace_back(x1 + t1 * dx, y1 + t1 * dy);
        if (t2 - 1.0 <= eps && t2 >= -eps) ret.emplace_back(x1 + t2 * dx, y1 + t2 * dy);
    }
	return ret;
}
