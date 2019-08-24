array<Point, 2> tangent(Point o, double r, Point p) {
    double dist = sqrt((p - o) * (p - o));
    double len = sqrt(dist * dist - r * r);
    double ang = acos(len / dist);
    Point vec = (o - p) / dist * len;
    array<Point, 2> res;
    for (int i = 0; i < 2; ++i) {
        int z = i == 0 ? 1 : -1;
        Point v(vec.x * cos(z * ang) - vec.y * sin(z * ang), vec.x * sin(z * ang) + vec.y * cos(z * ang));
        res[i] = p + v; 
    }
    return res;
}

