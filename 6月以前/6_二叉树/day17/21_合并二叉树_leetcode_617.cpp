/*
### 1. 合并二叉树 (LeetCode 617)

**问题描述**：给定两棵二叉树 `root1` 和 `root2`，将它们合并成一棵新二叉树。合并规则是：如果两个节点重叠，则将它们的值相加作为新节点的值；否则，不为空的节点将作为新树的节点。

#### 我们遇到的问题与解决方案：

1.  **最初代码的编译错误**：
    * **你的问题**：函数 `mergeTrees` 编译不通过，提示 `Non-void function does not return a value in all control paths` (非 `void` 函数并非在所有控制路径都返回值)。
    * **根本原因**：在 `root1` 和 `root2` 都不为 `nullptr` 的情况下，你执行了 `root1->val += root2->val;` 和递归调用，但**缺少了最终的 `return root1;` 语句**。C++ 编译器要求所有非 `void` 函数在其所有可能的执行路径上都必须有 `return` 语句。
    * **解决方案**：在完成当前节点的合并和子树的递归连接后，明确 `return root1;`。

2.  **对 `return` 语句位置的理解**：
    * **你的疑问**：你提到“`return` 好像一般放在终止条件那里”。
    * **解释与澄清**：
        * 对于**“自底向上”**的递归（例如计算树高、统计节点数），通常每个分支（包括基本情况和递归情况）都会返回一个值。
        * 对于**“自顶向下”**的递归（例如收集所有路径），如果函数返回 `void`，终止条件就是 `return;`。
        * **本题 (`mergeTrees`) 属于“自顶向下修改树结构”并同时“返回 `TreeNode*`”的混合模式**。因此，它在基本情况 (`root1 == nullptr` 或 `root2 == nullptr`) 处有 `return`，在处理完当前层逻辑并连接子树后，也需要 `return` 当前层修改后的根节点 (`root1`)。

#### 最终代码逻辑（递归）：

```cpp
class Solution {
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        // 1. 终止条件 / 基本情况
        if (root1 == nullptr) {
            return root2; // 如果 root1 为空，直接返回 root2（可能为null，也可能是子树）
        }
        if (root2 == nullptr) {
            return root1; // 如果 root2 为空，而 root1 不为空，返回 root1
        }

        // 2. 单层递归逻辑 / 处理当前节点
        // 如果 root1 和 root2 都不为空，则合并当前节点的值 (原地修改 root1)
        root1->val += root2->val;

        // 3. 递归合并子树
        // 相信递归会正确返回合并后的左/右子树根节点，并连接到 root1
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        // 4. 返回当前合并后的树的根节点
        return root1; 
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
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        // 确定终止条件
        if (root1 == nullptr) {
            return root2;
        }
        if (root2 == nullptr) {
            return root1;
        }
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        return root1;
    }
};