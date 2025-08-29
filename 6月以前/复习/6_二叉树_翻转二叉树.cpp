
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
    // 1.签名和承诺
    // 签名: 根节点
    // 承诺: 把当前根节点的左右子树进行调换

    // 2.基本情况
    // 1) 空节点不修改
    // 2) 左右非空, 即叶子节点不修改 (剪枝和优化)

    // 3.假设左右情况处理好

    // 4.信息流向 自底向上 (后序遍历)

    // 5.剪枝和优化
    void postorder_invertree(TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        if (root->left == nullptr && root->right == nullptr) {
            return;
        }
        postorder_invertree(root->left);
        postorder_invertree(root->right);

        TreeNode *node = root->left;
        root->left = root->right;
        root->right = node;
    }

    TreeNode *invertTree(TreeNode *root) {
        postorder_invertree(root);
        return root;
    }
};