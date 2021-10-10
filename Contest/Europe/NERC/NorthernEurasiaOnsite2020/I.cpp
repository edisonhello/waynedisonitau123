#include <bits/stdc++.h>
using namespace std;

const int maxc = 30;
const double base = 1.5;

#ifdef SELF
#define round jiosfjiosefjioesfjiofse
int _n, _m;
int mistake_cnt[1005];
int this_answer;
int me_mistake;
int round;
#endif

void GetInit(int &n, int &m) {
#ifdef SELF
  _n = n = 2;
  _m = m = 10000;
#else
  cin >> n >> m;
#endif
}

vector<int> GetGuess() {
#ifdef SELF
  ++round;
  this_answer = round & 1;
  vector<int> v = {0, 1};
  // this_answer = rand() & 1;
  // for (int i = 0; i < _n; ++i) v.push_back(rand() & 1);
  for (int i = 0; i < _n; ++i) if (v[i] != this_answer) ++mistake_cnt[i];
  return v;
#else
  string s; cin >> s;
  vector<int> v(s.size());
  for (int i = 0; i < s.size(); ++i) v[i] = s[i] == '1';
  return v;
#endif
}

int Output(int x) {
#ifdef SELF
  if (x != this_answer) ++me_mistake;
  return this_answer;
#else
  cout << x << endl;
  int answer; cin >> answer;
  return answer;
#endif
}

double _pw[50];

int main() {
  int n, m; 
  GetInit(n, m);

  _pw[0] = 1;
  for (int i = 1; i < 50; ++i) _pw[i] = _pw[i - 1] * base;

  vector<int> mistake(n, 0);
  int my_fault = 0;

  for (int i = 0; i < m; ++i) {
    vector<int> v = GetGuess();
    vector<double> w(2, 0);

    int min_mistake = *min_element(mistake.begin(), mistake.end());

    for (int i = 0; i < n; ++i) {
      double weight = mistake[i] > min_mistake + maxc ? 1 : _pw[30 - (mistake[i] - min_mistake)];
      w[v[i]] += weight;
    }

    double tot = w[0] + w[1];
    double zero = w[0] / tot;
    double rnd = (double)rand() / RAND_MAX;
    int ans;
    if (rnd <= zero) ans = 0;
    else ans = 1;

    int real_ans = Output(ans);
    if (ans != real_ans) ++my_fault;

    for (int i = 0; i < n; ++i) {
      if (v[i] != real_ans) ++mistake[i];
    }
  }

  cerr << "fault " << my_fault << endl;

#ifdef SELF
  int min_mistake = *min_element(mistake_cnt, mistake_cnt + _n);
  cout << "min_mistake = " << min_mistake << endl;
  cout << "me_mistake = " << me_mistake << endl;
  int limit = min_mistake * 1.3 + 100;
  cout << "limit = " << limit << endl;
  exit(me_mistake <= limit);
#endif
}
