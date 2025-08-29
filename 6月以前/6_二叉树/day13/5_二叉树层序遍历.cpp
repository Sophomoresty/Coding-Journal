#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void levelorder_traversal(TreeNode *node, vector<int> &vec_res) {
    if (node == nullptr) {
        return;
    }
    queue<TreeNode *> que;
    que.push(node);

    while (!que.empty()) {
        TreeNode *cur = que.front();
        que.pop();
        vec_res.push_back(cur->val);
        if (cur->left != nullptr) {
            que.push(cur->left);
        }
        if (cur->right != nullptr) {
            que.push(cur->right);
        }
    }
}

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

    // 层次遍历

    vector<int> level_res;
    levelorder_traversal(root, level_res);
    cout << "层次遍历: ";
    for (auto i : level_res) {
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
