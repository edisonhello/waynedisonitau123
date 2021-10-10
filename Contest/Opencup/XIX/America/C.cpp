#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool same(double a, double b) {
  return abs(a - b) < eps;
}

double ifl[11];
double mdf[111];

int main() {
  int y, c, q; cin >> y >> c >> q;
  vector<vector<double>> mat;
  // [ifl * y, price0 * c, mdf * c]

  for (int i = 1; i < y; ++i) {
    cin >> ifl[i];
    if (ifl[i] > 0) {
      vector<double> line(y + c + c + 1);
      line[i] = 1;
      line.back() = log(ifl[i]);
      mat.push_back(line);
    }
  }

  for (int i = 1; i <= y; ++i) {
    for (int j = 0; j < c; ++j) {
      double prz; cin >> prz;
      if (prz > 0) {
        vector<double> line(y + c + c + 1);
        for (int ii = 1; ii < i; ++ii) line[ii] = 1;
        line[y + j] = 1;
        line[y + c + j] = i - 1;
        line.back() = log(prz);
        mat.push_back(line);
      }
    }
  }

  int ru = mat.size();

  for (int i = 0; i < q; ++i) {
    int yy, ii; cin >> ii >> yy;
    --ii;
    vector<double> line(y + c + c + 1);
    for (int iii = 1; iii < yy; ++iii) line[iii] = -1;
    // cerr << "y + ii = " << y + ii << endl;
    line[y + ii] = -1;
    line[y + c + ii] = -yy + 1;
    // cerr << "line ";
    // for (double dd : line) cerr << dd << ' ';
    // cerr << endl;
    mat.push_back(line);
  }

  int nn = mat.size();
  int mm = y + c + c;

  // for (int i = 0; i < nn; ++i) {
  //   for (int j = 0; j <= mm; ++j) {
  //     cout << mat[i][j] << ' ';
  //   }
  //   cout << endl;
  // }

  vector<int> used(nn);
  for (int j = 0; j < mm; ++j) {
    int pv = -1;
    for (int i = 0; i < ru; ++i) if (!same(mat[i][j], 0) && !used[i]) { pv = i; break; }
    
    if (pv != -1) {
      used[pv] = 1;
      double div = mat[pv][j];
      for (int jj = 0; jj <= mm; ++jj) mat[pv][jj] /= div;

      for (int i = 0; i < nn; ++i) if (i != pv) {
        double subs = mat[i][j];
        for (int jj = 0; jj <= mm; ++jj) {
          mat[i][jj] -= subs * mat[pv][jj];
        }
      }
    }

  // cout << endl;
  // cout << "mat" << endl;
  // for (int i = 0; i < nn; ++i) {
  //   for (int j = 0; j <= mm; ++j) {
  //     cout << mat[i][j] << ' ';
  //   }
  //   cout << endl;
  // }
  }

  // cout << endl;
  // for (int i = 0; i < nn; ++i) {
  //   for (int j = 0; j <= mm; ++j) {
  //     cout << mat[i][j] << ' ';
  //   }
  //   cout << endl;
  // }

  for (int i = ru; i < nn; ++i) {
    bool ok = 1;
    for (int j = 0; j < mm; ++j) if (!same(mat[i][j], 0)) ok = 0;
    if (ok) {
      cout << fixed << setprecision(12);
      cout << exp(mat[i].back()) << '\n';
    } else {
      cout << -1 << '\n';
    }
  }


}
