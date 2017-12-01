int Graham(Point p[], int n, int res[]) {
    int len, top;
    top = 1;
	sort(p, p + n, [](const Point &a, const Point &b) { return a.y == b.y ? a.x < b.x : a.y < b.y; }
    // QSort(p,0,n-1);
    for (int i = 0; i < 3; i++) res[i] = i;
    for (int i = 2; i < n; i++) {
        while (top && epssgn(Cross(p[i], p[res[top]], p[res[top - 1]])) >= 0) top--;
        res[++top] = i;
    }
    len = top;
    res[++top] = n - 2;
    for (int i = n-3; i>=0; i--) {
        while (top != len && epssgn(Cross(p[i], p[res[top]], p[res[top - 1]])) >= 0) top--;
        res[++top] = i;
    }
    return top;
}
