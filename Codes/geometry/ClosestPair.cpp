pt p[maxn];

double dis(const pt& a, const pt& b) {
    return sqrt((a - b) * (a - b));
}

double closest_pair(int l, int r) {
    if (l == r) return inf;
    if (r - l == 1) return dis(p[l], p[r]);
    int m = (l + r) >> 1;
    double d = min(closest_pair(l, m), closest_pair(m + 1, r));
    vector<int> vec;
    for (int i = m; i >= l && fabs(p[m].x - p[i].x) < d; --i) vec.push_back(i);
    for (int i = m + 1; i <= r && fabs(p[m].x - p[i].x) < d; ++i) vec.push_back(i);
    sort(vec.begin(), vec.end(), [=](const int& a, const int& b) { return p[a].y < p[b].y; });
    for (int i = 0; i < vec.size(); ++i) {
        for (int j = i + 1; j < vec.size() && fabs(p[vec[j]].y - p[vec[i]].y) < d; ++j) {
            d = min(d, dis(p[vec[i]], p[vec[j]]));
        }
    }
    return d;
}
