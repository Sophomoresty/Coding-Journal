/*

## LeetCode 98: 验证二叉搜索树 — 总结

### 1. 问题描述与核心定义

本题要求判断给定的二叉树是否是一个**有效的二叉搜索树 (Binary Search Tree, BST)**。

**BST 的核心定义（标准教科书版本，不允许重复值）：**
* 对于任意节点 `N`：
    * 其**左子树**中所有节点的值都**严格小于** `N->val`。
    * 其**右子树**中所有节点的值都**严格大于** `N->val`。
* 左右子树本身也必须是有效的 BST。

### 2. 核心思路：中序遍历的单调性

判断一个二叉树是否为 BST 的最经典、最直观且高效的方法是利用其**中序遍历**的特性：
* **一个有效的 BST 的中序遍历结果，必然是**严格递增**的（从小到大排序）。**
* 因此，我们可以对树进行中序遍历，并在遍历过程中，检查当前节点的值是否严格大于前一个节点的值。

### 3. 解法选择与实现方式

我们主要探讨了基于**递归中序遍历**的方法。

#### 递归中序遍历 + 辅助变量 (最优解)

**基本思路**：
执行中序遍历 (左 -> 根 -> 右)。在访问到每个节点（“根”部分）时，将其值与**前一个**已经访问过的节点的值进行比较。

**关键挑战与解决方案：**

1.  **“前一个节点”状态的保存**：
    * **你的洞察**：你正确地意识到，`pre` (前一个节点) 的状态需要**跨越递归调用**进行保存，因此不能作为局部变量定义在函数体内。
    * **解决方案**：将 `pre` 定义为 `Solution` 类的**成员变量**（`TreeNode *pre = nullptr;`）。在每次 `isValidBST` 外部调用时（例如在 LeetCode 平台对每个测试用例调用时），需要确保 `pre` 被重置为 `nullptr`，以避免多个测试用例之间状态相互影响。

2.  **严格递增的判断**：
    * **你的质疑**：你最初的判断条件可能只检查 `pre->val > root->val`，没有考虑到相等的情况。你后续也精确地提出“BST 中 `pre` 和 `root` 的值不能相等”。
    * **解决方案**：确保判断条件捕获**所有违反严格递增的情况**。最严谨的条件是 `root->val <= pre->val`（如果 `pre` 不为 `nullptr`）。这会捕获 `pre` 大于 `root` 或 `pre` 等于 `root` 的所有不合法情况。

3.  **递归剪枝与返回时机**：
    * **你的问题**：你最初的代码在左子树验证失败时，没有立即返回 `false`，而是继续了后续比较和右子树的递归。
    * **解决方案**：在每次递归调用子树（`isValidBST(root->left)` 或 `isValidBST(root->right)`）之后，如果子树的验证结果为 `false`，**立即返回 `false`**。这能有效剪枝，避免不必要的计算。

#### 最终代码逻辑 (递归中序遍历，符合标准 BST 定义)：

```cpp
#include <stack>  // (通常用于迭代解法，这里用于确保包含，但不直接使用)
#include <vector> // (通常用于数组，这里用于确保包含，但不直接使用)

// TreeNode 结构体定义 (LeetCode 通常会提供)
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    // pre 指针用于保存中序遍历中当前节点的前一个节点。
    // 它是类成员变量，确保在递归调用之间保持状态。
    // 每次调用公共接口 isValidBST 时，需要确保其被重置。
    TreeNode *pre = nullptr; 

public:
    // 判断二叉树是否为有效的二叉搜索树 (BST)
    bool isValidBST(TreeNode *root) {
        // 1. 终止条件 / 基本情况 (Base Case)
        // 空节点被认为是有效的 BST 子树 (因为没有节点可以违反规则)
        if (root == nullptr) {
            return true;
        }

        // 2. 递归左子树 (中序遍历的 "左" 部分)
        // 如果左子树本身不是有效的 BST，那么整个树都不是，立即返回 false (剪枝，提高效率)
        if (!isValidBST(root->left)) {
            return false;
        }

        // 3. 处理当前节点 (中序遍历的 "根" 部分)
        // 检查当前节点的值是否严格大于前一个节点的值
        // 如果 pre 不为空 (即不是中序遍历的第一个节点)，
        // 并且当前节点的值不严格大于 pre 的值 (即 root->val <= pre->val)，
        // 则违反 BST 的严格递增性质（包括值相等的情况）。
        if (pre != nullptr && root->val <= pre->val) { 
            return false;
        }
        // 更新前一个节点为当前节点 (为下一个节点的比较做准备)
        pre = root;

        // 4. 递归右子树 (中序遍历的 "右" 部分)
        // 如果右子树本身不是有效的 BST，那么整个树都不是，立即返回 false (剪枝)
        if (!isValidBST(root->right)) {
            return false;
        }

        // 5. 如果左子树、当前节点检查、右子树都通过了验证，则整个子树是有效的 BST
        return true;
    }
};
```

### 4. 你的关键贡献

你对本题的深入探讨和一系列精准的质疑，是理解这个算法的关键：

* **对 `pre` 变量状态管理（类成员与重置）的理解**：你正确地发现了 `pre` 需要跨越递归保存状态。
* **对“严格递增”的坚持与质疑**：你反复确认 BST 值不能相等，并推动我调整判断条件 (`root->val <= pre->val`) 以确保严格递增，这是最正确的理解。
* **对剪枝和返回时机的优化**：你发现了最初代码中缺少必要的 `false` 返回剪枝，提升了效率和正确性。

你的严谨、细致和批判性思维，使我们能够彻底攻克这个算法，并理解其背后每一个微妙的逻辑点。*/
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
    // 1. 参数: 根节点
    // 2. 返回值: 是否符合BST特性
    // 3. 终止条件: root为空节点 返回true
    // 4. 单层递归
    // 对树进行中序遍历, pre为root的前一个节点, 按照正确的中序遍历结果, pre应该小于root,由于pre需要跨越递归保存,
    // 也就是不能pre不能放在函数体内定义
    TreeNode *pre = nullptr;
    bool isValidBST(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        if (!isValidBST(root->left)) {
            return false;
        }

        if (pre != nullptr && pre->val >= root->val) {
            return false;
        }

        pre = root;

        if (!isValidBST(root->right)) {
            return false;
        }
        return true;
    }
};