#include <bits/stdc++.h>
using namespace std;

bool good(deque<int> &v) {
    for (int i = 1; i < (int)v.size(); ++i) {
        if (v[i - 1] > v[i]) return false;
    }
    return true;
}

deque<int> go(deque<int> v) {
    deque<int> res;

    int dt = 1;
    res.push_back(-1);
    while (v.size()) {
        // cerr << "dt " << dt << endl;
        // cerr << "v: "; for (int i : v) cerr << i << ' '; cerr << endl;
        // cerr << "res: "; for (int i : res) cerr << i << ' '; cerr << endl;
        if (dt == 1) {
            if (v.front() >= res.back() && v.back() >= res.back()) {
                if (v.front() < v.back()) {
                    res.push_back(v.front());
                    v.pop_front();
                } else {
                    res.push_back(v.back());
                    v.pop_back();
                }
            } else if (v.front() >= res.back()) {
                res.push_back(v.front());
                v.pop_front();
            } else if (v.back() >= res.back()) {
                res.push_back(v.back());
                v.pop_back();
            } else dt = -1;
        } else {
            if (v.front() <= res.back() && v.back() <= res.back()) {
                if (v.front() > v.back()) {
                    res.push_back(v.front());
                    v.pop_front();
                } else {
                    res.push_back(v.back());
                    v.pop_back();
                }
            } else if (v.front() <= res.back()) {
                res.push_back(v.front());
                v.pop_front();
            } else if (v.back() <= res.back()) {
                res.push_back(v.back());
                v.pop_back();
            } else dt = 1;
        }
    }

    res.pop_front();
    // cerr << "v: "; for (int i : v) cerr << i << ' '; cerr << endl;
    // cerr << "res: "; for (int i : res) cerr << i << ' '; cerr << endl;
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    
    deque<int> v(n);

    for (int i = 0; i < n; ++i) cin >> v[i];

    int ans = 0;

    while (!good(v)) {
        ++ans;

        v = go(v);
    }

    cout << ans << endl;
}

