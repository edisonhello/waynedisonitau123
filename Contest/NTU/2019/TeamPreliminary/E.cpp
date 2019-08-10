#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    multiset<int> st;
    queue<int> q;
    while (n--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int x; scanf("%d", &x);
            st.insert(x);
            q.push(x);
        } else {
            int x = q.front();
            st.erase(st.find(x));
            q.pop();
        }
        if (st.empty()) printf("0\n");
        else printf("%d\n", *st.rbegin());
    }
}
