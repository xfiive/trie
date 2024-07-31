#include "../../include/tests/trie-tests.h"

void trie_tests() {
  Trie *trie = create_trie();

  puts("Trie created");

  insert(trie, (const char *)"T", 1);
  puts("node 'T' insertred");
  insert(trie, (const char *)"E", 2);
  puts("node 'E' insertred");
  insert(trie, (const char *)"S", 3);
  puts("node 'S' insertred");
  insert(trie, (const char *)"T", 4);
  puts("node 'T' insertred");

  destroy_trie(trie);
  puts("trie destroyed");
}