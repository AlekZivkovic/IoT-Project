#ifndef ATDRIVER_INCLUDE_TRIE_TRIE_H_
#define ATDRIVER_INCLUDE_TRIE_TRIE_H_

#include <stdint.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

/* AT Commands Identifiers */
#define OK          0x0
#define RECEIVE     0x1
#define NONE        0x2


typedef struct TrieNode_
{
    struct TrieNode_ *children[ALPHABET_SIZE];
    uint8_t command;
} TrieNode;

TrieNode* xTrieNodeCreateNode(void);
void vTrieNodeInsert(TrieNode *root, const char *key, uint8_t command);

#endif
