#include <bits/stdc++.h>
using namespace std;

int r() {
    return rand() % 101;
}

int main() {
    srand(time(0) * clock());
    int t = 1; cout << t << endl;
    while (t--) {
        cout << r() << " " << r() << " " << r() << " " << r() << endl;
        int n = 20; cout << n << endl;
        while (n--) {
            cout << r() << " " << r() << endl;
        }
    }
}
