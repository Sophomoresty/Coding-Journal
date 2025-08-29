

/*
好的，我们来针对性地总结一下本次讨论中**关于 LeetCode 347 (前 K 个高频元素)** 及其核心实现——**堆（优先级队列）** 部分的所有问题和回答。

---

## 本次讨论总结：LeetCode 347 (前 K 个高频元素) 及堆的实现

我们本次的讨论深入探讨了 LeetCode 347 这道经典题目，其核心解法是利用**哈希表**统计频率，再结合**优先队列（堆）** 来筛选出前 K 个高频元素。

### 一、算法核心与时间复杂度

1.  **问题核心思路：**
    * 使用 `std::unordered_map<int, int>` 来统计每个数字的出现频率（键是数字，值是频率）。
    * 利用一个大小为 `k` 的**小顶堆（Min-Heap）** 来存储当前频率最高的 `k` 个元素。
2.  **算法流程：**
    * 遍历输入数组 `nums`，填充 `unordered_map`。
    * 遍历 `unordered_map` 中的每个键值对（数字-频率）。
    * 将键值对 `push` 入小顶堆。
    * 如果小顶堆的大小超过 `k`，则 `pop` 掉堆顶元素。由于是小顶堆，被弹出的将是当前堆中频率最小的那个元素。
    * 最终，堆中剩下的 `k` 个元素就是频率最高的 `k` 个。
    * 将堆中的元素按正确顺序（通常是倒序弹出）放入结果 `vector`。
3.  **时间复杂度分析：**
    * 统计频率：$O(N)$，其中 $N$ 是 `nums` 的长度。
    * 遍历 `map` 并维护堆：$O(M \log K)$，其中 $M$ 是 `map` 中不重复元素的数量（最坏情况下 $M=N$）。每次 `push` 和 `pop` 操作都是 $O(\log K)$。
    * 收集结果：$O(K \log K)$（因为要弹出 `K` 次）。
    * **总时间复杂度：$O(N + M \log K + K \log K)$，简化为 $O(N \log K)$**。这是该问题的最优解法。

### 二、小顶堆的实现与定制化

1.  **C++ 小顶堆的实现：**
    * **是的**，在 C++ STL 中，小顶堆通过 **`std::priority_queue`** 来实现。
    * `std::priority_queue` 默认是大顶堆。要实现小顶堆，需要为其提供一个自定义的**比较器（Comparator）**。

2.  **`std::priority_queue` 的模板参数：**
    * `std::priority_queue<T, Container, Compare>`
        * **`T`**：堆中存储的元素类型。在本题中是 `std::pair<int, int>`（数字-频率对）。
        * **`Container`**：实际存储元素的底层容器类型，通常是 `std::vector<T>`。
        * **`Compare`**：定义元素优先级的**函数对象（Functor）的类型**。这是实现小顶堆的关键。

3.  **自定义比较器 `mycomparison`（或 `cmp` 类）：**
    * 这是一个**类**，它重载了**函数调用运算符 `operator()`**。
    * **作用：** 它让 `mycomparison` 的实例（对象）能够像函数一样被调用，从而作为 `std::priority_queue` 的比较规则。
    * **访问修饰符：** `operator()` **必须是 `public` 的**，否则 `std::priority_queue` 无法调用它。
    * **比较逻辑：** `bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs)`
        * 其返回值为 `true` 表示 `lhs` 的优先级低于 `rhs`（即 `lhs` 应该排在 `rhs` 之后）。
        * 要实现小顶堆（希望**频率小**的元素优先级高），比较逻辑是 `return lhs.second > rhs.second;`。这意味着如果 `lhs` 的频率大于 `rhs` 的频率，那么 `lhs` 的优先级就低，它会被放到堆的下方。

4.  **`operator()` 中 `lhs` 和 `rhs` 的含义：**
    * `lhs` (left-hand side) 和 `rhs` (right-hand side) 是比较函数中**约定俗成**的参数命名，代表**任意两个待比较的元素**。
    * **它们不固定代表堆操作中的特定元素**（如即将加入的或堆顶元素）。`std::priority_queue` 内部的堆算法在调整过程中，会把需要比较的元素作为 `lhs` 和 `rhs` 传入。

5.  **`const &` 参数的作用：**
    * `const pair<int, int>& lhs` 中的 `&` 是**引用**，用于**避免复制 `pair` 对象的开销**，提高性能，因为比较器会被频繁调用。
    * `const` 确保函数内部不会修改传入的参数。

### 三、相关 C++ 语言特性

1.  **`std::pair` 数据结构：**
    * 它是一个简单的模板类，用于**精确组合两个（且只能是两个）** 值（如数字和频率）。成员通过 `.first` 和 `.second` 访问。
    * 如果需要组合**多于两个**元素：
        * 推荐使用 **`std::tuple` (C++11+)**，它可以组合任意数量的不同类型的值。
        * 或者定义**自定义 `struct` 或 `class`**，当数据有明确语义时更佳。
2.  **`operator()` 重载的本质：**
    * 它让类的实例（对象）可以像函数一样被调用。
    * 在 C++98/03 中，定义重载 `operator()` 的类是为 `std::priority_queue` 提供自定义比较器的**主要方式**，因为其模板参数需要一个**类型**。C++11 后的 Lambda 表达式也基于函数对象实现。
    * 比较器的作用就是**改变 `std::priority_queue` 的默认排序行为**（从大顶堆到小顶堆）。

### 四、代码细节问题与修正

1.  **结果 `vector` 初始化：**
    * **原问题：** `vector<int> vec_res;` 后直接使用 `vec_res[i] = ...;` 导致**越界访问**。
    * **修正：** 需要将 `vector` 初始化为所需大小，例如 `vector<int> vec_res(k);`，再进行倒序填充。
2.  **`cmp::operator()` 访问修饰符：**
    * **原问题：** `private: bool operator()...`
    * **修正：** 必须是 `public`，否则外部无法调用。

---

*/
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
private:
    // 定义小顶堆的cmp类
    class cmp {
    public:
        bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return lhs.second > rhs.second;
            // rhs是后加进来的元素, 为了让小的优先级大, 也就是让大于成立
        }
    };

public:
    vector<int> topKFrequent(vector<int> &nums, int k) {
        // 用map统计数字出现的次数 数字:频率
        // 时间复杂度 o(n)
        unordered_map<int, int> map_res;
        for (int i = 0; i < nums.size(); i++) {
            map_res[nums[i]]++;
        }
        // 定义小顶堆
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> queue_res;

        // 遍历map, 元素加入小顶堆, 大于k个弹出
        // 小顶堆排序的复杂度o(logk)
        // 总时间复杂度o(nlogk)
        for (auto i : map_res) {
            queue_res.push(i);
            if (queue_res.size() > k) {
                queue_res.pop();
            }
        }
        // 时间复杂度o(k)
        // 最初构造数组, 倒序加入, 毎加入一次就弹出
        vector<int> vec_res(k);
        for (int i = k - 1; i >= 0; i--) {
            vec_res[i] = queue_res.top().first;
            queue_res.pop();
        }
        return vec_res;
        // 最后的时间复杂度 o(nlogk)
    }
};