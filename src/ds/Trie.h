#ifndef __TRIE_H__
#define __TRIE_H__

#include <string>

using namespace std;

// https://leetcode.com/problems/implement-trie-prefix-tree/

class Trie
{
    struct TrieNode
    {
        /* data */
        bool isEnd{false};
        TrieNode *next[26]{nullptr};
    };
    TrieNode *_root{nullptr};
    bool findExist(TrieNode *cur)
    {
        if (cur == nullptr)
            return false;
        if (cur->isEnd)
            return true;

        for (auto &next : cur->next)
        {
            if (findExist(next))
                return true;
        }
        return false;
    }
    void free(TrieNode* cur) {
        if (cur == nullptr)
            return;

        for (auto &next : cur->next)
            free(next);
        delete cur;
    }
public:
    Trie()
    {
        _root = new TrieNode();
    }
    ~Trie()
    {
        // delete TrieNode
        free(_root);
    }
    void insert(std::string word)
    {
        TrieNode *cur = _root;
        for (char &c : word)
        {
            if (cur->next[c - 'a'] == nullptr)
                cur->next[c - 'a'] = new TrieNode();
            cur = cur->next[c - 'a'];
        }
        cur->isEnd = true;
    }

    bool search(string word)
    {
        TrieNode *cur = _root;
        for (char &c : word)
        {
            if (cur->next[c - 'a'] == nullptr)
                return false;
            cur = cur->next[c - 'a'];
        }
        return cur->isEnd;
    }

    bool startsWith(string prefix)
    {
        TrieNode *cur = _root;
        for (char &c : prefix)
        {
            if (cur->next[c - 'a'] == nullptr)
                return false;
            cur = cur->next[c - 'a'];
        }
        return findExist(cur);
    }
};

#endif