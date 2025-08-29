#include <cstdio>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {

        // ransomNote 和 magazine 由小写英文字母组成
        // 可以用长度26的数组作为哈希表, magazing出现过的字符, 对应值+1,
        // for循环遍历ransomNote, 看哈希表中有没有对应的字符
        vector<int> res_vec(26, 0);
        for (auto i : magazine) {
            res_vec[i - 'a']++;
        }

        for (auto i : ransomNote) {
            if (res_vec[i - 'a'] > 0) {
                res_vec[i - 'a']--;
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    string ransomNote = "aa";
    string magazine = "aab";
    Solution sol;
    bool flag = sol.canConstruct(ransomNote, magazine);
    // canConstruct("a", "b") -> false
    printf("canConstruct(\"%s\", \"%s\") -> %s\n", ransomNote.c_str(),
           magazine.c_str(), flag ? "true" : "false");
    return 0;
}