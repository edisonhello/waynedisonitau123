#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n;

    vector<int> a(n), b(n), posa(n), posb(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        posa[a[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        --b[i];
        posb[b[i]] = i;
    }

    set<int> ali;
    for (int i = 0; i < n; ++i) ali.insert(i);

    auto Prev = [&] (int x) {
        return (x - 1 + n) % n;
    };
    auto Next = [&] (int x) {
        return (x + 1) % n;
    };

    while (ali.size()) {
        int start = *ali.begin();
        vector<int> road = vector<int>{start};
        // cerr <// // // // // // < "start = " << start << endl;
        int l1 = posa[start], r1 = posa[start];
        int l2 = posb[start], r2 = posb[start];

        while ((int)road.size() < n) {
            // cerr << "l1 r1 l2 r2 " << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
            set<int> st;
            st.insert(a[Prev(l1)]);
            st.insert(a[Next(r1)]);

            if (st.count(b[Prev(l2)])) {
                road.push_back(b[Prev(l2)]);
                // cerr << "next = " << b[Prev(l2)] << endl;
                l2 = Prev(l2);
                if (a[Prev(l1)] == b[l2]) l1 = Prev(l1);
                else r1 = Next(r1);
            } else if (st.count(b[Next(r2)])) {
                road.push_back(b[Next(r2)]);
                // cerr << "next = " << b[Next(l2)] << endl;
                r2 = Next(r2);
                if (a[Prev(l1)] == b[r2]) l1 = Prev(l1);
                else r1 = Next(r1);
            } else break;
        }

        if ((int)road.size() != n) {
            for (int i : road) ali.erase(i);
        } else {
            for (int i : road) cout << i + 1 << ' ';
            cout << endl;
            exit(0);
        }
    }
    cout << -1 << endl;
}

