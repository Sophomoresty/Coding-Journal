#include <stdio.h>
#include <vector>
using namespace std;
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

    // 参数 前序数组 和 后序数组
    // 返回 对应的树的根节点
    // 1.后序数组为0, 返回空节点
    // 2.后序数组最后一个元素为根节点元素, 创建根节点
    // 3.用根节点元素寻找中序数组的位置, 作为切割点
    // 4.切割中序数组
    // 5.切割后序数组
    // 6.递归处理做区间和右区间
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        // 发现一个问题, 切割数组会创建非常多的空间
        // 1.终止条件 中序数组和后序数组的合法性题目已经保证
        if (postorder.empty()) {
            return nullptr;
            // 2.找到根节点, 创建根节点
        }

        TreeNode *node = new TreeNode(postorder[postorder.size() - 1]);
        // 3.确定中序数组的分割点
        int index;
        for (index = 0; index < inorder.size(); index++) {
            if (inorder[index] == postorder[postorder.size() - 1]) {
                break;
            }
        }
        // 4.切割中序数组 遵循左闭右开  左中右
        vector<int> inorder_left(inorder.begin(), inorder.begin() + index);

        vector<int> inorder_right(inorder.begin() + index + 1, inorder.end());

        // 5.切割后序数组 遵循左闭右开, 用中序数组的长度  左右中
        
        vector<int> postorder_left(postorder.begin(),
                                   postorder.begin() + inorder_left.size());

        vector<int> postorder_right(postorder.begin() + inorder_left.size(),
                                    postorder.begin() + inorder_left.size() +
                                        inorder_right.size());

        // 6.单层递归, 递归处理的时候以考虑某一层来写
        node->left = buildTree(inorder_left, postorder_left);

        node->right = buildTree(inorder_right, postorder_right);
        return node;
    }
};

void inorder_traversal(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    inorder_traversal(root->left);
    printf("%d ", root->val);
    inorder_traversal(root->right);
}

int main() {
    Solution sol;
    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    TreeNode *root = sol.buildTree(inorder, postorder);
    printf("中序遍历结果\n");
    inorder_traversal(root);
    printf("\n中序遍历结果\n");
    return 0;
}