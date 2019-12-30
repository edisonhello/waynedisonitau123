#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0) * clock());
    int k = 128; cout << k << endl;
    for (int i = 0; i < k; ++i) cout << rand() % 1000000000 << ' '; cout << endl;
    set<int> b;
    while (b.size() < k) b.insert(rand() % 1000000000);
    for (int i : b) cout << i << ' '; cout << endl;
}
