struct MultiEval {
    MultiEval *lc, *rc;
    vector<int> p, ml;
    // v is the points to be queried
    MultiEval(const vector<int> &v, int l, int r) : lc(nullptr), rc(nullptr) {
        if (r - l <= 64) {
            p = vector<int>(v.begin() + l, v.begin() + r);
            ml.resize(1, 1);
            for (int x : p) ml = Multiply(ml, {kMod - x, 1});
            return;
        }
        int m = (l + r) >> 1;
        lc = new MultiEval(v, l, m), rc = new MultiEval(v, m, r);
        ml = Multiply(lc->ml, rc->ml);
    }
    // poly is the polynomial to be evaluated
    void Query(const vector<int> &poly, vector<int> &res, int l, int r) const {
        if (r - l <= 64) {
            for (int x : p) {
                int s = 0, bs = 1;
                for (int i = 0; i < poly.size(); ++i) {
                    (s += 1LL * bs * poly[i] % kMod) %= kMod;
                    bs = 1LL * bs * x % kMod;
                }
                res.push_back(s);
            }
            return;
        }
        auto pol = Modulo(poly, ml);
        int m = (l + r) >> 1;
        lc->Query(pol, res, l, m), rc->Query(pol, res, m, r);
    }
};
