#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  const vector<string> bad_words = {"xy", "yz"};
  const vector<set<char>> valid_chars = {{'x', 'z'}, {'y'}, {'x', 'z'}};
  const int n = 3;
  vector<set<string>> d(n+1);
  vector<int> dd(n+1);
  d[0] = {""};
  dd[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (const string &prefix : d[i-1]) {
      for (char ch : valid_chars[i-1]) {
        d[i].insert(prefix + ch);
      }
    }
    dd[i] = dd[i-1] * valid_chars[i-1].size();
    for (const string &w : bad_words) {
      if (w.length() > i) continue;
      bool valid = true;
      for (int j = 0; j < w.length(); j++) {
        int pos = i - w.length() + 1 + j;
        if (valid_chars[pos-1].find(w[j]) == valid_chars[pos-1].end()) {
          valid = false;
        }
      }
      if (!valid) continue;

      for (const string &prefix : d[i - w.length()]) {
        d[i].erase(prefix + w);
      }
      dd[i] -= dd[i - w.length()];
    }
    cout << "i = " << i << ", dd = " << dd[i] << ", |d| = " << d[i].size();
    for (const string &s : d[i]) {
      cout << ", " << s;
    }
    cout << endl;
  }

  return 0;
}
