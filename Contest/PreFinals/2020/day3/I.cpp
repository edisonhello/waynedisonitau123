#include <bits/stdc++.h>
using namespace std;

// map<int, int> answer;
set<long long> ans[105];

int main() {
    ans[9] = set<long long>{231, 45, 35, 15, 11, 9, 7, 5, 3};
    ans[11] = set<long long>{135, 105, 63, 35, 27, 21, 15, 9, 7, 5, 3};
    ans[13] = set<long long>{945, 189, 135, 105, 63, 45, 27, 21, 15, 9, 7, 5, 3};
    ans[15] = set<long long>{735, 441, 315, 245, 147, 105, 49, 45, 35, 21, 15, 9, 7, 5, 3};
    ans[17] = set<long long>{2835, 567, 405, 315, 189, 135, 105, 81, 63, 45, 35, 27, 15, 9, 7, 5, 3};
    ans[19] = set<long long>{1155, 693, 385, 315, 231, 165, 105, 99, 77, 55, 45, 35, 33, 21, 15, 11, 9, 5, 3};
    ans[21]=set<long long>{3465,1155,693,495,385,315,231,165,105,99,77,63,45,35,33,21,15,11,9,5,3};
    ans[23] = set<long long>{2835,945,675,567,525,405,315,189,175,135,105,81,75,63,45,35,27,25,21,15,7,5,3};

    ans[25]=set<long long>{4725,2835,1575,945,675,567,525,405,315,225,175,135,105,81,75,63,45,35,27,25,21,15,7,5,3};
ans[27]=set<long long>{22275,7425,4455,2475,2025,1485,891,825,675,495,405,297,275,225,165,99,81,55,45,33,27,25,15,11,9,5,3};
    int n; cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    if (n % 2 == 0) {
        cout << -1 << endl;
        exit(0);
    }
    if (n <= 7) {
        cout << -1 << endl;
        exit(0);
    }

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    
    for (int i = 29; i <= 100; i += 2) {
        // cerr << "i = " << i << endl;
        int j = i - 14;
        for (long long z : ans[j]) {
            ans[i] = ans[j];
            ans[i].erase(z);
            // cerr << "z = " << z << endl;

            bool bad = 0;
            for (long long y : ans[15]) {
                if (ans[i].count(y * z)) {
                    bad = 1;
                }
                if (y * z > kInf) {
                    cerr << "i = " << i << endl;
                    exit(0);
                }
                ans[i].insert(y * z);
            }

            if (!bad) break;
            else ans[i].clear();
        }

        assert(ans[i].size());
    }

    for (long long i : ans[n]) cout << i << ' ';
    cout << endl;


    // for (int i = 3; ; i += 2) {
    //     vector<int> facs;
    //     for (int j = 1; j < i; ++j) {
    //         if (i % j == 0) facs.push_back(j);
    //     }

    //     for (int z = 1; z < (1 << facs.size()); ++z) {
    //         int sum = 0;
    //         for (int y = 0; y < (int)facs.size(); ++y) if (z & (1 << y)) {
    //             sum += facs[y];
    //         }

    //         if (sum == i) {
    //             if (answer.count(__builtin_popcount(z))) continue;
    //             answer[__builtin_popcount(z)] = i;
    //             cout << "Use " << __builtin_popcount(z) << " construct " << i << " : ";
    //             for (int y = 0; y < (int)facs.size(); ++y) if (z & (1 << y)) cout << i / facs[y] << ' ';
    //             cout << endl;
    //         }
    //     }
    // }

}

