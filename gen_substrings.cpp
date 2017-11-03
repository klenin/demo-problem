#include "testlib.h"

#include <cassert>
#include <iostream>

using namespace std;

const vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y'};
const vector<char> consonants = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
                                 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w',
                                 'x', 'z'};

int main(int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int l1 = atoi(argv[3]);
  int l2 = atoi(argv[4]);
  int c = atoi(argv[5]);
  int v = atoi(argv[6]);

  assert(c <= consonants.size());
  assert(v <= vowels.size());
  assert(l1 <= l2);
  assert(l2 <= n);

  bool is_vowel_first = (rnd.next(2) > 0);
  string w;
  for (int j = 0; j < n; j++) {
    bool vowel = ((j%2) == 0);
    if (!is_vowel_first) vowel = !vowel;
    int ch = rnd.next(vowel ? v : c);
    w += vowel ? vowels[ch] : consonants[ch];
  }

  cout << n << " " << m << endl;
  for (int i = 0; i < m; i++) {
    int len = rnd.next(l1, l2);
    int start = rnd.next(0, (int)w.size() - len);
    cout << w.substr(start, len) << endl;
  }

  return 0;
}
