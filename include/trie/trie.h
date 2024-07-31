#ifndef _TRIE_H
#define _TRIE_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <threads.h>

typedef struct node {
  bool has_value;
  char *key;
  int value;
  struct node **children;
  size_t children_count;
} Node;

typedef struct {
  Node *root;
} Trie;

Node *create_node(const char *key, const int value);

Trie *create_trie();

void insert(Trie *trie, const char *key, const int value);

int search(Trie *trie, const char *key);

void delete_key(Trie *trie, const char *key);

void destroy_trie(Trie *trie);

#endif