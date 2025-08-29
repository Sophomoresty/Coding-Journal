#include <vector>
using namespace std;
class Solution {

private:
    void swapString(vector<char> &s, int left, int right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
    }

public:
    void reverseString(vector<char> &s) {
        int left, right;
        for (left = 0, right = s.size() - 1; left < right; left++, right--) {
            swapString(s, left, right);
        }
    }
};