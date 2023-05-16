#include <Node.h>
#include <unordered_map>

Node *createGraph(vector<vector<int32_t>> adjList) {
    size_t n = adjList.size();
    if (n == 0)
        return nullptr;
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

/*
https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/
*/
ListNode *swapNodes(ListNode *head, int k) {
    ListNode *fast = head;
    while (--k)
        fast = fast->next;

    ListNode *tmp = fast;

    ListNode *slow = head;
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    std::swap(tmp->val, slow->val);
    return head;
}

/*
https://leetcode.com/problems/swap-nodes-in-pairs/submissions/323607887/
*/
ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    ListNode *res = head->next;
    head->next = head->next->next;
    res->next = head;

    head->next = swapPairs(head->next);
    return res;
}