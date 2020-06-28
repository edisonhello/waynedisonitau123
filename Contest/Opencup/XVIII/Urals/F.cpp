#include <bits/stdc++.h>
using namespace std;

vector<int> p_, rev_;
int counter_, n;

int Ask(int a, int b, int c) {
    static map<tuple<int, int, int>, int> mp;
    auto it = mp.find(make_tuple(a, b, c));
    if (it != mp.end()) return it->second;
#ifndef LOCAL
    cout << "? ";
    cout << a << ' ' << b << ' ' << c << endl;
    int x; cin >> x;
#else
    counter_++;
    int g = (1LL * p_[a] * p_[b] + p_[c]) % n;
    int x = rev_[g];
#endif
    return mp[make_tuple(a, b, c)] = x;

}

int FindZ(int n) {
    vector<int> cand;
    for (int i = 0; i < n; ++i) {
        if (Ask(i, i, i) == i) cand.push_back(i);
    }

    vector<int> xs(n);
    iota(xs.begin(), xs.end(), 0);
    random_shuffle(xs.begin(), xs.end());
    while (cand.size() > 1u && xs.size()) {
        vector<int> tmp;
        for (int i : cand) {
            if (Ask(i, xs.back(), 0) == 0) tmp.push_back(i);
        }
        xs.pop_back();
        cand = tmp;
    }

    assert(cand.size() == 1u);
    return cand[0];
}

int FindM1(int n, int z) {
    vector<int> cand;
    for (int i = 0; i < n; ++i) if (i != z) {
        if (Ask(i, i, i) == Ask(z, z, z)) cand.push_back(i);
    }

    vector<int> xs(n);
    iota(xs.begin(), xs.end(), 0);
    random_shuffle(xs.begin(), xs.end());
    while (cand.size() > 1u && xs.size()) {
        vector<int> tmp;
        for (int i : cand) {
            if (Ask(i, xs.back(), xs.back()) == z) tmp.push_back(i);
        }
        xs.pop_back();
        cand = tmp;
    }

    assert(cand.size() == 1u);
    return cand[0];
}

int main() {
    cin >> n;
#ifdef LOCAL
    srand(clock() + time(0));
    p_.resize(n);
    iota(p_.begin(), p_.end(), 0);
    random_shuffle(p_.begin(), p_.end());
    rev_.resize(n);
    for (int i = 0; i < n; ++i) rev_[p_[i]] = i;
#endif

    if (n == 1) {
        cout << "! " << 0 << endl;
        exit(0);
    }

    int z = FindZ(n);

    int ne = FindM1(n, z);

    vector<int> p = {z};
    while ((int)p.size() < n) {
        p.push_back(Ask(ne, ne, p.back()));
    }

    vector<int> inv(n);
    for (int i = 0; i < n; ++i) inv[p[i]] = i;
    cout << "!";
    for (int i : inv) cout << ' ' << i;
    cout << endl;
#ifdef LOCAL
    assert(p_ == inv);
    counter_++;
    assert(counter_ <= 12512);
#endif
}

