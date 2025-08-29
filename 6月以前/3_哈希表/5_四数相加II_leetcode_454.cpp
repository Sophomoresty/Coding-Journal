#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
public:
    //

    // 哈希法
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                     vector<int> &nums4) {
        // 初始定义map
        unordered_map<int, int> res_map;

        //  遍历数组1,2, 对map进行初始化
        for (auto a : nums1) {
            for (auto b : nums2) {
                auto it = res_map.find(a + b);
                // unordered_map在创建未存在的键的时候会自动初始赋值为0,
                // 所以不需要手动初始化 不存在则value赋值为1
                // 存在则value++
                res_map[a + b]++;
            }
        }
        // 定义符合条件的四元组个数
        int count = 0;
        // 遍历数组3,4,在map中找对应的target的value
        for (auto c : nums3) {
            for (auto d : nums4) {
                int target = 0 - (c + d);
                auto it = res_map.find(target);
                // 找到的情况下
                if (it != res_map.end()) {
                    count += res_map[target]; //
                }
            }
        }
        return count;
    }
};