#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(0) * clock());
    int m = rand() % 100 + 1;
    int n = rand() % (m + 1);
    int d = rand() % 100000 + 2;
    cout << m << ' ' << n << ' ' << d << endl;
}
