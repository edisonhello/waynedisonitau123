#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    while (getline(cin, s)) {
        string V = "aiyeou";
        string C = "bkxznhdcwgpvjqtsrlmf";
        for (int i = 0; i < s.size(); ++i) {
            if (!isalpha(s[i])) {
                cout << s[i];
                continue;
            }
            char c = s[i];
            bool U = false;
            if (isupper(c)) {
                c = tolower(c);
                U = true;
            }
            auto it = find(V.begin(), V.end(), c);
            if (it != V.end()) {
                int p = it - V.begin();
                (p += 3) %= V.size();
                c = V[p];
            } else {
                it = find(C.begin(), C.end(), c);
                assert(it != C.end());
                int p = it - C.begin();
                (p += 10) %= C.size();
                c = C[p];
            }
            if (U) c = toupper(c);
            cout << c;
        }
        cout << "\n";
    }
}
