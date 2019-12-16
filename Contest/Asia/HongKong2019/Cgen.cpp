#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    srand(atoi(argv[1]));
    cout << 1 << endl;
    cout << 10 << endl;
    for (int i = 0; i < 10; ++i) cout << rand() % 10 + 1 << ' ';
    cout << endl;
    for (int i = 1; i < 10; ++i) {
        int p = rand() % i;
        cout << p + 1 << ' ' << i + 1 << endl;
    }
    // cout << 5 << endl;
    // for (int i = 0; i < 5; ++i) cout << rand() % 5 + 1 << ' ';
    // cout << endl;
    // for (int i = 1; i < 5; ++i) {
    //     int p = rand() % i;
    //     cout << p + 1 << ' ' << i + 1 << endl;
    // }
}
