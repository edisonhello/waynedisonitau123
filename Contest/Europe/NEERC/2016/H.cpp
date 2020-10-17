#include <bits/stdc++.h>
using namespace std;

int parseInt(string s) {
    return stoi(s);
}

int main() {
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);

    string s;
    vector<pair<int, int>> seg;
    while (getline(cin, s)) {
        stringstream ss(s);
        vector<string> v;
        while (ss >> s) v.push_back(s);
        if (v.back() == "||") v.pop_back();

        if (v.size() == 7u) {
            int L = parseInt(v[2]);
            int R = parseInt(v[6]);
            if (L > R) continue;
            seg.emplace_back(L, R);
        } else {
            int x = parseInt(v[2]);
            if (v[1] == "<=") {
                seg.emplace_back(-32768, x);
            } else {
                seg.emplace_back(x, 32767);
            }
        }
    }

    sort(seg.begin(), seg.end());
    if (seg.empty()) {
        cout << "false" << endl;
        exit(0);
    }

    vector<pair<int, int>> nseg;
    int cl = seg[0].first, cr = seg[0].second;
    for (auto &p : seg) {
        if (p.first <= cr + 1) {
            cr = max(cr, p.second);
        } else {
            nseg.emplace_back(cl, cr);
            cl = p.first, cr = p.second;
        }
    }
    nseg.emplace_back(cl, cr);

    if (nseg.size() == 1u && nseg[0] == make_pair(-32768, 32767)) {
        cout << "true" << endl;
        exit(0);
    }

    for (int i = 0; i < (int)nseg.size(); ++i) {
        auto p = nseg[i];
        if (p.first == -32768) {
            cout << "x <= " << p.second;
        } else if (p.second == 32767) {
            cout << "x >= " << p.first;
        } else {
            cout << "x >= " << p.first << " && x <= " << p.second;
        }

        if (i != (int)nseg.size() - 1) {
            cout << " ||";
        }

        cout << '\n';
    }
    
}

