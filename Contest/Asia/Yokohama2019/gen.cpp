#include <bits/stdc++.h>
using namespace std;


int main() {
    srand(time(0) * clock());
    int n = rand() % 3 + 1;
    cout << n << endl;
    set<string> st;
    while (n--) {
        string s;
        while (true) {
            int len = rand() % 3 + 1;
            s = "";
            while ((int)s.size() < len) s += rand() & 1 ? "0" : "1";
            if (st.count(s) == 0) break;
        }
        cout << s << endl;
        st.insert(s);
    }
}
