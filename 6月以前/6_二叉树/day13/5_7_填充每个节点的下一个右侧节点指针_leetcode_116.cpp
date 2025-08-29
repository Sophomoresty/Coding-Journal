/*
好的，我们来总结一下本次关于 LeetCode 116 "填充每个节点的下一个右侧节点指针"
的所有问题以及我的回答。

---

## LeetCode 116 题目总结：填充每个节点的下一个右侧节点指针

本次讨论的核心是利用**层次遍历（BFS）** 来解决二叉树的 `next`
指针连接问题，并在此基础上进行了**空间复杂度的优化**。

### 一、你的初始思路与分析

你最初的思路是：

1.  执行层次遍历（BFS）。
2.  在遍历过程中，将**每一层的所有节点指针**都收集到一个 `vector<vector<Node*>>`
（二维数组）中。
3.  层次遍历结束后，再遍历这个二维数组，在每一层内部，将每个节点的 `next`
指针指向其右边的兄弟节点（即 `vec_res[i][j]->next =
vec_res[i][j+1]`），并将每层最后一个节点的 `next` 指向 `nullptr`。

**我的评估：**

* **算法正确性：** 这个思路是**完全正确**的，能够正确地连接所有 `next` 指针。
* **时间复杂度：** $O(N)$，其中 $N$
是树中节点的总数。因为每个节点都被访问和处理了一次，这是最优的。
* **空间复杂度：** $O(N)$。因为你使用了 `vector<vector<Node*>>`
来存储所有节点的指针，这会占用与节点总数成正比的空间。

### 二、问题的核心洞察与优化

你随后发现，你的方法虽然正确，但可能不是最优解。

1.  **你发现的问题：**
    * “没必要先存储的，再出来遍历一次的。”
    * 你提到了“没有想到用队列的 `front()`
作为下一个节点”，感觉自己忽略了这个特性，导致空间复杂度变高。

2.  **我的回答与优化方案：**
    * **核心洞察：**
你对“没必要先存储再遍历”的认识是**完全正确**的。这是优化空间的关键。
    * **优化方法：** 在**层次遍历的同一循环中**直接进行 `next`
指针的连接，而**无需**将所有节点存储到 `vector<vector<Node*>>` 中。
    * **关键技巧：** 利用队列的 **FIFO（先进先出）** 特性。当你在处理当前节点
`cur` 时，如果它不是当前层的最后一个节点，那么队列的 `front()`
元素（或者说在它之后刚刚入队的节点）**就是它的右侧兄弟节点**。
    * **代码体现：**
        ```cpp
        while (!que.empty()) {
            int level_size = que.size(); // 获取当前层的节点数量
            for (int i = 0; i < level_size; ++i) {
                Node *cur = que.front();
                que.pop();

                // 核心连接逻辑：
                if (i < level_size - 1) { // 如果不是当前层的最后一个节点
                    cur->next = que.front(); //
直接指向队列中下一个（即右侧兄弟） } else { // 如果是当前层最后一个节点
                    cur->next = nullptr; // 指向 nullptr
                }

                // 将子节点入队，为下一层做准备
                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
        ```
    * **优化后的空间复杂度：** 降为 $O(W)$，其中 `W`
是树的最大宽度（由队列决定）。这比 `O(N)`
更优，因为它避免了存储整个树结构的额外开销。
    * **时间复杂度：** 保持 $O(N)$
不变，但由于减少了内存分配和数据拷贝，实际运行时间会更快（常数因子优化）。

### 三、其他相关点

* **函数参数：** `Node *&root` 可以简化为 `Node *root`，因为你只修改 `root`
指向的节点内容，不改变 `root` 指针本身。

---

**总结：**

你最初的思路非常正确，有效地解决了问题。但通过我的引导和你的深入思考，你成功地发现了如何巧妙地利用**队列的
`front()` 特性**，在**同一层次遍历循环中直接完成 `next`
指针的连接**。这一优化使得算法的**空间复杂度从 $O(N)$ 降至
$O(W)$**，并带来了实际运行效率的提升。

这次讨论再次体现了在算法学习中，除了理解核心思路，还需要深入掌握数据结构的特性，并关注细节上的优化，才能写出更高效、更优雅的代码。你能够理解并吸收这些优化点，这表明你对算法的理解已经非常深入了！

*/

#include <queue>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    void levelorder_traversal_v2(Node *root) {
        if (root == nullptr) {
            return;
        }
        queue<Node *> que;
        que.push(root);

        while (!que.empty()) {
            int size = que.size();
            Node *cur;
            // i不是该层的最后一个, 都指向下一个节点
            // i是该层的最后一个, 指向空节点, 默认值是空, 不需要额外指定

            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                if (i < size - 1) {
                    cur->next = que.front();
                }

                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
        }
    }

    // 思路层序遍历, 每一层的的节点指针都加入数组, 指针数组保存到二维数组中
    // 最后对数组进行遍历, 处理每一层
    // 这么做的原因: 不是在层序遍历中处理,
    // 是因为层序遍历中无法知道同一层的后续节点, 要想知道就必须弹出后续节点,
    // 但这就做不到层序遍历
    // 不需要返回值, 修改头指针即可
    void levelorder_traversal(Node *&root) {
        if (root == nullptr) {
            return;
        }
        vector<vector<Node *>> vec_res;
        queue<Node *> que;
        que.push(root);
        while (!que.empty()) {
            int size = que.size();
            Node *cur;
            vector<Node *> temp;
            for (int i = 0; i < size; i++) {
                cur = que.front();
                que.pop();
                temp.push_back(cur);
                if (cur->left != nullptr) {
                    que.push(cur->left);
                }
                if (cur->right != nullptr) {
                    que.push(cur->right);
                }
            }
            vec_res.push_back(temp);
        }
        // vec_res存放每一层, 从左到右的指针
        for (int i = 0; i < vec_res.size(); i++) {
            // 遍历每一层的指针 vec_res[i][j]
            // 至少有1个元素, 每一个指针的next指向下一个
            // 如果下一个超出了索引size-1, 则指向空, 也就是 j+1  =
            // vec_res[i].size()
            for (int j = 0; j < vec_res[i].size(); j++) {
                if (j == vec_res[i].size() - 1) {
                    vec_res[i][j]->next = nullptr;
                } else {
                    vec_res[i][j]->next = vec_res[i][j + 1];
                }
            }
        }
    }

    Node *connect(Node *root) {
        levelorder_traversal(root);
        return root;
    }
};