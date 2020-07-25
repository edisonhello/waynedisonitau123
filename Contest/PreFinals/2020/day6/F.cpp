#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
};

long long operator^ (const P &a, const P &b) { return 1ll * a.y * b.x - 1ll * a.x * b.y; }
bool operator< (const P &a, const P &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
ostream& operator<< (ostream &o, const P p) { o << "(" << p.x << ", " << p.y << ")"; return o; }

long long CalcArea(P &a, P &b, P &c) {
    return abs((a ^ b) + (b ^ c) + (c ^ a));
}
long long CalcArea(P &a, P &b, P &c, P &d) {
    long long z = abs((a ^ b) + (b ^ c) + (c ^ d) + (d ^ a));
    // cerr << "CalcArea " << a << ' ' << b << ' ' << c << ' ' << d << " = " << z << endl;
    return z;
}
bool IsTu(P &a, P &b, P &c, P &d) {
    vector<long long> tris;
    tris.push_back(CalcArea(a, b, c));
    tris.push_back(CalcArea(a, b, d));
    tris.push_back(CalcArea(a, c, d));
    tris.push_back(CalcArea(b, c, d));
    sort(tris.begin(), tris.end());
    return tris[0] + tris[1] + tris[2] != tris[3];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<P> ps;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ps.emplace_back(P{x, y});
    }

    vector<int> id(n), pos(n);
    vector<pair<int, int>> line(n * (n - 1) / 2);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) 
            line[m++] = make_pair(i, j);
    }
    
    sort(line.begin(), line.end(), [&] (const pair<int, int> &a, const pair<int, int> &b) -> bool {
        if (ps[a.first].x == ps[a.second].x) return 0;
        if (ps[b.first].x == ps[b.second].x) return 1;
        return (double)(ps[a.first].y - ps[a.second].y) / (ps[a.first].x - ps[a.second].x) < 
               (double)(ps[b.first].y - ps[b.second].y) / (ps[b.first].x - ps[b.second].x);
    });

    for (int i = 0; i < n; ++i) id[i] = i;
    sort(id.begin(), id.end(), [&] (const int &a, const int &b) { return ps[a] < ps[b]; });
    for (int i = 0; i < n; ++i) pos[id[i]] = i;

    long long min_area = LLONG_MAX;
    int cnt_ou = 0, cnt_tu = 0;
    long long sumab = 0;

    for (int i = 0; i < m; ++i) {
        auto li = line[i];

        // cerr << "now li = " << li.first << ", " << li.second << endl;

        int l = min(pos[li.first], pos[li.second]);
        int r = max(pos[li.first], pos[li.second]);
        int pl = l, pr = r;

        // cerr << "pos l r " << l << ' ' << r << endl;
        // cerr << "id: ";
        // for (int i : id) cerr << i << ' '; cerr << endl;
        // cerr << "pos: ";
        // for (int i : pos) cerr << i << ' '; cerr << endl;

        if (l > 0 && r < n - 1) {
            --pl, ++pr;
            long long now_area = CalcArea(ps[id[pl]], ps[li.first], ps[id[pr]], ps[li.second]);
            // cerr << "\tnow_area = " << now_area << endl;
            if (now_area > min_area);
            else {
                if (now_area < min_area) min_area = now_area, cnt_ou = 0, cnt_tu = 0;

                while (pl > 0 && CalcArea(ps[id[pl - 1]], ps[li.first], ps[id[pr]], ps[li.second]) == now_area) --pl;
                while (pr < n - 1 && CalcArea(ps[id[pl]], ps[li.first], ps[id[pr + 1]], ps[li.second]) == now_area) ++pr;

                // cerr << "\t\tpl pr " << pl << ' ' << pr << endl;

                for (int ppl = pl; ppl < l; ++ppl) for (int ppr = r + 1; ppr <= pr; ++ppr) {
                    if (IsTu(ps[id[ppl]], ps[li.first], ps[id[ppr]], ps[li.second])) ++cnt_tu;
                    else ++cnt_ou;
                }
            }
        }

        sumab += 1ll * (n - 1 - r) * l;
        // cerr << "sumab now = " << sumab << endl;

        tie(pos[li.first], pos[li.second], id[pos[li.first]], id[pos[li.second]]) = 
            make_tuple(pos[li.second], pos[li.first], li.second, li.first);
    }


    // cerr << "cnt_ou tu " << cnt_ou << ' ' << cnt_tu << endl;


    cout << (cnt_ou + cnt_tu / 2) * 2 + sumab << endl;
}

