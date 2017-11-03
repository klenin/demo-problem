#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const bool DEBUG = true;
const int MAXN = 110;
const int MAXM = 110;
const int MAXL = 110;
const int MODULO = 1000000007;

int n, m;

const set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};
set<char> consonants;

// d[i][j][k] -- количество способов составить строку длины i таким образом, что
// плохие слова в ней не встречаются, но при этом самый длинный префикс плохого
// слова, являющийся суффиксом построенной строки -- это w[j][0..k-1]. При этом
// d[i][j][0] = 0 при j > 0, а d[i][0][0] означает количество способов сделать
// так, чтобы ни один префикс плохого слова не является нашим текущим суффиксом.
int d[MAXN + 1][MAXM][MAXL];

// p[i][j][ch] = (x, y) означает, что если к w[i][0..j-1] приписать символ ch,
// то w[x][0..y-1] -- это самый длинный префикс плохого слова, который
// одновременно является суффиксом w[i][0..j-1] + ch. При этом, если такого
// префикса не сущестует, то (x, y) = (0, 0).
pair<int, int> p[MAXM][MAXL + 1][26];

void Update(int i, int j, char ch, int i1, int j1) {
  int ch1 = ch - 'a';
  if (j1 > p[i][j][ch].second) {
    p[i][j][ch].first = i1;
    p[i][j][ch].second = j1;
  }
}

int main() {
  for (char ch = 'a'; ch <= 'z'; ch++) {
    if (vowels.find(ch) == vowels.end()) consonants.insert(ch);
  }

  if (!DEBUG) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  }

  cin >> n >> m;
  vector<string> a(m);
  for (int i = 0; i < m; i++) {
    cin >> a[i];
  }

  vector<string> w;
  for (int i = 0; i < m; i++) {
    bool keep = true;
    for (int j = 0; j < m; j++) {
      if (i == j) continue;
      if (a[i].find(a[j]) != string::npos) {
        keep = false;
        break;
      }
    }
    if (keep) {
      w.push_back(a[i]);
    }
  }
  if (w.empty()) w.push_back("*");
  m = w.size();

  if (DEBUG) {
    cout << "w = ";
    for (int i = 0; i < m; i++) {
      cout << w[i] << ", ";
    }
    cout << endl;
  }

  for (int i = 0; i < m; i++) {
    for (int i1 = 0; i1 < m; i1++) {
      set<int> valid_starts;
      for (int j = 0; j < w[i1].length(); j++) {
        valid_starts[j].insert(j);
      }
      for (int j = 0; j < w[i].length(); j++) {
        set<int> old_valid_starts = valid_starts;
        for (int start: old_valid_starts) {
          if (start + j < w[i1].length() && w[i1][start + j] == w[i][j]) {
            if (j + 1 < w[i].length()) {
              Update(i1, start + j + 1, w[i][j + 1], i, j + 2);
            }
          } else {
            valid_starts.remove(start);
          }
        }
      }
    }
  }

  if (DEBUG) {
    for (i = 0; i < m; i++) {
      for (j = 0; j <
    }
  }

  int ans = 0;
  for (bool is_vowel_first: {true, false}) {
    memset(d, 0, sizeof(d));
    d[0][0][0] = 1;
    for (int i = 0; i < n; i++) {
      bool vowel = ((i%2) == 0);
      if (!is_vowel_first) vowel = !vowel;
      const set<string> &chars = vowel ? vowels : consonants;
      for (int j = 0; j < m; j++) {
        for (int k = 0; k <= w[j].length(); k++) {
          if (d[i][j][k] == 0) continue;
          for (char ch: chars) {
            if (k == w[j].length()-1 && ch == w[j][k]) continue;
            int ch1 = ch - 'a';
            int j1 = p[j][k][ch1].first;
            int k1 = p[j][k][ch1].second;
            d[i+1][j1][k1] = (d[i+1][j1][k1] + d[i][j][k]) % MODULO;
          }
        }
      }
    }
    for (int j = 0; j < m; j++) {
      for (int k = 0; k <= w[j].length(); k++) {
        ans = (ans + d[n][j][k]) % MODULO;
      }
    }
  }

  cout << ans << endl;

  if (!DEBUG) {
    fclose(stdin); fclose(stdout);
  }
  return 0;
}
