#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    // 结构体的构造函数
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 前序递归遍历
// 递归函数中定义变量, 是有问题的, 保存结果的数组应该作为参数传入
// 1. 参数: 根节点指针(不需要修改), 数组(需要修改) 返回值: 空
// 2. 终止条件: 当前节点为空
// 3. 单层递归逻辑: 根左右

// 如果参数是大型对象（如 std::vector<int>），用 const T& 可以避免复制。
// 如果参数是指针，直接传递指针即可，不需要引用。
void preorder_traversal(const TreeNode *tree, vector<int> &vec_res) {
    // 终止条件
    if (tree == nullptr) {
        return;
    }
    vec_res.push_back(tree->val);
    preorder_traversal(tree->left, vec_res);
    preorder_traversal(tree->right, vec_res);
};
void inorder_traversal(const TreeNode *tree, vector<int> &vec_res) {
    if (tree == nullptr) {
        return;
    }
    inorder_traversal(tree->left, vec_res);
    vec_res.push_back(tree->val);
    inorder_traversal(tree->right, vec_res);
}

void postorder_traversal(const TreeNode *tree, vector<int> &vec_res) {
    if (tree == nullptr) {
        return;
    }
    postorder_traversal(tree->left, vec_res);
    postorder_traversal(tree->right, vec_res);
    vec_res.push_back(tree->val);
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

    // 调用前序遍历
    vector<int> pre_result;
    preorder_traversal(root, pre_result);

    // 打印结果
    cout << "前序遍历结果: ";
    for (int val : pre_result) {
        cout << val << " ";
    }
    cout << endl; // 预期输出: 3 9 20 15 7

    // 调用中序遍历
    vector<int> in_result;
    inorder_traversal(root, in_result);

    cout << "中序遍历结果: ";
    for (int val : in_result) {
        cout << val << " ";
    }
    cout << endl;
    // 调用后序遍历
    vector<int> post_result;

    postorder_traversal(root, post_result);

    cout << "后序遍历结果: ";
    for (int val : post_result) {
        cout << val << " ";
    }
    cout << endl;

    // !!! 重要：释放内存，防止内存泄漏
    // 对于手动创建的树，需要手动递归删除节点
    // 这是一个简单示例，实际项目中通常用智能指针或统一的析构函数来管理
    delete root;
    delete node9;
    delete node20;
    delete node15;
    delete node7;

    return 0;
}