namespace km {
int w[kN][kN], hl[kN], hr[kN], slk[kN];
int fl[kN], fr[kN], pre[kN], qu[kN], ql, qr;
bool vl[kN], vr[kN];
bool Check(int x) {
    if (vl[x] = true, fl[x] != -1) return vr[qu[qr++] = fl[x]] = true;
    while (x != -1) swap(x, fr[fl[x] = pre[x]]);
    return false;
}
void Bfs(int s, int n) {
    fill(slk, slk + n, kInf);
    fill(vl, vl + n, false);
    fill(vr, vr + n, false);
    ql = qr = 0;
    qu[qr++] = s;
    vr[s] = true;
    while (true) {
        int d;
        while (ql < qr) {
            for (int x = 0, y = qu[ql++]; x < n; ++x) {
                if (!vl[x] && slk[x] >= (d = hl[x] + hr[y] - w[x][y])) {
                    if (pre[x] = y, d) slk[x] = d;
                    else if (!Check(x)) return;
                }
            }
        }
        d = kInf;
        for (int x = 0; x < n; ++x) {
            if (!vl[x] && d > slk[x]) d = slk[x];
        }
        for (int x = 0; x < n; ++x) {
            if (vl[x]) hl[x] += d;
            else slk[x] -= d;
            if (vr[x]) hr[x] -= d;
        }
        for (int x = 0; x < n; ++x) {
            if (!vl[x] && !slk[x] && !Check(x)) return;
        }
    }
}
long long Solve(int n) {
    fill(fl, fl + n, -1);
    fill(fr, fr + n, -1);
    fill(hr, hr + n, 0);
    for (int i = 0; i < n; ++i) hl[i] = *max_element(w[i], w[i] + n);
    for (int i = 0; i < n; ++i) Bfs(i, n);
    long long res = 0;
    for (int i = 0; i < n; ++i) res += w[i][fl[i]];
    return res;
}}

