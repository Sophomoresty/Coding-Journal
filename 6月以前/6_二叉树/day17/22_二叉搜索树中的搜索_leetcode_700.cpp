/*
**问题描述**：给定二叉搜索树（BST）的根节点和一个值 `val`，在 BST 中找到值为 `val` 的节点。如果节点存在，返回其子树；如果不存在，返回 `nullptr`。

#### 我们遇到的问题与解决方案：

1.  **未充分利用 BST 特性**：
    * **你的最初尝试**：你最初的代码同时递归搜索了左右子树，像遍历普通二叉树一样。
        ```cpp
        // ...
        TreeNode *left = searchBST(root->left, val);
        TreeNode *right = searchBST(root->right, val);
        if (left == nullptr) return right;
        // ... (错误示范)
        ```
    * **根本原因**：没有利用 BST 的核心定义（左子树 < 根 < 右子树）。这种方法退化成了 $O(N)$ 的通用二叉树搜索，浪费了 BST 的 $O(\log N)$ 优势。
    * **解决方案**：在每个节点，根据 `root->val` 与 `val` 的比较结果，**只向一个方向（左或右）递归**。这实现了**剪枝**，显著提高效率。

2.  **递归函数 `return` 路径的严谨性**：
    * **你的问题**：在修正了 BST 特性后，你提供的代码 (`if (val < root->val) { return ...; } if (val > root->val) { return ...; }`) 依然被编译器报错 `Non-void function does not return a value in all control paths`。
    * **根本原因**：C++ 编译器在进行静态分析时，无法自动推断出 `val < root->val` 和 `val > root->val` 已经穷尽了 `val != root->val` 的所有可能性（因为它没有“记住” `val == root->val` 的情况已经在函数开头处理了）。它认为可能存在一个分支没有 `return`。
    * **解决方案**：使用 `else if` 或 `else` 结构，明确告诉编译器所有路径都被覆盖。最常见且推荐的是：`if (val < root->val) { return ...; } else { return ...; }`。

#### 最终代码逻辑（递归，利用 BST 特性）：


#### 额外思考：迭代解法

* **你的代码**：你独立写出的迭代解法 `searchBST_traversal`，也是 BST 搜索的常用且高效的实现。它同样利用了 BST 特性进行定向移动，避免了递归栈的开销。
* **它不是标准的树遍历**：你的代码只是沿着一条路径查找，不会访问树中所有节点。
```cpp
class Solution {
public:
    TreeNode *searchBST(TreeNode *root, int val) {
        // 1. 终止条件 / 基本情况
        // 如果当前节点为空 (没找到)，或者当前节点的值就是目标值 (找到了)
        if (root == nullptr || root->val == val) {
            return root; // 直接返回当前节点（可能是 nullptr，也可能是目标节点）
        }

        // 2. 递归关系 / 单层逻辑 (利用 BST 特性进行剪枝)
        // 如果目标值比当前节点值小，只向左子树搜索
        if (val < root->val) {
            return searchBST(root->left, val); 
        }
        // 否则（目标值比当前节点值大），只向右子树搜索
        else { // val > root->val
            return searchBST(root->right, val); 
        }
    }
};
```
*/
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
    // 1. 参数: 当前树的根节点, 参考值
    // 2. 返回值: 匹配到了的节点
    // 3. 终止条件:
    // 1) 空节点, 返回空节点
    // 2) 根节点匹配对应的值, 返回对应节点
    // 4.单层递归逻辑
    TreeNode *searchBST(TreeNode *root, int val) {
        // 3.终止条件
        if (root == nullptr || root->val == val) {
            return root;
        }

        if (val < root->val) {
            return searchBST(root->left, val);
        }
        if (val > root->val) {
            return searchBST(root->right, val);
        }
    }

    TreeNode *searchBST_traversal(TreeNode *root, int val) {
        // 迭代法遍历, 利用BST的特性
        while (root != nullptr) {
            if (val == root->val) {
                return root;
            } else if (val < root->val) {
                root = root->left;
            }
            // val > root->val
            else {
                root = root->right;
            }
        }
        return nullptr;
    }
};