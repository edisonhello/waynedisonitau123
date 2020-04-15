#include <bits/stdc++.h>
using namespace std;

vector<int> Kmp(const vector<int> &s) {
    vector<int> f(s.size(), 0);
    int k = 0;
    for (int i = 1; i < s.size(); ++i) {
        while (k > 0 && s[i] != s[k]) k = f[k - 1];
        if (s[i] == s[k]) k++; 
        f[i] = k;
    }
    return f;
}

int Search(const vector<int> &s, const vector<int> &t) {
    auto f = Kmp(t);
    for (int i = 0, k = 0; i < s.size(); ++i) {
        while (k > 0 && (k == t.size() || s[i] != t[k])) k = f[k - 1];
        if (s[i] == t[k]) k++;
        if (k == t.size()) return i - t.size() + 1;
    }
    return -1;
}


int CheckCyclic(vector<int> v, vector<int> u) {
    // cerr << "CheckCyclic" << endl;
    // cerr << "v: "; for (int i : v) cerr << i << ' '; cerr << endl;
    // cerr << "u: "; for (int i : u) cerr << i << ' '; cerr << endl;
    vector<int> vv(v.begin(), v.end());
    vv.insert(vv.end(), v.begin(), v.end());
    return Search(vv, u);
    // TODO
    for (int r = 0; r < (int)v.size(); ++r) {
        bool ok = 1;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[(i + r) % v.size()] != u[i]) {
                ok = 0;
                break;
            }
        }
        if (ok) return r;
    }
    return -1;
}

int main() {
    string s; cin >> s;
    int t = 0;
    for (char c : s) {
        if (c == 'R') ++t;
        else if (c == 'L') --t;
    }

    bool _reverse = 0;
    if (t < 0) {
        _reverse = 1;
        for (char &c : s) {
            if (c == 'L') c = 'R';
            else if (c == 'R') c = 'L';
        }
        t *= -1;
    }

    if (t == 0) {
        set<int> pat;
        int cur = 0;
        for (char c : s) {
            if (c == 'R') ++cur;
            else if (c == 'L') --cur;
            else {
                if (pat.count(cur)) pat.erase(cur);
                else pat.insert(cur);
            }
        }

        int z; cin >> z;
        set<int> want;
        while (z--) {
            int y; cin >> y;
            if (_reverse) y *= -1;
            want.insert(y);
        }

        if (want == pat) {
            cout << "" << endl;
            exit(0);
        } else {
            cout << "NO" << endl;
            exit(0);
        }
    }

    // cerr << "t = " << t << endl;

    vector<int> pat;
    vector<int> modpat(t);
    int cur = 0;
    for (char c : s) {
        if (c == 'R') ++cur;
        else if (c == 'L') --cur;
        else {
            pat.push_back(cur);
            modpat[(cur % t + t) % t] ^= 1;
        }
    }

    int z; cin >> z;
    vector<int> want;
    vector<int> modwant(t);

    for (int i = 0; i < z; ++i) {
        int y; cin >> y;
        if (_reverse) y = -y;
        want.push_back(y);
        modwant[(y % t + t) % t] ^= 1;
    }


    int r = CheckCyclic(modpat, modwant);
    // cerr << "r = " << r << endl;
    if (r < 0) {
        cout << "NO" << endl;
        exit(0);
    }

    for (int &i : pat) i -= r;

    // cerr << "pat: ";
    // for (int i : pat) cerr << i << ' ';
    // cerr << endl;

    set<int> setpat;
    for (int i : pat) {
        if (setpat.count(i)) setpat.erase(i);
        else setpat.insert(i);
    }

    // cerr << "setpat: ";
    // for (int i : setpat) cerr << i << " ";
    // cerr << endl;

    map<int, int> fx;
    for (int i : want) {
        if (!setpat.count(i)) {
            fx[i] = 1;
        } else {
            setpat.erase(i);
        }
    }

    for (int i : setpat) fx[i] = 1;

    // cerr << "fx = ";
    // for (auto p : fx) {
    //     cerr << p.first << " ";
    // }
    // cerr << endl;

    set<int> light;
    while (fx.size()) {
        auto it = prev(fx.end());
        light.insert(it->first - t);
        fx[it->first - t] ^= 1;
        if (fx[it->first - t] == 0) {
            fx.erase(fx.find(it->first - t));
        }
        fx.erase(it);
    }

    // cerr << "light ";
    // for (int i : light) cerr << i << ' ';
    // cerr << endl;

    // cerr << "r = " << r << endl;

    string ans;
    if (light.size()) {
        int now = 0;
        while (now < *prev(light.end())) {
            ++now;
            ans += "R";
        }

        while (light.size()) {
            while (now > *prev(light.end())) {
                --now;
                ans += "L";
            }
            assert(now == *prev(light.end()));
            light.erase(prev(light.end()));
            ans += "X";
        }

        while (now < 0) now++, ans += "R";
        while (now > 0) now--, ans += "L";
    }
    if (r > 0) {
        while (r--) ans += "L";
    } else if (r < 0) {
        while (r++) ans += "R";
    }

    if (_reverse) {
        for (char &c : ans) {
            if (c == 'L') c = 'R';
            else if (c == 'R') c = 'L';
        }
    }

    cout << ans << endl;
}

