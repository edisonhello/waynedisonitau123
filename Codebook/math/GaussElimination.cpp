double Gauss(vector<vector<double>> &d) {
  int n = d.size(), m = d[0].size();
  double det = 1;
  for (int i = 0; i < m; ++i) {
    int p = -1;
    for (int j = i; j < n; ++j) {
      if (fabs(d[j][i]) < kEps) continue;
      if (p == -1 || fabs(d[j][i]) > fabs(d[p][i])) p = j;
    } 
    if (p == -1) continue;
    if (p != i) det *= -1;
    for (int j = 0; j < m; ++j) swap(d[p][j], d[i][j]);
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      double z = d[j][i] / d[i][i];
      for (int k = 0; k < m; ++k) d[j][k] -= z * d[i][k];
    }
  }
  for (int i = 0; i < n; ++i) det *= d[i][i];
  return det;
} 

