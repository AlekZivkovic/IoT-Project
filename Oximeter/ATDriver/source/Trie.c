#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <ATDriver/include/Trie.h>


TrieNode* xTrieNodeCreateNode(void)
{
    TrieNode *node = malloc(sizeof(struct TrieNode_));
    if (node)
    {
        node->command = NONE;
        uint8_t idx = 0;
        while (idx < ALPHABET_SIZE)
        {
            node->children[idx] = NULL;
            idx++;
        }
    }
    return node;
}

void vTrieNodeInsert(TrieNode *root, const char *key, uint8_t command)
{
    if (root == NULL)
        return;

    TrieNode *crawler = root;
    uint8_t level = 0;
    for (; level < strlen(key); level++)
    {
        uint8_t index = key[level] - 'A';
        if (!crawler->children[index])
            crawler->children[index] = xTrieNodeCreateNode();
        crawler = crawler->children[index];
    }
    crawler->command = command;
}

