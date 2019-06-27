# 并查集 Union Set

* 功能：用来合并集合
* 算法：首先确定每一个元素的父亲：如果觉得两者属于同一个集合，就让其中一者的父亲为另一者。然后通过父亲找祖宗，两者肯定能找到相同的祖宗。


## 例子

763.  Partition Labels

A string  `S`  of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

**Example 1:**  

**Input:** S = "ababcbacadefegdehijhklij"
**Output:** [9,7,8]
**Explanation:**
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

**Note:**  

1.  `S`  will have length in range  `[1, 500]`.
2.  `S`  will consist of lowercase letters (`'a'`  to  `'z'`) only.

**解题思路：**按照字符划分集合。对每个字符，确定头尾字符圈定的范围，范围内的字符都能追溯到相同的祖宗。

```cpp
class Solution {
public:
    vector<int> partitionLabels(string S) {
        int* father = new int[S.size()];
        int* ancester = new int[S.size()];
        for(int i=0; i<S.size(); i++){
            father[i] = -1;
        }
        for(char a='a'; a<='z'; a++){
            int head, tail;
            for(head=0; head<S.size(); head++){
                if(S[head] == a) break;
            }
            for(tail=S.size()-1; tail>=0; tail--){
                if(S[tail] == a) break;
            }
            if(head<=tail){
                for(int i=head+1; i<=tail; i++) father[i] = head;
            }
        }
        vector<int> result;
        int curr = -1;
        for(int i=0; i<S.size(); i++){
            int ans = i;
            while(father[ans] != -1) ans = father[ans];
            ancester[i] = ans;
        }
        for(int i=0; i<S.size()-1; i++){
            if(ancester[i] != ancester[i+1]){
                result.push_back(i-curr);
                curr = i;
            }
        }
        result.push_back(S.size()-1-curr);
        delete[] father;
        delete[] ancester;
        return result;
    }
};
```
