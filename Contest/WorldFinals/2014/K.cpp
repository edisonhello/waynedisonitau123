#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> segs;
    for (int i = 1; i <= k; ++i) {
        int u, v; cin >> u >> v;
        segs.emplace_back(u, v);
    }
    sort(segs.begin(), segs.end(), [&] (pair<int, int> a, pair<int, int> b) { return a.first == b.first ? a.second > b.second : a.first < b.first; });

    [&] () -> void {
        vector<pair<int, int>> nsegs;
        int rrr = -1;
        for (auto p : segs) {
            int l, r;
            tie(l, r) = p;
            if (r < l) rrr = max(rrr, r);
        }
        if (rrr != -1) {
            for (auto p : segs) {
                int l, r;
                tie(l, r) = p;
                if (l <= r && r <= rrr);
                else nsegs.push_back(p);
            }
            nsegs.swap(segs);
        }
    } ();

    [&] () -> void {
        vector<pair<int, int>> nsegs;
        int curr = -1;
        bool flip = false;
        for (auto p : segs) {
            int l, r;
            tie(l, r) = p;
            if (l <= r) {
                if (flip) continue;
                if (r > curr) {
                    curr = r;
                    nsegs.emplace_back(l, r);
                }
            } else {
                r += n;
                if (flip) {
                    if (r > curr) {
                        curr = r;
                        nsegs.emplace_back(l, r);
                    }
                } else {
                    curr = r;
                    nsegs.emplace_back(l, r);
                }
                flip = 1;
            }
        }
        segs.swap(nsegs);
    } ();


    // cerr << "segs: " << endl;
    // for (int i = 0; i < (int)segs.size(); ++i) {
    //     cerr << segs[i].first << ", " << segs[i].second << endl;
    // }

    auto choose = [&] () {
        int start = segs[0].first;
        int nr = segs[0].second;
        int rrr = nr;
        int rrrid = -1;
        vector<int> rt;
        rt.push_back(0);
        for (int i = 0; i < (int)segs.size(); ++i) {
            int l, r; 
            tie(l, r) = segs[i];
            // cerr << "i l r " << i << ' ' << l << ' ' << r << " nr " << nr << " rrr " << rrr << endl;
            if (l <= nr + 1) {
                rrr = r;
                rrrid = i;
            } else {
                if (l > rrr + 1) {
                    cout << "impossible" << endl;
                    exit(0);
                }
                rt.push_back(rrrid);
                rrrid = i;
                nr = rrr;
                rrr = r;
            }
        }
        // cerr << "rrr " << rrr << " rid " << rrrid << endl;
        if (rrr < start - 1 + n) {
            cout << "impossible" << endl;
            exit(0);
        }
        if (nr < start - 1 + n) {
            rt.push_back(rrrid);
        }
        return rt;
    } ();

    // cerr << "choosed: ";
    // for (int i : choose) cerr << i << ' ';
    // cerr << endl;

    int near = INT_MAX, neari = -1;
    for (int i = 1; i < (int)choose.size(); ++i) {
        if (choose[i] - choose[i - 1] < near) {
            near = choose[i] - choose[i - 1];
            neari = i;
        }
    }

    vector<int> ty;
    if (neari != -1) {
        for (int j = choose[neari - 1]; j <= choose[neari]; ++j) {
            ty.push_back(j);
        }
    } else ty.push_back(choose[0]);


    int mn = INT_MAX;
    for (int j : ty) {
        // cerr << "start from " << j << endl;
        int cnt = 1;
        int nr = segs[j].second;
        int rrr = nr;
        bool flip = 0;
        for (int k = j, cc = 0; cc < (int)segs.size(); ++cc, k = (k == (int)segs.size() - 1 ? (flip = 1, 0) : k + 1)) {
            if (segs[k].first + (flip ? n : 0) <= nr + 1) {
                rrr = segs[k].second + (flip ? n : 0);
            } else {
                // cerr << "new cnt " << endl;
                ++cnt;
                nr = rrr;
                rrr = segs[k].second + (flip ? n : 0);
                if (cnt >= mn) break;
            }
            // cerr << "nr rrr " << nr << ' ' << rrr << " cnt " << cnt << endl;
        }
        // cerr << "nr = " << nr << endl;
        // cerr << "rrr = " << rrr << endl;
        if (rrr >= segs[j].first + n - 1) {
            if (nr < segs[j].first + n - 1) ++cnt;
            // cerr << "cnt = " << cnt << endl;

            mn = min(mn, cnt);
        }
    }

    cout << mn << endl;

}

