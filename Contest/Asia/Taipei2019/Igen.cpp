#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0) * clock());
    int n = 62; cout << n << endl;
    set<int> st;
    st.insert(0);
    while ((int)st.size() < n) {
        st.insert(rand() % 1000);
    }
    vector<int> v;
    for (int i : st) v.push_back(i);
    vector<int> giv;
    for (int i = 0; i < (int)st.size(); ++i) for (int j = i + 1; j < (int)st.size(); ++j) {
        giv.push_back(v[j] - v[i]);
    }
    sort(giv.begin(), giv.end());
    for (int i : giv) cout << i << ' '; 
    cout << endl;
}
