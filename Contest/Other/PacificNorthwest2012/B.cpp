#include <bits/stdc++.h>
using namespace std;


int main() {
    long long t; while (cin >> t) {
        set<int> st;

        auto parse = [&] (long long x) {

            while (x) {
                st.insert(x % 10);
                x /= 10;
            }
        };

        long long tt = 0;
        int k = 0;
        while (st.size() < 10u) {
            tt += t;
            ++k;
            parse(tt);
        }

        cout << k << '\n';
    }
}
