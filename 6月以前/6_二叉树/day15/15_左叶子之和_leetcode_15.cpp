// #### 方案一：前序递归（自顶向下），传递“我是左孩子吗？”的状态

// 这种方案需要一个辅助函数和一个全局变量，类似于我们之前求深度的方式。

// * **`sumOfLeftLeaves(TreeNode* root)` 函数的作用：** 遍历树，累加所有左叶子的值到全局变量 `total_sum`。
// * **辅助函数 `dfs(TreeNode* node, bool is_left_child)`：**
//     * `node`：当前节点。
//     * `is_left_child`：布尔值，表示 `node` 是不是其父节点的左孩子。这个信息由父节点传递下来。
// * **累加时机：** 当 `node` 是一个叶子节点，并且 `is_left_child` 为 `true` 时，才将 `node->val` 加到 `total_sum`。

// ```cpp
// #include <iostream> // For testing
// // TreeNode 定义 (假设已存在)
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

// class Solution {
// public:
//     int total_sum_of_left_leaves; // 全局变量，累加所有左叶子之和

//     /**
//      * @brief 辅助函数：使用前序递归遍历树，并根据节点是否是左孩子进行累加。
//      *
//      * @param node 当前访问的节点。
//      * @param is_left_child 布尔值，指示当前 node 是否为其父节点的左孩子。
//      */
//     void dfs_preorder(TreeNode* node, bool is_left_child) {
//         // 1. 终止条件 (Base Case):
//         // 如果当前节点是 nullptr，直接返回。
//         if (node == nullptr) {
//             return;
//         }

//         // 2. "访问"当前节点 (前序处理):
//         // 如果当前节点是叶子节点，并且它是一个左孩子，则将其值加入总和。
//         if (node->left == nullptr && node->right == nullptr && is_left_child) {
//             total_sum_of_left_leaves += node->val;
//         }

//         // 3. 递归到左右子树:
//         // 向左子树递归时，传递 true (表示左孩子)。
//         dfs_preorder(node->left, true);
//         // 向右子树递归时，传递 false (表示右孩子)。
//         dfs_preorder(node->right, false);
//     }

//     /**
//      * @brief 计算所有左叶子之和的主函数。
//      *
//      * @param root 二叉树的根节点。
//      * @return int 所有左叶子之和。
//      */
//     int sumOfLeftLeaves(TreeNode* root) {
//         total_sum_of_left_leaves = 0; // 每次调用清零

//         // 处理空树的情况
//         if (root == nullptr) {
//             return 0;
//         }

//         // 从根节点开始 DFS。根节点本身不是任何人的“左孩子”，所以传入 false。
//         dfs_preorder(root, false);

//         return total_sum_of_left_leaves;
//     }
// };
// ```

// #### 方案二：后序递归（自底向上），在父节点进行判断和累加（更巧妙）

// 这种方案利用后序递归的返回值。函数返回的是**其子树中左叶子的和**。

// * **`sumOfLeftLeaves(TreeNode* root)` 函数的作用：** 返回以 `root` 为根的子树中**所有左叶子的和**。
// * **累加时机：** 当一个节点 `root` 接收到其左孩子 `root->left` 的返回值后，它自己判断 `root->left` 是否是左叶子。
//     * 如果 `root->left` 存在，且 `root->left` 是一个叶子节点，那么 `root->left->val` 就是一个左叶子，需要加到总和里。
//     * 然后，加上 `root->left` 为根的子树中**其余**左叶子的和（递归调用 `sumOfLeftLeaves(root->left)` 的返回值），以及 `root->right` 为根的子树中所有左叶子的和。

// ```cpp
// #include <iostream> // For testing
// // TreeNode 定义 (假设已存在)
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };

// class Solution {
// public:
//     /**
//      * @brief 使用后序递归计算所有左叶子之和。
//      * 函数返回以 root 为根的子树中所有左叶子的和。
//      *
//      * @param root 当前子树的根节点。
//      * @return int 当前子树中所有左叶子之和。
//      */
//     int sumOfLeftLeaves(TreeNode* root) {
//         // 1. 终止条件 (Base Case):
//         // 如果当前节点是 nullptr，它没有左叶子，返回 0。
//         if (root == nullptr) {
//             return 0;
//         }

//         // 2. 递归获取左右子树中左叶子之和 (后序遍历，左右):
//         // sumOfLeftLeaves(root->left) 将返回以 root->left 为根的子树中所有左叶子的和。
//         int left_sum = sumOfLeftLeaves(root->left);
//         // sumOfLeftLeaves(root->right) 将返回以 root->right 为根的子树中所有左叶子的和。
//         int right_sum = sumOfLeftLeaves(root->right);

//         // 3. 处理当前节点 (后序遍历，根):
//         // 关键点：在这里判断 root 的左孩子是否是一个左叶子。
//         int current_node_contribution = 0;
//         // 如果 root 有左孩子，并且这个左孩子是一个叶子节点，
//         // 那么这个左孩子就是一个“左叶子”，它自己的值需要被加上。
//         if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
//             current_node_contribution = root->left->val;
//         }

//         // 4. 返回总和：
//         // 当前子树所有左叶子之和 = 左子树中左叶子之和 + 右子树中左叶子之和 + 当前节点左孩子作为左叶子的贡献。
//         return left_sum + right_sum + current_node_contribution;
//     }
// };
// ```

// ### 总结

// 你之前的困惑在于，如何将“我是左孩子”这个信息传递给递归，并正确累加。

// * **方案一（前序）：** 通过在函数参数中传递 `is_left_child` 布尔值，自顶向下地告诉每个节点它的身份。在叶子节点处进行判断和累加。
// * **方案二（后序）：** 更巧妙。每个父节点自行判断其左孩子是否是左叶子，然后将这个值加上其左右子树递归返回的和。这样，`sumOfLeftLeaves(node)` 返回的就是 `node` 子树中所有左叶子的总和。这种方法更符合你所说的“我相信它会返回正确结果”的后序递归模式。

// 两种方案都能正确解决问题。方案二（后序递归）通常被认为是更简洁和优雅的解决方案，因为它避免了全局变量。
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
    // 返回左叶子之和
    int sumOfLeftLeaves(TreeNode *root) {
        // 1.退出条件
        if (root == nullptr) {
            return 0;
        }
        // 后序遍历
        // 左
        int left_sum = sumOfLeftLeaves(root->left);
        // 右
        int right_sum = sumOfLeftLeaves(root->right);

        // 根 处理当前节点
        // 默认贡献为0
        int cur_contribution = 0;
        // 有左叶子
        if (root->left != nullptr && root->left->left == nullptr &&
            root->left->right == nullptr) {
            cur_contribution = root->left->val;
        }
        return left_sum + right_sum + cur_contribution;
    }
};