#include <bits/stdc++.h>
using namespace std;

multiset<int> Ask(vector<int> v) {
    if (v.size() <= 1u) return multiset<int>();

    cout << "2 " << v.size();
    for (int i : v) cout << ' ' << i;
    cout << endl;

    int x = v.size() * (v.size() - 1) / 2;
    multiset<int> st;
    while (x--) {
        int t; cin >> t;
        st.insert(t);
    }
    return st;
}

int main() {
    int n; cin >> n;
    if (n <= 5) {
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cout << "1 " << i << endl;
            cin >> a[i];
        }
        cout << "3 ";
        for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
        cout << endl;
    } else {
        vector<int> a(n + 1);
        cout << "1 " << n << endl;
        cin >> a[n];
        cout << "1 " << n - 1 << endl;
        cin >> a[n - 1];

        vector<set<int>> haves(10);
        set<int> all;
        for (int z = 0; z < 8; ++z) {
            vector<int> asklist;
            for (int i = 1; i <= n - 2; ++i) {
                if (i & (1 << z)) asklist.push_back(i);
            }

            multiset<int> res = Ask(asklist);
            asklist.push_back(n - 1);
            multiset<int> resa = Ask(asklist);
            asklist.back() = n;
            multiset<int> resb = Ask(asklist);
            asklist.pop_back();

            for (int i : res) resa.erase(resa.find(i));
            for (int i : res) resb.erase(resb.find(i));

            vector<int> aa(resa.begin(), resa.end());
            vector<int> bb(resb.begin(), resb.end());

            set<int> have;

            if (a[n - 1] > a[n]) {
                for (int i = aa.size() - 1; i >= 0; --i) {
                    if (resb.count(a[n - 1] + aa[i] - a[n])) {
                        have.insert(a[n - 1] + aa[i]);
                        resb.erase(resb.find(a[n - 1] + aa[i] - a[n]));
                    } else {
                        have.insert(a[n - 1] - aa[i]);
                        resb.erase(resb.find(abs(a[n - 1] - aa[i] - a[n])));
                    }
                }
            } else {
                for (int i = bb.size() - 1; i >= 0; --i) {
                    if (resa.count(a[n] + bb[i] - a[n - 1])) {
                        have.insert(a[n] + bb[i]);
                        resa.erase(resa.find(a[n] + bb[i] - a[n - 1]));
                    } else {
                        have.insert(a[n] - bb[i]);
                        resa.erase(resa.find(abs(a[n] - bb[i] - a[n - 1])));
                    }
                }
            }

            haves[z] = have;
            for (int i : have) all.insert(i);
        }

        for (int i : all) {
            int v = 0;
            for (int z = 0; z < 8; ++z) if (haves[z].count(i)) v |= 1 << z;
            a[v] = i;
        }

        cout << 3 << " ";
        for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
        cout << endl;
    }
}

