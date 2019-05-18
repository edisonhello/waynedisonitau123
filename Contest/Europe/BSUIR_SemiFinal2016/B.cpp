#include <bits/stdc++.h>
using namespace std;


int main() {
    long long a, b; cin >> a >> b;
    stack<int> st;
    while (a > 1 || b > 1) {
        if (a > (1ll << (b - 1))) {
            st.push(1);
            a = (1ll << b) - a;
        } else {
            --b;
            st.push(0);
        }
    }
    cout << 0;
    while (st.size()) {
        cout << st.top();
        st.pop();
    }
    cout << endl;
}
