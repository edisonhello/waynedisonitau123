Point TriangleOrthoCenter(Point a, Point b, Point c) { 
    return TriangleMassCenter(a, b, c) * 3.0 - TriangleCircumCenter(a, b, c) * 2.0;
}
