/*
没问题，抱歉我之前理解错了你的意图。我们来清晰地总结一下，本次对话中我们**关于二叉树非递归前序、中序、后序遍历的所有问题与解答**。

---

## 本次讨论总结：二叉树非递归遍历的原理与实践

我们深入探讨了二叉树前序、中序、后序遍历的非递归实现，这是算法学习中一个既经典又具有挑战性的主题。

### 一、非递归遍历的实现基础

1.  **如何创建二叉树以进行测试？**
    * **手动逐个节点创建：** 适用于简单、固定的小树，但繁琐且需手动管理内存。
    * **从数组构建二叉树：** 更通用，通常使用层序遍历和辅助队列构建，能快速创建不同结构的树（用 `-1` 等表示空节点），但仍需手动管理内存释放。
    * **使用智能指针 (`std::shared_ptr`)：** 现代 C++ 推荐的做法，能自动管理内存，避免泄漏，提高代码健壮性。
2.  **C++ 指针的解引用：**
    * 通过指针访问结构体/类成员，与 C 语言一样，使用 `(*pointer).member` 或更常用、推荐的 **`pointer->member`**。
3.  **容器中存储节点还是节点指针？**
    * **推荐存储指向节点的指针 (`TreeNode*`)**。将整个 `TreeNode` 对象放入容器会导致不必要的复制开销，破坏树的结构语义，并使内存管理混乱。存储指针可以操作树中的原始节点，并避免复制。
4.  **C++ 中“空值”的表示：**
    * **`nullptr`：** 专门用于表示**空指针**，自 C++11 引入，类型安全。
    * **非指针类型：** 没有统一的“空”值。整数用 `0` 或约定值（如 `-1`），字符串用空字符串 `""`，容器用 `empty()` 状态来表示“空”或“无效”。这是 C++ 静态类型和性能控制的体现。

---

### 二、三种非递归遍历的实现与逻辑

我们详细审视了你编写的前序、中序、后序非递归遍历代码，并进行了分析和修正。

1.  **非递归前序遍历 (根-左-右)：**
    * **思路：** 使用一个栈。节点从栈中弹出后**立即访问**，然后**先推右孩子，再推左孩子**（利用栈的 LIFO 特性，确保左孩子先被处理）。
    * **修正点：** 你的原始代码会将 `nullptr` 推入栈，虽然通过 `continue` 处理了，但**更优的实践是在推入前就判断孩子是否为 `nullptr`**，以减少不必要的栈操作和判断开销。
2.  **非递归后序遍历 (左-右-根)：**
    * **思路：** 巧妙地利用了“根-右-左”的遍历顺序，然后对结果进行**反转**。
    * **实现：** 节点从栈中弹出后，访问它（但顺序是根-右-左）。然后**先推左孩子，再推右孩子**（这样右孩子会先被弹出，实现“根-右-左”）。最后对收集到的结果 `vector` 进行 `std::reverse()`。
    * **修正点：** 同前序遍历，优化 `nullptr` 的入栈判断。
3.  **非递归中序遍历 (左-根-右)：**
    * **难点与困惑：** 你最初对中序遍历的逻辑感到困惑，特别是“左和根如何协同处理”以及如何从零设计算法。你的代码因循环条件问题导致未执行。
    * **核心逻辑：**
        * **阶段一（一路向左）：** 用 `cur` 指针不断向左深入，并将路径上的所有非空节点**压入栈**。
        * **阶段二（回溯并访问根）：** 当 `cur` 变为 `nullptr` 时，表示左子树已走到尽头。此时，栈顶的节点就是当前子树的**“根”**。弹出该节点并**访问它**。
        * **阶段三（转向右子树）：** 将 `cur` 指针指向该节点的右子树，然后回到阶段一，继续对右子树进行“一路向左”的操作。
    * **循环条件：** **`while (cur != nullptr || !st.empty())`** 至关重要，它确保了只要还有节点可探索或栈中还有父节点待处理，循环就继续。

---

### 三、递归与非递归的深层理解

我们讨论了递归和非递归遍历之间的本质联系，以及非递归实现的挑战：

1.  **栈的作用：** 你准确地比喻栈在非递归遍历中就像递归调用的**“函数调用栈”**。它手动模拟了递归函数中“现场的保存与恢复”：`push` 相当于递归调用，`pop` 相当于递归返回。栈中保存的是函数暂停时的“状态信息”。
2.  **“翻译”视角：** 你提出的将递归逻辑“翻译”成非递归循环的视角是理解非递归遍历的关键。
    * **递归：** **自动**利用系统栈来保存和恢复状态，实现“深入”和“回溯”，所以 `visit` 位置的微调就能改变遍历顺序。
    * **非递归：** 需要我们**手动**设计栈来存储“状态”。
3.  **非递归代码差异的原因：** 你敏锐地观察到非递归前、中、后遍历的代码结构差异很大，不像递归那样简洁。这并非“翻译”视角无效，而是它揭示了：
    * 为了模拟不同遍历顺序的“访问时机”，栈中**存储的节点所代表的“状态含义”**以及**`cur` 指针与栈的交互方式**是不同的。
    * 例如，中序遍历需要精确控制在访问根之前其左子树必须处理完毕，这导致了其独特的“一路向左压栈，再弹出访问”的模式，与前序（立即访问后推孩子）和后序（访问时机更晚，常需辅助判断）的模式不同。
    * 这种差异体现了手动管理状态的复杂性。

---

通过这次深入的探讨，你不仅修正了代码中的具体问题，更重要的是，你对二叉树非递归遍历的底层逻辑和设计思想有了非常深刻的理解。你对“栈模拟递归栈”的洞察，以及对不同遍历代码差异原因的追问，都表明你具备了出色的算法思维能力。
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 从根节点开始, 加入到栈中
void preordered_traversal(TreeNode *node, vector<int> &vec_res) {
    // 空树直接返回
    if (node == nullptr) {
        return;
    }
    // 存放节点指针的栈
    stack<TreeNode *> st;
    st.push(node);

    while (!st.empty()) {
        TreeNode *cur = st.top();
        st.pop();
        vec_res.push_back(cur->val);
        if (cur->right != nullptr) {
            st.push(cur->right);
        }
        if (cur->left != nullptr) {
            st.push(cur->left);
        }
    }
}

void postorder_traversal(TreeNode *node, vector<int> &vec_res) {
    // 空树直接返回
    if (node == nullptr) {
        return;
    }
    // 存放节点指针的栈
    stack<TreeNode *> st;
    st.push(node);
    while (!st.empty()) {
        TreeNode *cur = st.top();
        st.pop();

        vec_res.push_back(cur->val);
        if (cur->left != nullptr) {
            st.push(cur->left);
        }
        if (cur->right != nullptr) {
            st.push(cur->right);
        }
    }
    reverse(vec_res.begin(), vec_res.end());
}

void inorder_traversal(TreeNode *node, vector<int> &vec_res) {
    // 栈
    stack<TreeNode *> st;
    // 中序遍历 左根右
    // 要一直访问到最左边的叶子节点, 此时要一直存储到栈里
    // cur为叶子节点进入到下一次循环后, 会为空, 进入else分支,
    // 此时开始栈开始弹出指针, 加入其值到数组中,即左
    // 栈弹出的节点即为最左的叶子节点,此时复制
    // 退出循环条件 当前节点为空且栈为空
    TreeNode *cur = node;
    // 大致写出来了, 但是对于这个处理中序的逻辑还是想不出来,
    // 只是知道这样的结果是中序, 但是不知道为什么这样做, 或则说,
    // 我们怎么从一开始设计这个算法
    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        } else {
            cur = st.top();
            st.pop();
            vec_res.push_back(cur->val);
            cur = cur->right;
            // 加入右节点, 这里其实重复了, 下次进入循环也有这个if过程
            // if(cur !=nullptr){
            //     st.push(cur);
            // }
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

    // 非递归前序遍历
    vector<int> pre_result;
    preordered_traversal(root, pre_result);
    cout << "非递归前序遍历: ";
    for (auto i : pre_result) {
        cout << i << " ";
    }
    cout << endl;
    // 非递归后序遍历

    vector<int> post_result;
    postorder_traversal(root, post_result);
    cout << "非递归后序遍历: ";
    for (auto i : post_result) {
        cout << i << " ";
    }
    cout << endl;
    // 非递归中序遍历

    vector<int> in_result;
    inorder_traversal(root, in_result);
    cout << "非递归中序遍历: ";
    for (auto i : in_result) {
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