# 并查集 Union Set

* 功能：用来合并集合
* 算法：首先确定每一个元素的父亲：如果觉得两者属于同一个集合，就让其中一者**祖宗**的父亲为另一者的**祖宗**。然后通过父亲找祖宗，两者肯定能找到相同的祖宗。注意一定要做这个找祖宗的工作，否则不能保证并查集的有效，或者导致嵌套。

## 练习1

L2-010  排座位  (25  分)

布置宴席最微妙的事情，就是给前来参宴的各位宾客安排座位。无论如何，总不能把两个死对头排到同一张宴会桌旁！这个艰巨任务现在就交给你，对任何一对客人，请编写程序告诉主人他们是否能被安排同席。

### 输入格式：

输入第一行给出3个正整数：`N`（≤100），即前来参宴的宾客总人数，则这些人从1到`N`编号；`M`为已知两两宾客之间的关系数；`K`为查询的条数。随后`M`行，每行给出一对宾客之间的关系，格式为：`宾客1 宾客2 关系`，其中`关系`为1表示是朋友，-1表示是死对头。注意两个人不可能既是朋友又是敌人。最后`K`行，每行给出一对需要查询的宾客编号。

这里假设朋友的朋友也是朋友。但敌人的敌人并不一定就是朋友，朋友的敌人也不一定是敌人。只有单纯直接的敌对关系才是绝对不能同席的。

### 输出格式：

对每个查询输出一行结果：如果两位宾客之间是朋友，且没有敌对关系，则输出`No problem`；如果他们之间并不是朋友，但也不敌对，则输出`OK`；如果他们之间有敌对，然而也有共同的朋友，则输出`OK but...`；如果他们之间只有敌对关系，则输出`No way`。

### 输入样例：

```
7 8 4
5 6 1
2 7 -1
1 3 1
3 4 1
6 7 -1
1 2 1
1 4 1
2 3 -1
3 4
5 7
2 3
7 2

```

### 输出样例：

```
No problem
OK
OK but...
No way
```

### 解题思路：
朋友关系：凡是涉及这种可数重关系也算关系的，就用并查集。每当两个人确定关系，就找到他们的祖宗，并确保这两个祖宗在同一个集合里，就能保证这两个人在同一个集合里。

敌人关系：可以直接存储（计算了一下，这道题的空间卡的不大，存储敌人关系并不麻烦。如果空间卡的严or太稀疏，就不按二维数组存储，而是直接存储输入。）


## 练习3

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

**解题思路：** 按照字符划分集合。对每个字符，确定头尾字符圈定的范围，范围内的字符都能追溯到相同的祖宗。

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
