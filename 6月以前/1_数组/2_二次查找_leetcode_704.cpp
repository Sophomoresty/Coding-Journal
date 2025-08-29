#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        int right, left, mid;
        right = 0;
        left = nums.size() - 1;
        for (; right <= left;) {
            mid = (right + left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                right = mid + 1;
            } else {
                left = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> test = {-1, 0, 3, 5, 9, 12};
    int target = 3;
    Solution s;
    int i = s.search(test, target);
    cout << i << '\n';
}