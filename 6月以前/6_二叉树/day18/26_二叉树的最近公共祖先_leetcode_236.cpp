/*
---

好的，我们来为 **LeetCode 236. 二叉树的最近公共祖先 (Lowest Common Ancestor, LCA)** 进行一次全面且深入的总结。这次总结将完整涵盖我们对该问题的**递归方法论应用**、**核心理解LCA的逻辑点**，以及所有攻克的难点。

---

## LeetCode 236: 二叉树的最近公共祖先 (LCA) — 终极总结

### 1. 问题描述与挑战

给定一个二叉树的根节点 `root`，以及树中的两个不同节点 `p` 和 `q`，找出它们的**最近公共祖先 (LCA)**。最近公共祖先的定义是：“对于有根树 `T` 的两个节点 `p`、`q`，最近公共祖先 `LCA(T, p, q)` 是指一个最低的节点 `z`，使得 `z` 既是 `p` 的祖先，又是 `q` 的祖先（我们允许一个节点是它自己的祖先）。”

**挑战**：LCA 问题的递归模式与传统二叉树遍历（前、中、后、层序）或简单递归（如计算高度、路径和）不同，它需要**更复杂的自底向上信息汇报和分叉点识别**。

### 2. 递归设计方法论在 LCA 中的应用

LCA 问题是理解**递归函数“承诺”模型**和**自底向上信息回溯**的经典案例。

#### 2.1 核心思想：函数就是黑箱 — 相信与承诺

所有递归设计的起点。我们将 `TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)` 这个函数视为一个能完成特定任务的“黑箱”。

* **函数签名**：`TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)`
* **函数承诺 (核心！)**：当这个函数被调用在**某个子树的根节点 `root` 上时，它承诺会返回：**
    1.  如果 `p` 和 `q` **都存在于** 以 `root` 为根的这棵子树中：
        * 返回它们的**最近公共祖先 (LCA) 节点**。
    2.  如果 `p` 和 `q` **只有一个存在于** 以 `root` 为根的这棵子树中：
        * 返回**那个存在的节点** (`p` 或 `q`)。
    3.  如果 `p` 和 `q` **都不存在于** 以 `root` 为根的这棵子树中：
        * 返回 `nullptr`。

#### 2.2 基本情况 (Base Case) — 递归的终点

* **`root == nullptr`**：空节点无法包含 `p` 或 `q`。
    * **返回**：`nullptr` (兑现承诺：什么都没找到)。
* **`root == p || root == q`**：当前节点就是 `p` 或 `q` 中的一个。
    * **返回**：`root` (兑现承诺：我找到了其中一个目标节点，就返回我。如果另一个目标节点在我的子树里，那我就是 LCA；否则，我就是那个唯一找到的节点)。

#### 2.3 递归关系 (Recursive Relation) — 分解与组合

这是“相信”的力量。假设子问题 (`root->left` 和 `root->right`) 的 `lowestCommonAncestor` 调用已经兑现了它们的“承诺”，返回了正确结果 (`left_res` 和 `right_res`)。现在，`root` 需要根据这些“汇报”，决定自己向上一层汇报什么。

* **场景 1：`left_res` 和 `right_res` 都非空** (`left_res != nullptr && right_res != nullptr`)
    * **含义**：左子树汇报找到了一个目标（或其 LCA），右子树也汇报找到了另一个目标（或其 LCA）。这说明 `p` 和 `q` 分别位于 `root` 的左右子树中。
    * **结论**：当前 `root` 就是 `p` 和 `q` 的 LCA。
    * **返回**：`root` (兑现承诺：返回 LCA)。

* **场景 2：`left_res` 为空，`right_res` 非空** (`left_res == nullptr && right_res != nullptr`)
    * **含义**：左子树什么都没找到，所有目标节点（`p` 和 `q`，或其中一个）都存在于 `root` 的右子树中。
    * **结论**：LCA 必然在右子树中，或者 `right_res` 本身就是 `p` 或 `q`。
    * **返回**：`right_res` (兑现承诺：返回那个存在的目标节点或子树中的 LCA)。

* **场景 3：`left_res` 非空，`right_res` 为空** (`left_res != nullptr && right_res == nullptr`)
    * **含义**：右子树什么都没找到，所有目标节点（`p` 和 `q`，或其中一个）都存在于 `root` 的左子树中。
    * **结论**：LCA 必然在左子树中，或者 `left_res` 本身就是 `p` 或 `q`。
    * **返回**：`left_res` (兑现承诺：返回那个存在的目标节点或子树中的 LCA)。

* **场景 4：`left_res` 和 `right_res` 都为空** (`left_res == nullptr && right_res == nullptr`)
    * **含义**：左右子树都什么都没找到。
    * **结论**：`p` 和 `q` 都不存在于以 `root` 为根的这棵子树中。
    * **返回**：`nullptr` (兑现承诺：什么都没找到)。

#### 2.4 信息流向：自底向上汇报结果

LCA 的递归本质是**自底向上**的信息传递。`p` 和 `q` 就像在树中发出信号的灯塔。这些信号沿着调用栈一层层向上回溯，直到：
* **信号汇聚点**：第一个同时收到来自左右子树信号的祖先节点，它就“捕获”了这两个信号，并识别出自己就是 LCA。
* **信号传递者**：如果一个节点只收到一个信号，它就继续把这个信号往上传。

### 3. 最终代码逻辑

```cpp
#include <cstddef> // For nullptr

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 1. 基本情况 / 递归终止条件
        // 如果 root 为空 (意味着当前子树找不到 p 或 q)，
        // 或者 root 就是 p 或 q (意味着我们找到了其中一个目标节点)。
        if (root == nullptr || root == p || root == q) {
            return root; // 直接返回 root (可能是 nullptr, p, 或 q)
        }

        // 2. 递归处理左右子树 (后序遍历的思路：先递归子节点，再处理当前节点)
        // left_res 承诺返回在左子树中找到的 p/q 或其 LCA，或 nullptr
        TreeNode* left_res = lowestCommonAncestor(root->left, p, q);
        // right_res 承诺返回在右子树中找到的 p/q 或其 LCA，或或 nullptr
        TreeNode* right_res = lowestCommonAncestor(root->right, p, q);

        // 3. 单层逻辑：根据左右子树的搜索结果判断当前 root 的角色
        // 场景 A：左右子树都找到了目标节点 (p 和 q 分别位于 root 的不同子树中)
        // 那么当前 root 就是它们的最近公共祖先 (LCA)
        if (left_res != nullptr && right_res != nullptr) {
            return root;
        } 
        // 场景 B, C, D 统一处理：
        // 如果 left_res 不为空，说明目标在左边（或者 left_res 就是 LCA），返回 left_res。
        // 否则 (left_res 为空)，说明目标在右边（或者 right_res 就是 LCA，或者两边都没有），返回 right_res。
        // (此写法简洁且覆盖了所有剩余情况，包括 left_res 和 right_res 都为 nullptr 时返回 nullptr)
        else if (left_res != nullptr) { 
            return left_res;
        } else { // 此时 left_res 必为 nullptr
            return right_res; // right_res 可能是找到了目标，也可能是 nullptr
        }
    }
};
```

### 4. 复杂度分析

* **时间复杂度**：$O(N)$。在最坏情况下，需要遍历树中的所有节点。每个节点最多被访问一次。
* **空间复杂度**：$O(H)$，其中 $H$ 是树的高度。这主要来自递归栈的深度。在最坏情况下（树倾斜），$H$ 可以是 $N$，所以空间复杂度为 $O(N)$。

### 5. 你的关键突破

你对 LCA 问题的理解，是你在递归方法论上的一次重大飞跃：

* **从“理解”到“设计”**：你通过套用“函数承诺”和“基本情况 - 递归关系”的框架，成功地推导出了这个复杂递归的逻辑。
* **攻克“自底向上”的难题**：你理解了 LCA 递归的本质是自下而上地汇报信息，并在最低的分叉点“截获”LCA。
* **对编译器严谨性的坚持**：你通过实践，理解了编译器对 `return` 语句的严格要求，即使逻辑上似乎穷尽了所有路径，也需要语法上的明确覆盖。

你对算法的深层探索精神，以及对细节的执着追求，都令人印象深刻。
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 1.明确签名与承诺:
    // 参数是当前树的节点, p,q两个目标节点
    // 承诺, 我感觉要回答承诺, 在一开始我很难直接给出, 我需要写出整体的函数框架, 才能给出承诺
    // 这里的承诺不是单一的, 思考也不能从根节点出发, 首先我们是自底向上的, 所以要代入基础情况和中间节点思考, 最后再到根节点
    // 从基础情况来看, root是空节点直接返回空节点; root是p或则q, 返回root, 表明我们找到了p或则q
    // 后续就是遵循自底向上, 也就是后序遍历, 我们拿到左右子树返回的结果, 噢, 不对由于后续的内容我还没思考, 我也不知道它返回什么结果.
    // 所以承诺必须得一开始思考出来, 在这里写的时候把函数当成黑箱, 用承诺去理解.
    // 所以承诺是:
    // 1) 如果有p或则q, 我返回给你
    // 2) 如果有p和q的最近的公共祖先, 我返回给你
    // 3) 如果没有p和q, 我返回给你空
    // 2.基本情况
    // 1) root是空节点
    // 2) root是p或则q
    // 3.假设子问题已经解决, 我现在需要综合左右子树返回的信息, 继续向上传递
    // 如果左右均不为空, 意味着root是最近的公共祖先
    // 如果左右其中一个为空, 我继续向上传递不为空
    // 如果左右均为空, 我传递为空
    // 4.信息流向, 自下而上汇报结果
    // 5.剪枝/优化, 优化不了, 我需要逐一从下往上汇报给根节点, 不能提前停止

    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        // 2.基本情况
        if (root == nullptr) {
            return root;
        }
        if (root == p || root == q) {
            return root;
        }
        // 3.递归关系

        TreeNode *left_res = lowestCommonAncestor(root->left, p, q);
        TreeNode *right_res = lowestCommonAncestor(root->right, p, q);
        // 拿到左右子树的结果, root要根据现有的信息再向上汇报
        if (left_res != nullptr && right_res != nullptr) {
            return root;
        } else if (left_res != nullptr) {
            return left_res;
        } else {
            return right_res;
        }
    }
};