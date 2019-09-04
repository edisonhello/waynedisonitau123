struct CH {
    vector<P> p, u, d;
    CH() {}
    CH(vector<P> ps) {
        sort(ps.begin(), ps.end(), cmp);
        for (int i = 0; i < ps.size(); ++i) {
            while (p.size() >= 2 && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0) p.pop_back();
            p.push_back(ps[i]);
        }
        int t = p.size();
        for (int i = (int)ps.size() - 2; i >= 0; --i) {
            while (p.size() > t && ((ps[i] - p[p.size() - 2]) ^ (p[p.size() - 1] - p[p.size() - 2])) >= 0) p.pop_back();
            p.push_back(ps[i]);
        }
        for (int i = 0; i < t; ++i) d.push_back(p[i]);
        for (int i = t; i < p.size(); ++i) u.push_back(p[i]);
        p.pop_back();
    }
};
