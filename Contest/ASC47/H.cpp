#pragma GCC optimize("O3")
#pragma GCC target("avx")

#include <bits/stdc++.h>
using namespace std;

int n;

#define mat vector<vector<long long>>

// struct number {
//     vector<int> d;
//     template <typename T>
//     number(T x) {
//         while (x > 0) {
//             d.push_back(x % 10);
//             x /= 10;
//         }
//     }
//     number(vector<int> d): d(d) {}
//     number operator+(const number &rhs) const {
//         vector<int> v;
//         for (int i = 0; i < (int)min(d.size(), rhs.size()); ++i) {
//             v.push_back(
//         }
//     }
// }

mat get_mat() {
    vector<vector<long long>> v(n, vector<long long>(n, 0));
    return v;
}
mat get_Imat() {
    vector<vector<long long>> v(n, vector<long long>(n, 0));
    for(int i=0;i<n;++i) v[i][i] = 1;
    return v;
}

mat operator*(const mat &a,const mat &b){
    mat res=get_mat();
    for (int i=0;i<n;++i) for(int j=0;j<n;++j) for(int k=0;k<n;++k) res[i][j] += a[i][k]*b[k][j];
    return res;
}

void print_mat(const mat m) {
    static bool first=1;
    if(!first)cout<<'\n'; first=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<m[i][j]<<" ";
        }
        cout << '\n';
    }
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("higher.in", "r", stdin);
    freopen("higher.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    map<mat,array<mat,4>> mp;
    while (cin>>n,n) {
        mat L=get_Imat(), A=get_mat(), R=get_Imat(), iL=get_Imat(), iR=get_Imat();
        for (int i=0;i<n;++i) for(int j=0;j<n;++j) cin>>A[i][j];
        auto it=mp.find(A);
        if (it != mp.end()) {
            print_mat(it->second[0]);
            print_mat(it->second[1]);
            print_mat(it->second[2]);
            print_mat(it->second[3]);
            continue;
        }
        mat OA=A;
        auto row_op = [&](int from, int to, long long tms) -> void {
            mat op=get_Imat();
            op[to][from] = tms;
            L=op*L;
            A=op*A;
            op[to][from] = -tms;
            iL=iL*op;
        };
        auto col_op = [&](int from, int to, long long tms) -> void {
            mat op=get_Imat();
            op[from][to] = tms;
            R=R*op;
            A=A*op;
            op[from][to] = -tms;
            iR=op*iR;
        };
        auto swap_row = [&](int u, int v) -> void {
            mat op=get_Imat();
            op[u][u] = op[v][v] = 0;
            op[u][v] = op[v][u] = 1;
            L=op*L;
            A=op*A;
            iL=iL*op;
        };
        auto swap_col = [&](int u, int v) -> void {
            mat op=get_Imat();
            op[u][u] = op[v][v] = 0;
            op[u][v] = op[v][u] = 1;
            R=R*op;
            A=A*op;
            iR=op*iR;
        };
        for (int z=0;z<n-1;++z){ // delete first z row and column
            // target: A[z][z] is factor of all A[z:n-1][z:n-1]
            long long mn=LLONG_MAX;
            if (A[z][z]) mn=min(abs(A[z][z]), mn);
            for (int i=z;i<n;++i) for (int j=z;j<n;++j) {
                if (A[i][j]) mn = min(abs(A[i][j]), mn);
            }
            if (abs(A[z][z]) != mn) {
                for (int i=z;i<n;++i) for (int j=z;j<n;++j) {
                    if (abs(A[i][j]) == mn) swap_row(i, z), swap_col(j, z);
                }
            }
            if (A[z][z] == 0) break;
            auto clear_row_and_column = [&]() -> void {
                while ( [&]() -> bool { // right and down have element?
                    for (int y=z+1;y<n;++y) if (A[z][y] || A[y][z]) return true;
                    return false;
                }() ) {
                    for (int y=z+1;y<n;++y) { // check down element
                        if (A[y][z] == 0) continue;
                        while (A[y][z] % A[z][z]) {
                            if (abs(A[y][z]) > abs(A[z][z])) {
                                long long tms = A[y][z] / A[z][z];
                                row_op(z, y, -tms);
                            } else {
                                long long tms = A[z][z] / A[y][z];
                                if (A[y][z] * tms == A[z][z]) --tms;
                                row_op(y, z, -tms);
                            }
                        }
                        row_op(z, y, -A[y][z] / A[z][z]);
                    }
                    for (int y=z+1;y<n;++y) { // check right element
                        if (A[z][y] == 0) continue;
                        while (A[z][y] % A[z][z]) {
                            if (abs(A[z][y]) > abs(A[z][z])) {
                                long long tms = A[z][y] / A[z][z];
                                col_op(z, y, -tms);
                            } else {
                                long long tms = A[z][z] / A[z][y];
                                if (A[z][y] * tms == A[z][z]) --tms;
                                col_op(y, z, -tms);
                            }
                        }
                        col_op(z, y, -A[z][y] / A[z][z]);
                    }
                }
            };
            clear_row_and_column();
            bool save = false;
            while (1) {
                bool change = false;
                for (int i=z+1;i<n;++i) for (int j=z+1;j<n;++j) {
                    if (A[i][j] % A[z][z]) {
                        row_op(i, z, 1);
                        clear_row_and_column();
                        change = true;
                    }
                }
                if (!change) break;
            }
        }
        print_mat(L);
        print_mat(iL);
        print_mat(R);
        print_mat(iR);
        mp[OA] = {L, iL, R, iR};
#ifndef ONLINE_JUDGE
        // cout << "A = " << endl; print_mat(A);
        // cout << "L * iL = " << endl; print_mat(L * iL);
        // cout << "R * iR = " << endl; print_mat(R * iR);
#endif
    }
}
