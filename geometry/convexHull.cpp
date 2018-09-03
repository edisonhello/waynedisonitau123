vector<point> convex(vector<point> p) {
    sort(p.begin(), p.end());
    vector<point> ch;
    for (int i = 0; i < n; ++i) {
        while (ch.size() >= 2 && ((p[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) ch.pop_back();
        ch.push_back(p[i]);
    }
    int t = ch.size();
    for (int i = n - 2; i >= 0; --i) {
        while (ch.size() > t && ((p[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) ch.pop_back();
        ch.push_back(p[i]);
    }
    ch.pop_back();
    return ch;
}
