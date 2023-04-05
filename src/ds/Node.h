#pragma once

#include <vector>
#include <unordered_map>
// #include <Utility.h>

using namespace std;

struct TreeNode {
    int32_t val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() :
        val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int32_t x) :
        val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int32_t x, TreeNode *left, TreeNode *right) :
        val(x), left(left), right(right) {
    }
};

class Node {
public:
    int32_t val;
    vector<Node *> neighbors;
    Node() :
        val(0), neighbors{} {
    }
    Node(int32_t _val) :
        val(_val), neighbors{} {
    }
    Node(int32_t _val, vector<Node *> _neighbors) :
        val(_val), neighbors(_neighbors) {
    }
};

Node *createGraph(vector<vector<int32_t>> adjList) {
    size_t n = adjList.size();
    if (n == 0) return nullptr;
    unordered_map<int, Node *> hash;
    Node *cur;
    for (size_t i = 1; i <= n; ++i) {
        if (hash.count(i) == 0) {
            hash[i] = cur = new Node(i);
        } else {
            cur = hash[i];
        }
        for (auto &next : adjList[i - 1]) {
            if (hash.count(next) == 0) {
                hash[next] = new Node(next);
                cur->neighbors.emplace_back(hash[next]);
            } else {
                cur->neighbors.emplace_back(hash[next]);
            }
        }
    }
    return hash[1];
}

Node *cloneGraph(Node *node) {
    if (node == nullptr)
        return nullptr;
    unordered_map<int, Node *> hash;
    Node *res;
    auto dfs = [&](const auto &dfs, Node *&target, Node *source) {
        if (source == nullptr)
            return;

        if (hash.count(source->val) == 0) {
            hash[source->val] = new Node(source->val);
            target = hash[source->val];
            size_t n = source->neighbors.size();
            target->neighbors.resize(n);
            for (size_t i = 0; i < n; ++i)
                dfs(dfs, target->neighbors[i], source->neighbors[i]);
        } else
            target = hash[source->val];
    };
    dfs(dfs, res, node);
    return res;
}

void deleteGraph(Node *root) {
    if (root == nullptr)
        return;
    unordered_map<int, Node *> hash;
    auto dfs = [&](const auto &dfs, Node *node) {
        if (node == nullptr)
            return;
        if (hash[node->val] == 0) {
            hash[node->val] = node;
            for (auto &next : node->neighbors) {
                dfs(dfs, next);
            }
        }
    };
    dfs(dfs, root);

    for (auto &it : hash)
        delete it.second;
}

// class Node
// {
// public:
//     int val;
//     vector<Node *> children;

//     Node() {}

//     Node(int _val)
//     {
//         val = _val;
//     }

//     Node(int _val, vector<Node *> _children)
//     {
//         val = _val;
//         children = _children;
//     }
// };

// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };
