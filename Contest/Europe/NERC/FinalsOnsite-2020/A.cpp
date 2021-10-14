#include <bits/stdc++.h>
using namespace std;

using Box = vector<string>;
using ParseResult = pair<Box, string_view>;

ParseResult ParseExpr(string_view s);

Box DrawBox(string_view s) {
  Box result(3, string(4 + s.size(), ' '));
  result[0][0] = result[1][0] = result[2][0] = '+';
  result[0].back() = result[1].back() = result[2].back() = '+';
  for (int i = 1; i + 1 < result[0].size(); ++i) {
    result[0][i] = '-';
    result[2][i] = '-';
  }
  result[1] = "+ " + string(s) + " +";
  return result;
}

Box DrawAtom(Box box, char ch) {
  if (ch == '+') {
    Box result(box.size() + 2, string(box[0].size() + 6, ' '));
    result[0] = "   " + box[0] + "   ";
    result[1] = "+->" + box[1] + "->+";
    for (int i = 2; i < box.size(); ++i) {
      result[i] = "|  " + box[i] + "  |";
    }
    result[result.size() - 2][0] = '|';
    result[result.size() - 2].back() = '|';
    result[result.size() - 1][0] = '+';
    result[result.size() - 1][1] = '<';
    result[result.size() - 1].back() = '+';
    for (int i = 2; i + 1 < result[0].size(); ++i) {
      result[result.size() - 1][i] = '-';
    }
    return result;
  } else if (ch == '?') {
    Box result(box.size() + 3, string(box[0].size() + 6, ' '));
    result[2][0] = '|';
    result[2].back() = '|';
    result[1][0] = '+';
    result[1][result[1].size() - 2] = '>';
    result[1].back() = '+';
    for (int i = 1; i + 2  < result[0].size(); ++i) {
      result[1][i] = '-';
    }
    result[3] = "|  " + box[0] + "  |";
    result[4] = "+->" + box[1] + "->+";
    for (int i = 2; i < box.size(); ++i) {
      result[3 + i] = "   " + box[i] + "   ";
    }
    return result;
  } else {
    assert(ch == '*');
    Box result(box.size() + 5, string(box[0].size() + 6, ' '));
    result[2][0] = '|';
    result[2].back() = '|';
    result[1][0] = '+';
    result[1].back() = '+';
    result[1][result[1].size() - 2] = '>';
    for (int i = 1; i + 2 < result[0].size(); ++i) {
      result[1][i] = '-';
    }
    result[3] = "|  " + box[0] + "  |";
    result[4] = "+->" + box[1] + "->+";
    for (int i = 2; i < box.size(); ++i) {
      result[3 + i] = "|  " + box[i] + "  |";
    }
    result[result.size() - 2][0] = '|';
    result[result.size() - 2].back() = '|';
    result[result.size() - 1][0] = '+';
    result[result.size() - 1][1] = '<';
    result[result.size() - 1].back() = '+';
    for (int i = 2; i + 1 < result[0].size(); ++i) {
      result[result.size() - 1][i] = '-';
    }
    return result;
  }
}

ParseResult ParseTerm(string_view s) {
  vector<Box> atoms;
  while (!s.empty()) {
    if (s[0] == '(') {
      auto [box, tail] = ParseExpr(s.substr(1));
      assert(!tail.empty() && tail[0] == ')');
      tail = tail.substr(1);
      atoms.push_back(box);
      s = tail;
    } else if (s[0] >= 'A' && s[0] <= 'Z') {
      atoms.push_back(DrawBox(s.substr(0, 1)));
      s = s.substr(1);
    } else if (s[0] == '+' || s[0] == '?' || s[0] == '*') {
      assert(!atoms.empty());
      Box nbox = DrawAtom(atoms.back(), s[0]);
      atoms.pop_back();
      atoms.push_back(nbox);
      s = s.substr(1);
    } else {
      break;
    }
  }
  if (atoms.size() == 1) {
    return make_pair(atoms[0], s);
  }
  int H = 0, W = 0;
  for (int i = 0; i < atoms.size(); ++i) {
    H = max(H, static_cast<int>(atoms[i].size()));
    W += atoms[i][0].size();
  }

  W += 2 * (atoms.size() - 1);
  Box result(H, string(W, ' '));
  int col = 0;
  for (int i = 0; i < atoms.size(); ++i) {
    for (int j = 0; j < atoms[i].size(); ++j) {
      for (int k = 0; k < atoms[i][j].size(); ++k) {
        result[j][k + col] = atoms[i][j][k];
      }
      if (i + 1 < atoms.size()) {
        result[1][col + atoms[i][j].size()] = '-';
        result[1][col + atoms[i][j].size() + 1] = '>';
      }
    }
    col += atoms[i][0].size();
    if (i + 1 < atoms.size()) col += 2;
  }
  return make_pair(result, s);
}

ParseResult ParseExpr(string_view s) {
  vector<Box> terms;
  string_view t = "";
  while (!s.empty()) {
    auto [term, tail] = ParseTerm(s);
    terms.push_back(term);
    if (!tail.empty()) {
      if (tail[0] != '|') {
        t = tail;
        break;
      }
      tail = tail.substr(1);
    }
    s = tail;
  }
  if (terms.size() == 1) {
    return make_pair(terms[0], t);
  }
  int W = 0;
  for (auto& box : terms) {
    W = max(W, static_cast<int>(box[0].size()));
  }
  for (auto& box : terms) {
    int G = box[0].size();
    for (auto& str : box) {
      str = "   " + str;
    }
    box[1][0] = '+';
    box[1][1] = '-';
    box[1][2] = '>';
    for (int i = 0; i < box.size(); ++i) {
      char ch = i == 1 ? '-' : ' ';
      int c = 0;
      while (G + c < W) box[i] += ch, c++;
      if (i == 1) {
        box[i] += "->+";
      } else {
        box[i] += "   ";
      }
    }
  }
  int H = 0;
  for (auto& box : terms) {
    H += box.size();
  }
  H += terms.size() - 1;
  Box result(H, string(W + 6, ' '));
  for (int i = 0, j = 0; i < terms.size(); ++i) {
    for (int k = 0; k < terms[i].size(); ++k) {
      assert(terms[i][k].size() == result[j + k].size());
      result[j + k] = terms[i][k];
    }
    if (i + 1 < terms.size()) {
      for (int k = 2; k < terms[i].size(); ++k) {
        result[j + k][0] = '|';
        result[j + k].back() = '|';
      }
      result[j + terms[i].size()][0] = '|';
      result[j + terms[i].size()].back() = '|';
    }
    if (i > 0) {
      result[j][0] = '|';
      result[j].back() = '|';
    }
    j += terms[i].size() + 1;
  }
  return make_pair(result, t);
}

ParseResult ParseInput(string_view s) {
  auto [expr, tail] = ParseExpr(s);
  assert(tail.empty());
  int N = expr.size(), M = expr[0].size();
  for (int i = 0; i < expr.size(); ++i) {
    expr[i] = "   " + expr[i] + "   ";
  }
  expr[1][0] = 'S';
  expr[1][1] = '-';
  expr[1][2] = '>';
  expr[1][M + 3] = '-';
  expr[1][M + 4] = '>';
  expr[1][M + 5] = 'F';
  return make_pair(expr, tail);
}

int main() {
  string s;
  cin >> s;
  auto [ans, tail] = ParseInput(s);
  assert(tail.empty());
  for (const string& row : ans) cout << row << "\n";
  return 0;
}
