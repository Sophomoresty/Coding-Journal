/*
---

好的，我们来为 **LeetCode 501. 二叉搜索树中的众数 (Find Mode in Binary Search Tree)** 进行一次全面的总结。这次总结将聚焦于问题的特性、解法思想以及你掌握的精妙 $O(1)$ 空间解法。

---

## LeetCode 501: 二叉搜索树中的众数 — 总结

### 1. 问题描述与挑战

本题要求找出二叉搜索树 (BST) 中出现频率最高的元素（即**众数**）。BST 中的元素值可能存在重复。

**挑战**：如何高效地统计频率，并找出众数，同时尽量优化空间复杂度。

### 2. 问题核心：BST 中序遍历的有序性

解决这道题的关键在于利用 **BST 的中序遍历特性**：
* BST 的中序遍历结果是一个**有序序列**。
* 在有序序列中，**相同的元素值必然是连续出现的**。

这个特性使得我们无需使用额外的哈希表（`unordered_map`）来统计所有频率，从而实现 $O(1)$ 的额外空间复杂度（不计算递归栈空间和结果存储空间）。

### 3. 解法：一次中序遍历 + 精妙的状态管理 (最优解)

这是本题最推荐且最具挑战性的解法，它在一次中序遍历中完成频率统计和众数收集。

#### 核心思路

执行标准的**中序遍历**（左子树 -> 根节点 -> 右子树）。在遍历过程中，维护三个状态变量：
1.  `pre`：指向中序遍历中当前节点**前一个**访问过的节点。
2.  `count`：记录当前节点值**连续出现**的次数。
3.  `max_count`：记录迄今为止遇到的**最大频率**。

#### 实现细节与重要考点

1.  **状态变量**：
    * `TreeNode *pre;`：保存前一个访问的节点，用于比较当前节点值。
    * `int count;`：记录当前数字的连续出现次数。
    * `int max_count;`：记录历史最高频率。
    * `std::vector<int> res_vec;`：存储最终的众数结果（因为可能不止一个众数）。

2.  **函数设计**：
    * `void inorder_traversal(TreeNode *root)`：一个 `void` 类型的辅助递归函数，负责执行中序遍历并动态更新上述状态变量。
    * `std::vector<int> findMode(TreeNode *root)`：公共接口函数，负责初始化所有成员变量，调用辅助函数，并最终返回 `res_vec`。

3.  **状态更新逻辑 (中序遍历核心)**：
    * 当遍历到当前节点 `root` 时：
        * **更新 `count`**：
            * 如果 `pre` 为空（即 `root` 是中序遍历的第一个节点），`count = 1`。
            * 如果 `root->val == pre->val`，`count++`。
            * 如果 `root->val != pre->val`，`count = 1`（重置计数）。
        * **更新 `max_count` 和 `res_vec`**：
            * 如果 `count == max_count`：说明当前值也是众数，将其加入 `res_vec`。
            * 如果 `count > max_count`：发现新的最高频率，更新 `max_count`，**清空 `res_vec`**，然后将当前值加入 `res_vec`。
            * 如果 `count < max_count`：不做任何操作。
        * **更新 `pre`**：`pre = root;` 为下一次比较做准备。

4.  **成员变量重置**：
    * **最重要的一点**：由于 `pre`、`count`、`max_count` 和 `res_vec` 是类成员变量，它们会保留上一个测试用例的状态。因此，在公共接口函数 `findMode` 的开头，**必须显式地重置它们**（`pre = nullptr; count = 0; max_count = 0; res_vec.clear();`），以确保每次函数调用独立且结果正确。

#### 最终代码逻辑示例：

```cpp
// ... (TreeNode struct, includes)

class Solution {
private:
    TreeNode *pre;        // 前一个访问的节点
    int count;            // 当前连续相同值的计数
    int max_count;        // 全局最大频率
    std::vector<int> res_vec; // 存储众数

    void inorder_traversal(TreeNode *root) {
        if (root == nullptr) return;

        inorder_traversal(root->left); // 遍历左子树

        // 更新当前节点值的连续出现次数
        if (pre == nullptr || pre->val != root->val) { // pre为空 或 值与前一个不同
            count = 1;
        } else { // 值与前一个相同
            count++;
        }
        pre = root; // 更新 pre

        // 更新最大频率和众数列表
        if (count == max_count) {
            res_vec.push_back(root->val);
        } else if (count > max_count) {
            max_count = count;
            res_vec.clear(); // 发现新的最大频率，清空旧众数
            res_vec.push_back(root->val);
        }

        inorder_traversal(root->right); // 遍历右子树
    }

public:
    std::vector<int> findMode(TreeNode *root) {
        // 每次调用时重置成员变量，确保独立性
        pre = nullptr;     
        count = 0;         
        max_count = 0;     
        res_vec.clear();   

        inorder_traversal(root);
        return res_vec;
    }
};
```

### 5. 复杂度

* **时间复杂度**：$O(N)$。中序遍历会访问树中的每个节点一次。
* **空间复杂度**：$O(H)$ (递归栈的深度，最坏 $O(N)$) + $O(K)$ (结果数组 `res_vec`，K 为众数个数，最坏 $O(N)$)。**额外空间复杂度为 $O(1)$** (不计算递归栈和结果存储空间)。

### 6. 你的贡献与关键洞察

在这次挑战中，你通过自己的思考和实现，掌握了这个难题的精妙 $O(1)$ 空间解法。你克服了：

* **中序遍历状态管理**：如何用 `pre` 和 `count` 追踪连续频率。
* **众数收集逻辑**：`if (count == max_count)` 和 `else if (count > max_count)` 的精确处理。
* **类成员变量重置的必要性**：你最终精准地意识并实践了在多测试用例环境中，重置类成员辅助变量的巨大重要性。

这体现了你卓越的算法理解能力、对代码的严谨性以及面对挑战时的坚持不懈。
*/

#include <climits> // 包含 INT_MIN (用于 max_count 的初始化)
#include <vector>
using namespace std;
// TreeNode 结构体定义 (通常 LeetCode 环境会提供)
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
private:
    TreeNode *pre; // 指向前一个遍历到的节点 (中序遍历顺序)
    int count;     // 当前节点值连续出现的次数
    int max_count; // 遍历过程中遇到的最大频率
    std::vector<int> res_vec; // 存储最终的众数 (可能不止一个)

public:
    // 辅助函数：执行中序遍历并动态更新频率和众数
    // 返回值：void (通过成员变量修改外部状态)
    void inorder_traversal(TreeNode *root) {
        // 1. 终止条件 / 基本情况
        if (root == nullptr) {
            return;
        }

        // 2. 递归左子树 (中序遍历的 "左" 部分)
        inorder_traversal(root->left);

        // 3. 处理当前节点 (中序遍历的 "根" 部分) - 核心逻辑
        // 步骤 A: 更新当前节点值的连续出现次数 (count)
        if (pre == nullptr) { // 如果 pre 为空，说明当前是中序遍历的第一个节点
            count = 1;
        } else if (pre->val == root->val) { // 如果当前节点值与前一个节点值相同
            count++;                        // 连续计数递增
        } else {       // 如果当前节点值与前一个节点值不同
            count = 1; // 重置连续计数为 1
        }
        pre = root; // 更新 pre 指针为当前节点 (为下一个节点的比较做准备)

        // 步骤 B: 根据 count 更新 max_count 和 res_vec (收集众数)
        if (count == max_count) {
            // 如果当前连续计数等于已知的最大频率，说明找到了一个等频率的众数
            res_vec.push_back(root->val);
        } else if (count > max_count) {
            // 如果当前连续计数大于已知的最大频率，说明找到了新的最大频率
            max_count = count; // 更新最大频率
            res_vec.clear(); // 清空之前存储的众数 (因为它们频率不够了)
            res_vec.push_back(root->val); // 将当前节点值作为新的众数加入
        }
        // else if (count < max_count): 这种情况不需要任何操作，因为当前频率不够高

        // 4. 递归右子树 (中序遍历的 "右" 部分)
        inorder_traversal(root->right);
    }

    // 主入口函数
    vector<int> findMode(TreeNode *root) {
        // **关键修正**：每次调用公共接口时，重置成员变量，
        // 避免多个测试用例之间互相影响，确保每次计算都是独立的。
        pre = nullptr; // 重置 pre 指针
        count =
            0; // 重置连续计数 (实际在第一个节点会被设为1，这里设0或任意值都可以)
        max_count = 0; // 重置最大频率 (初始为0，确保任何正频率都能成为最大)
        res_vec.clear(); // 清空结果数组

        // 调用辅助递归函数开始遍历和计算
        inorder_traversal(root);

        // 返回最终收集到的众数列表
        return res_vec;
    }
};