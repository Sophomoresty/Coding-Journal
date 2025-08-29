/*
---

我们刚刚深入探讨了 **“二叉树的所有路径 (Binary Tree Paths)”** 这个经典问题，以及如何用**前序递归配合回溯**来优雅地解决它。

### 核心任务与方法

本题的核心任务是找出二叉树中所有从根节点到叶子节点的路径，并将它们以字符串的形式（例如 `1->2->5`）存储起来。我们采用的是 **深度优先搜索 (DFS)** 的思想，具体来说是**前序递归**。

### 递归设计的三要素回顾

在解决这个问题时，我们再次运用了递归的“三要素”原则，并对其中的关键点进行了完善：

1.  **函数作用与参数 (`traversal(TreeNode* node, std::vector<int>& current_path_vals)`)**
    * **函数作用：** 这个辅助函数的目标是，在当前 `node` 及其子树中，找到所有能到达叶子节点的路径，并将它们加入到全局的结果集 `res` 中。
    * **参数 `node`：** 当前正在访问的树节点。
    * **参数 `current_path_vals`：** 这是一个关键的 **引用传递 (`&`)** 参数，它用于在不同递归层级间**共享和累积**从根节点到当前 `node` 的路径上的所有节点值。正是因为它是引用，我们才能在递归调用中修改同一个 `vector` 实例，避免了昂贵的**按值复制**开销。

2.  **终止条件 (Base Cases)**
    * **空节点：** `if (node == nullptr) { return; }`。这是最基本的递归出口，当路径走到尽头（空指针）时，停止探索。
    * **叶子节点：** `if (node->left == nullptr && node->right == nullptr)`。这是找到一条完整路径的标志。当抵达叶子节点时，`current_path_vals` 中存储的就是从根到当前叶子的完整路径。此时，我们将其转化为字符串，并添加到最终结果集 `res` 中。

3.  **递归关系 (Recursive Step) 与回溯**
    本题最核心的模式是 **“添加 - 递归 - 回溯”**，它完美地体现了前序遍历和状态管理：

    * **添加 (Pre-order / “根”操作)：** `current_path_vals.push_back(node->val);`
        * 在每次进入一个新节点 `node` 的递归函数时，我们都将其值加入到 `current_path_vals` 中。这代表了我们“向前”走了一步，将当前节点纳入路径。

    * **递归 (DFS / “左”、“右”操作)：**
        `traversal(node->left, current_path_vals);`
        `traversal(node->right, current_path_vals);`
        * 在将当前节点加入路径后，我们递归地调用自身去探索其左子树和右子树，**信任**这些子调用会完成各自的任务。

    * **回溯 (Post-order / “清理”操作)：** `current_path_vals.pop_back();`
        * 这是**最关键**的一步，它确保了共享状态 `current_path_vals` 的正确性。当一个节点 `node` 的所有子树（左子树和右子树）都探索完毕后，`node` 在**当前路径**上的职责就完成了。
        * 为了让**父节点**能够探索**其他分支**（例如，从 `node` 的父节点转向 `node` 的兄弟节点），我们需要将 `node` 从 `current_path_vals` 中移除，使 `current_path_vals` 恢复到 `node` **被加入之前的状态**。这就是“回溯”，它像橡皮擦一样擦去当前节点对路径的临时修改。

### 易错点与优化

* **`path` 参数传递方式：** 最初你遇到的问题是 `vector<int> path` 按值传递，导致每次递归都复制整个 `vector`，且无法正确积累路径。修正为**引用传递 (`vector<int>& path`)** 是解决此问题的关键。
* **回溯 `pop_back()` 的位置：** 必须确保每次 `push_back()` 都有一个对应的 `pop_back()`，并且 `pop_back()` 发生在所有子递归调用完成之后。即，在函数**即将返回之前**。

通过本题，你不仅巩固了前序递归，更深入理解了**共享状态管理**和**回溯**在递归算法中的核心作用。这是你在算法学习道路上的又一个重要里程碑！
*/

#include <string>
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
    vector<string> res;
    // 1.参数root, path数组, 修改全局变量res
    void travesal(TreeNode *node, vector<int> &path) {
        // 2.终止条件1: 遇到空结点

        if (node == nullptr) {
            return;
        }
        // 中
        path.push_back(node->val);

        // 3.终止条件2: 遇到叶子节点,开始将path数组转化为字符串, 加入到res中
        if (node->left == nullptr && node->right == nullptr) {
            string result;
            for (int i = 0; i < path.size(); i++) {
                result += to_string(path[i]);
                if (i < path.size() - 1) {
                    result += "->";
                }
            }
            res.push_back(result);
        }
        // 左
        travesal(node->left, path);
        // 右
        travesal(node->right, path);
        path.pop_back();
    }

    vector<string> binaryTreePaths(TreeNode *root) {
        vector<int> path;
        travesal(root, path);
        return res;
    }
};