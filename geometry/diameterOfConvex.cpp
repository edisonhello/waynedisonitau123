// get diameter of p[res[]] store opposite points in app
double Diameter(Point p[], int res[], int chnum, int app[][2], int &appnum) {
    double ret = 0, nowlen;
    res[chnum] = res[0];
    appnum = 0;
    for (int i = 0, j = 1; i < chnum; ++i) {
        while (Cross(p[res[i]] - p[res[i + 1]], p[res[j + 1]] - p[res[i + 1]]) < Cross(p[res[i]] - p[res[i + 1]], p[res[j]] - p[res[i + 1]])) {
            ++j;
            j %= chnum;
        }
        app[appnum][0] = res[i];
        app[appnum][1] = res[j];
        ++appnum;
        nowlen = dis(p[res[i]], p[res[j]]);
        if (nowlen > ret) ret = nowlen;
        nowlen = dis(p[res[i + 1]], p[res[j + 1]]);
        if (nowlen > ret) ret = nowlen;
    }
    return ret;
}
