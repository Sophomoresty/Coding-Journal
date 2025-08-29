#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void preorder_traversal(TreeNode *node, vector<int> &vec_res) {
    if (node == nullptr) {
        return;
    }
    stack<TreeNode *> st;
    st.push(node);

    while (!st.empty()) {
        TreeNode *cur = st.top();
        st.pop();
        vec_res.push_back(cur->val);
        if (cur->right != nullptr) {
            st.push(cur->right);
        }
        if (cur->left != nullptr) {
            st.push(cur->left);
        }
    }
}

void postorder_traversal(TreeNode *node, vector<int> &vec_res) {
    if (node == nullptr) {
        return;
    }
    stack<TreeNode *> st;
    st.push(node);
    while (!st.empty()) {
        TreeNode *cur = st.top();
        st.pop();
        vec_res.push_back(cur->val);
        if (cur->left != nullptr) {
            st.push(cur->left);
        }
        if (cur->right != nullptr) {
            st.push(cur->right);
        }
    }
    reverse(vec_res.begin(), vec_res.end());
}

void inorder_traversal(TreeNode *node, vector<int> &vec_res) {
    if (node == nullptr) {
        return;
    }
    stack<TreeNode *> st;
    TreeNode *cur = node;
    while (cur != nullptr || !st.empty()) {
        // 一路向左, 将路径上的节点压入栈
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        // 弹出根节点,加入节点
        cur = st.top();
        st.pop();
        vec_res.push_back(cur->val);
        // 遍历右子树
        cur = cur->right;
    }
}

int main() {
    TreeNode *root = new TreeNode(3);
    TreeNode *node9 = new TreeNode(9);
    TreeNode *node20 = new TreeNode(20);
    TreeNode *node15 = new TreeNode(15);
    TreeNode *node7 = new TreeNode(7);

    root->left = node9;
    root->right = node20;
    node20->left = node15;
    node20->right = node7;
    //   3
    //  / \
    // 9  20
    //   /  \
    //  15   7

    // 前序遍历
    vector<int> pre_res;
    preorder_traversal(root, pre_res);
    cout << "前序遍历:  ";
    for (auto i : pre_res) {
        cout << i << " ";
    }
    cout << endl;

    // 后序遍历
    vector<int> post_res;
    postorder_traversal(root, post_res);
    cout << "后序遍历:  ";
    for (auto i : post_res) {
        cout << i << " ";
    }
    cout << endl;

    // 中序遍历
    vector<int> in_res;
    inorder_traversal(root, in_res);
    cout << "中序遍历:  ";
    for (auto i : in_res) {
        cout << i << " ";
    }
    cout << endl;

    delete root;
    delete node9;
    delete node20;
    delete node15;
    delete node7;

    return 0;
}