#include <bits/stdc++.h>
using namespace std;

int a[5005], b[5005];

int calc2(int l, int r) { // return max possible
    // cerr << "calc2 " << l << " " << r << " : ";
    // for (int i = l; i <= r; ++i) cerr << b[i] << ' '; cerr << endl;
    vector<int> v;
    for (int i = l; i <= r; ++i) {
        v.push_back(b[i]);
        while (v.size() >= 3u && v[v.size() - 1] == -1 && v[v.size() - 2] == -1 && v[v.size() - 3] == -1) 
            v.pop_back(), v.pop_back();
        while (v.size() >= 2u && v[v.size() - 1] == 1 && v[v.size() - 2] == -1)
            v.pop_back(), v.pop_back();
    }
    int pt = 0;
    for (int i : v) pt += i;
    return pt;
    /* for (int i = l; i <= r; ++i) {
        v.push_back(b[i]);
        while (v.size() >= 3u && v[v.size() - 1] == -1 && v[v.size() - 2] == -1 && v[v.size() - 3] == -1) 
            v.pop_back(), v.pop_back();
    }
    vector<int> left(v.size()), right(v.size()), exist(v.size(), 1);
    left[0] = -1;
    right.back() = -1;
    for (int i = 1; i < (int)v.size(); ++i) left[i] = i - 1;
    for (int i = 0; i < (int)v.size() - 1; ++i) right[i] = i + 1;
    for (int i = 0; i < (int)v.size(); ++i) if (exist[i] && v[i] == -1) {
        int lok = left[i] == -1 || v[left[i]] == 1;
        int rok = right[i] == -1 || v[right[i]] == 1;
        if (lok + rok >= 1) {
            lok = v[left[i]] == 1;
            rok = v[right[i]] == 1;
            if (lok) {
                exist[i] = 0;
                if (right[i] != -1) left[right[i]] = left[i];
                if (left[i] != -1) right[left[i]] = right[i];
                exist[left[i]] = 0;
                if (right[left[i]] != -1) left[right[left[i]]] = left[left[i]];
                if (left[left[i]] != -1) right[left[left[i]]] = right[left[i]];
            } else if (rok) {
                exist[i] = 0;
                if (right[i]) left[right[i]] = left[i];
                if (left[i]) right[left[i]] = right[i];
                exist[right[i]] = 0;
                if (right[right[i]] != -1) left[right[right[i]]] = left[right[i]];
                if (left[right[i]] != -1) right[left[right[i]]] = right[right[i]];
            }
        }
    }

    vector<int> vv;
    for (int i = 0; i < (int)v.size(); ++i) if (exist[i]) vv.push_back(v[i]);
    v = vv; vv.clear();

    for (int i = 0 */ 
}

pair<int, int> calc(int l, int r) {
    if (r < l) return make_pair(0, 0);
    // cerr << "calc " << l << " " << r << endl;
    int z = calc2(l, r);
    for (int i = l; i <= r; ++i) b[i] = -b[i];
    int x = calc2(l, r);
    return make_pair(-x, z);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) b[j] = (a[j] < a[i] ? -1 : 1);
            pair<int, int> left = calc(1, i - 1),
                           right = calc(i + 1, n);
            right = make_pair(-right.second, -right.first);
            // cerr << "i = " << i << ", left = (" << left.first << ", " << left.second << ") right = (" << right.first << ", " << right.second << ")" << endl;
            if (min(left.second, right.second) >= max(left.first, right.first)) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }
}
