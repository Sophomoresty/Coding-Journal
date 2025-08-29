#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    // 暴力解法
    // 遍历s,t两个数组, 对s中每一个字符, 在t中找到对应的字符,
    // 为了防止重复匹配到已匹配的字符, 需要对匹配的字符进行换值, 因此t需要备份,
    bool baoli_isAnagram(string s, string t) {
        // 长度不等直接false
        if (s.length() != t.length()) {
            return false;
        }
        // 因为要对t修改, 提前备份
        string t_backup = t;

        // 定义1个bool值, 表示当前s的字符是否匹配上t了
        bool found;
        for (int i = 0; i < s.length(); i++) {
            found = false;
            for (int j = 0; j < t_backup.length(); j++) {
                // 如果相等的话
                if (s[i] == t_backup[j]) {
                    found = true;
                    t_backup[j] = '#'; // 对匹配到的字符进行更替, 防止重复匹配
                    break; // s的字符已经找到了对应的字符, 没必要找了
                }
            }
            // s的一个字符在t中没找到, 直接返回false
            if (found == false) {
                return false;
            }
        }
        return true;
    }
    // 只处理小写字母, 而不是unicode编码, 小写字母的ascii码有26个,
    // 所以只需要长度为26的数组, 遍历s,t将每个字符映射到数组的索引, 然后++
    // 如果数组中的值均为2, 则s,t是字母异位词, 有问题,
    // 字符串里面的字符可以重复出现,
    // 也就是出现偶数个才是正确的, 还是有问题, 如果是 aa 和 bb,也会是偶数
    // 所以最好的思路是, t中的字符++, s中的字符--,
    // 如果字符在数组中对应的值为0的话, 也就意味着字符相等
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }

        vector<int> hash_vec(26);
        for (int i = 0; i < s.length(); i++) {
            hash_vec[s[i] - 'a']++;
            hash_vec[t[i] - 'a']--;
        }
        for (int i = 0; i < hash_vec.size(); i++) {
            if (hash_vec[i] != 0) {
                return false;
            }
        }
        return true;
    }
};