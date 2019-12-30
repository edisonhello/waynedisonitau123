#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(clock() + time(0));
    int k = 5, m = 1;
    for (int i = 0; i < k; ++i) m *= 3;
    cout << k << endl;
    for (int i = 0; i < m; ++i) cout << rand() % 1000 << ' ';
    cout << endl; 
    for (int i = 0; i < m; ++i) cout << rand() % 1000 << ' ';
    cout << endl; 
}
