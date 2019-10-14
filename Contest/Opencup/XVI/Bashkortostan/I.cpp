#include <bits/stdc++.h>
using namespace std;
 
void next_gen(vector<int> &can, int should) {
    vector<int> nx;
    for (int i : can) {
        if ((__builtin_popcount(i) & 1) == should) {
            nx.push_back((487237ll * i + 1011807) & ((1ll << 20) - 1));
        }
    }
    can.swap(nx);
}
 
int get_next(vector<int> &can) {
    int rr = __builtin_popcount(can[0]) & 1;
     next_gen(can, rr);
    return rr;
}
 
int _x, qc = 0;
 
int Query(int v, int $) {
#ifdef LOCALZ
    ++qc;
    int res = -1;
    if (__builtin_popcount(_x) % 2 == 0) res = $ - v;
    else res = $ + v;
    _x = (487237ll * _x + 1011807) & ((1 << 20) - 1);
    if (res == 200) res = -1, cout << "good" << endl;
    if (qc > 200) res = -1, cout << "bad" << endl;
    // cout << "qc = " << qc << ", bet = " << v << ", res = " << res << endl;
    return res;
#else
    cout << v << endl; fflush(stdout);
    int res; cin >> res;
    if (res == -1) exit(0);
    return res;
#endif
}
 
int main() {
#ifdef LOCALZ
    cin >> _x;
#endif
    vector<int> can(1 << 20); iota(can.begin(), can.end(), 0);
    int $; cin >> $;
    assert($ == 160);
    while ((int)can.size() > 1) {
        int $$ = Query(1, $);
        if ($$ == -1) exit(0);
        if ($$ > $) next_gen(can, 1);
        else next_gen(can, 0);
        $ = $$;
    }
    if (can.empty()) assert(false);
    while ($ != 200) {
        int nxt = get_next(can);
        if (nxt == 1) $ = Query(200 - $, $); 
        else $ = Query(1, $);
        if ($ == -1) exit(0);
    }
#ifdef LOCALZ
    assert(qc <= 200);
    cout << "win" << endl;
#endif
}
