#include "../../include/trie/trie.h"

Node *create_node(const char *key, const int value) {
  if (key == NULL)
    return NULL;

  Node *node = (Node *)calloc(1, sizeof(struct node));

  if (!node) {
    perror("Failed to allocate node memory");
    return NULL;
  }

  node->children = NULL;
  node->children_count = 0;
  node->has_value = false;
  node->key = strdup(key);
  node->value = value;

  return node;
}

Trie *create_trie() {
  Trie *trie = (Trie *)calloc(1, sizeof(Trie));

  if (!trie) {
    perror("Failed to allocate trie memory");
    return NULL;
  }

  trie->root = create_node("", 0);

  return trie;
}

void insert(Trie *trie, const char *key, const int value) {
  Node *current = trie->root;
  while (*key) {
    bool is_found = false;

    for (size_t i = 0; i < current->children_count; i++) {
      if (current->children[i]->key[0] == *key) {
        current = current->children[i];
        is_found = true;
        break;
      }
    }

    if (!is_found) {
      Node *new_node = create_node(key, INT_MAX);
      current->children = (Node **)realloc(
          current->children, sizeof(Node *) * (current->children_count + 1));
      current->children[current->children_count++] = new_node;
      current = new_node;
    }

    key++;
  }

  current->has_value = true;
  current->value = value;
}

int search(Trie *trie, const char *key) {
  Node *current = trie->root;
  while (*key) {
    bool is_found = false;

    for (size_t i = 0; i < current->children_count; i++) {
      if (current->children[i]->key[0] == *key) {
        current = current->children[i];
        is_found = true;
        break;
      }
    }

    if (!is_found) {
      return INT_MIN;
    }

    key++;
  }
  return current->has_value ? current->value : INT_MIN;
}

bool delete_key_recursive(Node *node, const char *key) {
  if (*key) {
    Node *child = NULL;
    size_t child_index = 0;
    bool is_found = false;

    for (size_t i = 0; i < node->children_count; i++) {
      if (node->children[i]->key[0] == *key) {
        child = node->children[i];
        child_index = i;
        is_found = true;
        break;
      }
    }

    if (is_found && delete_key_recursive(child, key + 1)) {
      free(node->children[child_index]->key);
      free(node->children[child_index]);

      for (size_t i = 0; i < node->children_count - 1; i++) {
        node->children[i] = node->children[i + 1];
      }

      node->children_count -= 1;
      node->children =
          realloc(node->children, sizeof(Node *) * node->children_count);

      return node->children_count == 0 && !node->has_value;
    }
  } else {
    node->has_value = false;
    return node->children_count == 0;
  }

  return false;
}

void delete_key(Trie *trie, const char *key) {
  delete_key_recursive(trie->root, key);
}

void delete_node(Node *node) {
  if (node == NULL) {
    return;
  }

  for (size_t i = 0; i < node->children_count; i++) {
    delete_node(node->children[i]);
  }

  free(node->key);
  free(node->children);
  free(node);
}

void destroy_trie(Trie *trie) {
  if (trie == NULL) {
    return;
  }

  delete_node(trie->root);

  free(trie);
}