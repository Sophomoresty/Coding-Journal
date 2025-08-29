struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {

public:
    // 1.签名和承诺(返回值)
    // 承诺:
    // 根节点坐在子树下
    // 1) 有p/q, 就返回p/q
    // 2) 没有p/q返回空
    // 3) 有pq的最近公共祖先, 则返回p,q的公共祖先

    // 2.基本情况

    // 3.假设子问题已经解决, 如何用子问题的承诺综合解决, 当层的承诺
    // 4.明确信息流向
    // 5.剪枝优化

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        // 基本情况
        if (root == nullptr) {
            return nullptr;
        }
        if (root == p || root == q) {
            return root;
        }

        TreeNode *left_res = lowestCommonAncestor(root->left, p, q);
        TreeNode *right_res = lowestCommonAncestor(root->right, p, q);

        if (left_res != nullptr && right_res != nullptr) {
            return root;
        } else if (left_res == nullptr) {
            return right_res;
        }
        // right_res == nullpet
        else {
            return left_res;
        }
    }
};