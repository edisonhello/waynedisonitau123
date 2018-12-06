struct query { int op, l, r, k, qid; };
// op = 1: insertion (l = pos, r = val)
// op = 2: deletion (l = pos, r = val)
// op = 3: query

void bs(vector<query> &qry, int l, int r) {
    // answer to queries in qry are from l to r
    if (l == r) {
        for (int i = 0; i < qry.size(); ++i) {
            if (qry[i].op == 3) ans[qry[i].qid] = l;
        }
        return;
    }
    if (qry.size() == 0) return;
    int m = l + r >> 1;
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 1 && qry[i].r <= m) bit.add(qry[i].l, 1);
        else if (qry[i].op == 2 && qry[i].r <= m) bit.add(qry[i].l, -1);
        else if (qry[i].op == 3) tmp[qry[i].qid] += bit.qry(qry[i].r) - bit.qry(qry[i].l - 1);
    }    
    vector<query> ql, qr;
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 3) {
            if (qry[i].k - tmp[qry[i].qid] > 0) qry[i].k -= tmp[qry[i].qid], qr.push_back(qry[i]);
            else ql.push_back(qry[i]);
            tmp[qry[i].qid] = 0;
            continue;
        }
        if (qry[i].r <= m) ql.push_back(qry[i]);
        else qr.push_back(qry[i]);
    }
    for (int i = 0; i < qry.size(); ++i) {
        if (qry[i].op == 1 && qry[i].r <= m) bit.add(qry[i].l, -1);
        else if (qry[i].op == 2 && qry[i].r <= m) bit.add(qry[i].l, 1);
    }    
    bs(ql, l, m), bs(qr, m + 1, r);
}
