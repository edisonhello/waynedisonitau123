#include <bits/stdc++.h>
using namespace std;


int main() {
    string s; getline(cin, s);
    int cnt = 0;
    while (s.back() == '!') {
        ++cnt;
        s.pop_back();
    }
    if (cnt == 0) {
        cout << "Pfff" << endl;
    } else {
        cout << "W";
        for (int i = 0; i < cnt; ++i) cout << "o";
        cout << "w" << endl;
    }
}
