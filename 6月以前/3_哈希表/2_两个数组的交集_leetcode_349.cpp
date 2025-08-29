#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
    // 暴力解法
    // 用1个额外的数组存储交点 (这个做法是错误的, 数组无法去重)
    // 空间复杂度o(min(n,m)), 时间复杂度o(n*m)
    vector<int> baoli_intersection(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> intersection_set;
        for (int i = 0; i < nums1.size(); i++) {
            for (int j = 0; j < nums2.size(); j++) {
                if (nums1[i] == nums2[j]) {
                    intersection_set.insert(nums1[i]);
                    break;
                }
            }
        }
        return vector<int>(intersection_set.begin(), intersection_set.end());
    }
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {

        // unordered_set无序, 数值不可以重复, 值不能更改,
        // 所以存储结果必须单开集合

        // 找到长, 短数组
        vector<int> nums_short = nums1.size() < nums2.size() ? nums1 : nums2;
        vector<int> nums_long = nums1.size() < nums2.size() ? nums2 : nums1;

        unordered_set<int> nums_set(nums_short.begin(), nums_short.end());
        unordered_set<int> res_set;
        for (int num : nums_long) {
            // 在nums_set中找有没有相同的值, 有则加入
            // find的结果
            // 1. 找到的情况下返回当前值的迭代器
            // 2.没找到的情况下返回nums_set.end()
            if (nums_set.find(num) != nums_set.end()) {
                res_set.insert(num);
            }
        }
        return vector<int>(res_set.begin(), res_set.end());
        // 1.时间复杂度分析
        // 循环中需要遍历长数组, 最坏情况下, 时间复杂度为o(max(n,m))

        // 2.空间复杂度分析
        // 2.1 将最小数组存入集合中, 空间复杂度o(min(n,m))
        // 2.2 res_set用于存放相交的值, 空间复杂度为o(k), k<= o(min(n,m))
        // 2.3 最后返回的数组, 空间复杂同为o(k)
        // 综合来看, 空间复杂度为o(min(n,m))
    }

    // 最优解, 由于题目规定了数值仅在0-1000,
    // 最开始放短数组的值可以放在数组中, 数组的开销小, 能用数组就不要用set,
    // 使用数字必须在空间确定的情况下, 不确定的情况习, 容易造成空间浪费,
    // 这种情况下用set 所以存放数值还是必须要放在哈希表中, 因为最后要不重复
    vector<int> better_intersection(vector<int> &nums1, vector<int> &nums2) {
        vector<int> nums_array(1001, 0);
        unordered_set<int> res_set;

        // 找到长短数组
        vector<int> nums_short = nums1.size() < nums2.size() ? nums1 : nums2;
        vector<int> nums_long = nums1.size() < nums2.size() ? nums2 : nums1;

        // 遍历短数组, 用其值作为索引, 出现的情况下+1, 后续判断是否相交,
        // 即对长数组遍历, 判断其值的索引的值是否为1即可
        for (int num : nums_short) {
            nums_array[num] = 1;
        }

        for (int num : nums_long) {
            if (nums_array[num] == 1) {
                res_set.insert(num);
            }
        }
        return vector<int>(res_set.begin(), res_set.end());
    }
};