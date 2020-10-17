#include <bits/stdc++.h>
using namespace std;

constexpr int Z = 1000;
constexpr int ZZ = 3000;
using Row = bitset<ZZ>;
using Pat = array<Row, ZZ>;

ostream& operator << (ostream& o, const Pat &p) {
    for (int i = 0; i < ZZ; ++i) o << p[i] << '\n';
    return o;
}


Pat MoveDown(const Pat &x, int o) {
    Pat y;
    for (int i = 0; i < ZZ; ++i) {
        int ii = i + o;
        if (ii < 0 || ii >= ZZ) continue;
        y[ii] = x[i];
    }
    return y;
}

Pat Xor(const Pat &x, const Pat &y) {
    Pat z;
    for (int i = 0; i < ZZ; ++i) z[i] = x[i] ^ y[i];
    return z;
}

pair<int, int> Normal(Pat &x) {
    int u = ZZ, l = ZZ;
    for (int i = 0; i < ZZ; ++i) {
        int y = x[i]._Find_first();
        if (y != ZZ && u == ZZ) {
            u = i;
        }
        l = min(l, y);
    }
    int du = u - Z, dl = l - Z;
    Pat y;
    for (int i = 0; i < ZZ; ++i) {
        int ii = i - du;
        if (ii < 0 || ii >= ZZ) continue;
        y[ii] = (dl < 0 ? x[i] << (-dl) : x[i] >> dl);
    }
    x.swap(y);
    return make_pair(du, dl);
}

Pat pa, pb, pc;
int main() {
    freopen("kids.in", "r", stdin);
    freopen("kids.out", "w", stdout);

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            pa[i + Z][j + Z] = s[j] == '*';
        }
    }

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            pb[i + Z][j + Z] = s[j] == '*';
        }
    }

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) {
            pc[i + Z][j + Z] = s[j] == '*';
        }
    }

    auto nora = Normal(pa);
    auto norb = Normal(pb);
    auto norc = Normal(pc);
    auto Answer = [&] (int a, int b) {
        cout << "YES" << endl;
        cout << a + nora.second - norb.second << ' ' << b + nora.first - norb.first << endl;
        exit(0);
    };

    Row ra, rb, rc;
    for (int i = 0; i < ZZ; ++i) {
        ra[i] = pa[i][Z];
        rb[i] = pb[i][Z];
        rc[i] = pc[i][Z];
    }

    Row tmpc = rc >> rc._Find_first();
    for (int o = -Z; o <= Z; ++o) {
        Row tmp = (o < 0 ? ra ^ (rb >> (-o)) : ra ^ (rb << o));
        tmp >>= tmp._Find_first();

        if (tmp.count() == 0u) {
            Pat tpb = MoveDown(pb, o);
            Pat pab = Xor(pa, tpb);
            Normal(pab);
            if (pab == pc) {
                Answer(0, o);
            }
            // break;
        }
    }

    for (int o = -Z; o <= Z; ++o) {
        Row tmpa = (o < 0 ? ra >> (-o) : ra << o);
        if (tmpa == rc) {
            Pat tpa = MoveDown(pa, o);
            Pat tpb = Xor(tpa, pc);
            auto offs = Normal(tpb);
            if (tpb == pb) {
                Answer(offs.second, -o + offs.first); // ?
            }
            // break;
        }
    }

    for (int o = -Z; o <= Z; ++o) {
        Row tmpb = (o < 0 ? rb >> (-o) : rb << o);
        if (tmpb == rc) {
            Pat tpb = MoveDown(pb, o);
            Pat tpa = Xor(tpb, pc);
            auto offs = Normal(tpa);
            if (tpa == pa) {
                Answer(-offs.second, o - offs.first); // ?
            }
            // break;
        }
    }

    ra = pa[Z];
    rb = pb[Z];
    rc = pc[Z];

    if (ra == rc) {
        Pat tpb = Xor(pa, pc);
        auto offs = Normal(tpb);
        // assert(offs.first == 0);
        if (tpb == pb) {
            Answer(0, offs.first);
        }
    }
    // for (int o = -Z; o <= Z; ++o) {
    //     Row tmpa = (o < 0 ? ra >> (-o) : ra << o);
    //     if (tmpa == rc) {
    //         Pat tpa = MoveRight(pa, o);
    //         Pat tpb = Xor(tpa, pc);
    //         auto offs = Normal(tpb);
    //         // assert(offs.first == 0);
    //         if (tpb == pb) {
    //             Answer(0, offs.second);
    //         }
    //     }
    // }

    if (rb == rc) {
        Pat tpa = Xor(pb, pc);
        auto offs = Normal(tpa);
        // assert(offs.first);
        if (tpa == pa) {
            Answer(0, -offs.first);
        }
    }

    Pat tpc = Xor(pa, pb);
    Normal(tpc);
    if (pc == tpc) {
        Answer(0, 0);
    }

    cout << "NO" << endl;
}

