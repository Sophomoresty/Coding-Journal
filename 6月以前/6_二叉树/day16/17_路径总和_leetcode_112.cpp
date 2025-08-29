
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode *root, int targetSum) {
        // 终止条件1
        if (root == nullptr) {
            return false;
        }
        // 终止条件2
        if (root->left == nullptr && root->right == nullptr) {
            return root->val == targetSum;
        }

        return hasPathSum(root->left, targetSum - root->val) ||
               hasPathSum(root->right, targetSum - root->val);
    }
};