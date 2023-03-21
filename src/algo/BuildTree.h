#include <TreeNode.h>

#include <queue>
#include <vector>

using namespace std;

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
    TreeNode *root;
    return root;
}

TreeNode *createTreeLevelOrder(vector<int> &nums)
{
    queue<TreeNode *> q;
    unsigned int j = 0, len = nums.size();
    TreeNode *root = new TreeNode(nums[j++]), *cur;
    q.push(root);
    while (!q.empty() && j < len)
    {
        for (unsigned int i = 0; i < q.size(), j < len; ++i)
        {
            cur = q.front();
            q.pop();
            if (j < len && nums[j] != -1)
            {
                cur->left = new TreeNode(nums[j]);
                q.push(cur->left);
            }
            ++j;
            if (j < len && nums[j] != -1)
            {
                cur->right = new TreeNode(nums[j]);
                q.push(cur->right);
            }
            ++j;
        }
    }
    return root;
}