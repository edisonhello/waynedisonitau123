#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    multiset<int> a;
    multiset<int> b;
    for (int i = 0; i < n; ++i) {
        int t; cin >> t;
        a.insert(t);
    }
    for (int i = 0; i < n; ++i) {
        int t; cin >> t;
        b.insert(t);
    }
    int sc = 0;
    vector<int> bye;
    for (int i : b) {
        auto it = a.lower_bound(i);
        if (it == a.begin()) continue;
        it = prev(it);
        a.erase(it);
        bye.push_back(i);
        sc += 2;
    }
    for (int i : bye) b.erase(b.find(i));
    bye.clear();
    for (int i : b) {
        if (a.count(i)) {
            ++sc;
            bye.push_back(i);
            a.erase(a.find(i));
        }
    }
    for (int i : bye) b.erase(b.find(i));
    cout << sc << endl;
}
