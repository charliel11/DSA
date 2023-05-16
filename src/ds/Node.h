#pragma once

#include <cstdint>
#include <vector>

using namespace std;

struct TreeNode {
    int32_t val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int32_t x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int32_t x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
  public:
    int32_t val;
    vector<Node *> neighbors;
    Node() : val(0), neighbors{} {}
    Node(int32_t _val) : val(_val), neighbors{} {}
    Node(int32_t _val, vector<Node *> _neighbors) : val(_val), neighbors(_neighbors) {}
};

Node *createGraph(vector<vector<int32_t>> adjList);

Node *cloneGraph(Node *node);

void deleteGraph(Node *root);

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *swapNodes(ListNode *head, int k);
ListNode *swapPairs(ListNode *head);