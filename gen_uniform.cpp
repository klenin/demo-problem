#include "testlib.h"

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

  printf("%d %d\n", n, m);
  for (int i = 0; i < m; i++) {
    int len = rnd.next(l1, l2);
    bool is_vowel_first = (rnd.next(2) > 0);
    for (int j = 0; j < len; j++) {
      j +=
    }
  }

  return 0;
}
