#include <iostream>
#include <stack>
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
    void inorder_traversal(TreeNode *root, vector<int> &vec_res) {
        if (root == nullptr) {
            return;
        }
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur != nullptr || !st.empty()) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            // cur==nullptr
            cur = st.top();
            st.pop();
            vec_res.push_back(cur->val);
            cur = cur->right;
        }
    }

    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> vec_res;
        inorder_traversal(root, vec_res);
        return vec_res;
    }
};

int main() {
    // 创建节点
    TreeNode *root = new TreeNode(3);
    TreeNode *node9 = new TreeNode(9);
    TreeNode *node20 = new TreeNode(20);
    TreeNode *node15 = new TreeNode(15);
    TreeNode *node7 = new TreeNode(7);

    // 构建树的结构
    // 3
    // | \
    // 9 20
    //   / \
    //  15  7
    root->left = node9;
    root->right = node20;
    node20->left = node15;
    node20->right = node7;

    // 非递归中序遍历
    Solution sol;
    vector<int> in_result = sol.inorderTraversal(root);
    cout << "非递归中序遍历: ";
    for (auto i : in_result) {
        cout << i << " ";
    }
    cout << endl;

    // 删除节点
    delete root;
    delete node9;
    delete node20;
    delete node15;
    delete node7;
    return 0;
}