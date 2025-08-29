#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        // 快慢指针法
        int slow, fast;
        slow = 0;
        for (fast = 0; fast < nums.size(); fast++) {
            if (nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        //slow指针指向新数组最后1个元素的下1个索引, 数值大小为新数组的元素个数, 即为不等于val的新数组元素个数
        return slow;
    }
};