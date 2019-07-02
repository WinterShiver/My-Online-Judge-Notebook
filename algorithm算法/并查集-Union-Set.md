# 并查集 Union Set

* 功能：用来合并集合，处理**连通域**问题，和**传递性关系**问题，最适合使用并查集。
* 算法：首先确定每一个元素的父亲：如果觉得两者属于同一个集合，就让其中一者**祖宗**的父亲为另一者的**祖宗**。然后通过父亲找祖宗，两者肯定能找到相同的祖宗。注意一定要做这个找祖宗的工作，否则不能保证并查集的有效，或者导致嵌套。
* 别忘了给father赋初始值-1

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

### 代码
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdio>
#include <bitset>
using namespace std;

const int N = 103;

static int father[N];
static int ancester[N];
static bool foul[N][N];

int def_ancester(int i){
    // 确定并赋值ans
    int ans = i;
    while(father[ans] != -1)
        ans = father[ans];
    ancester[i] = ans;
    return ans;
}

void def_father(int i, int j){
    // 确定并查集的关系，有赋值副作用
    int ans_i = def_ancester(i);
    int ans_j = def_ancester(j);
    if(ans_i != ans_j)
        father[ans_i] = ans_j;
}

int main(){
    int n, m, k; 
    cin >> n >> m >> k;
    for(int i=0; i<=n; i++)
        father[i] = -1;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            foul[i][j] = false;
    // new father
    int aa, bb, judge;
    // printf("Begin cin m ge\n");
    for(int i=0; i<m; i++){
        // printf("i = %d, m = %d", i, m);
        cin >> aa >> bb >> judge;
        aa--; bb--;
        if(judge == 1)
            def_father(aa, bb);
        else
            foul[aa][bb] = foul[bb][aa] = true;
    }
    // new ancester
    for(int i=0; i<n; i++){
        def_ancester(i);
    }
    // relation judge
    // printf("Begin cin k ge\n");
    for(int i=0; i<k; i++){
        // printf("i = %d, k = %d", i, k);
        cin >> aa >> bb;
        aa--; bb--;
        if(ancester[aa] == ancester[bb]){
            if(foul[aa][bb])
                printf("OK but...");
            else
                printf("No problem");
        }
        else{
            if(foul[aa][bb])
                printf("No way");
            else
                printf("OK");
        }
        if(i < k-1) printf("\n");
    }
    return 0;
}
```

## 练习2


L2-007  家庭房产  (25  分)

给定每个人的家庭成员和其自己名下的房产，请你统计出每个家庭的人口数、人均房产面积及房产套数。

### 输入格式：

输入第一行给出一个正整数N（≤1000），随后N行，每行按下列格式给出一个人的房产：

```
编号 父 母 k 孩子1 ... 孩子k 房产套数 总面积

```

其中`编号`是每个人独有的一个4位数的编号；`父`和`母`分别是该编号对应的这个人的父母的编号（如果已经过世，则显示`-1`）；`k`（0≤`k`≤5）是该人的子女的个数；`孩子i`是其子女的编号。

### 输出格式：

首先在第一行输出家庭个数（所有有亲属关系的人都属于同一个家庭）。随后按下列格式输出每个家庭的信息：

```
家庭成员的最小编号 家庭人口数 人均房产套数 人均房产面积

```

其中人均值要求保留小数点后3位。家庭信息首先按人均面积降序输出，若有并列，则按成员编号的升序输出。

### 输入样例：

```
10
6666 5551 5552 1 7777 1 100
1234 5678 9012 1 0002 2 300
8888 -1 -1 0 1 1000
2468 0001 0004 1 2222 1 500
7777 6666 -1 0 2 300
3721 -1 -1 1 2333 2 150
9012 -1 -1 3 1236 1235 1234 1 100
1235 5678 9012 0 1 50
2222 1236 2468 2 6661 6662 1 300
2333 -1 3721 3 6661 6662 6663 1 100

```

### 输出样例：

```
3
8888 1 1.000 1000.000
0001 15 0.600 100.000
5551 4 0.750 100.000
```
### 解题思路

因为祖宗有父母两种，而且男女可能以任意的组合形成父母，所以直接找祖宗不方便。使用并查集，单纯把父母儿女当成亲属关系建立并查集，从而确定亲属关系。

### 代码
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdio>
#include <bitset>
using namespace std;

const int N = 10003;

static int num[N];
static double area[N];
static int father[N];
static int ancester[N];
static int family_num[N];
static bool isUsed[N];
static bool isUsed_family[N];

class Family{
public:
    int least_num;
    int num;
    int p_num;
    double area;
    Family(){
        least_num = N;
        p_num = num = area = 0;
    }
};

bool cmp(Family f1, Family f2){
    if(f1.area / f1.p_num > f2.area / f2.p_num) return true;
    else if(f1.area / f1.p_num < f2.area / f2.p_num) return false;
    else{
        return f1.least_num < f2.least_num;
    }
}

static Family fam[N];

int def_ancester(int i){
    // 确定并赋值ans
    int ans = i;
    while(father[ans] != -1)
        ans = father[ans];
    ancester[i] = ans;
    return ans;
}

void def_father(int i, int j){
    // 确定并查集的关系，有赋值副作用
    int ans_i = def_ancester(i);
    int ans_j = def_ancester(j);
    if(ans_i != ans_j)
        father[ans_i] = ans_j;
}

int main(){
    int n; cin >> n;
    for(int i=0; i<N; i++){
        num[i] = area[i] = 0;
        father[i] = -1;
        isUsed[i] = isUsed_family[i] = false;
    }
    for(int i=0; i<n; i++){
        int index, f, m, k;
        cin >> index >> f >> m;
        isUsed[index] = true;
        if(f != -1){
            def_father(index, f);
            isUsed[f] = true;
        }
        // cout << "ok here" << endl;
        if(m != -1){
            def_father(index, m);
            isUsed[m] = true;
        }
        // cout << "ok here" << endl;
        cin >> k;
        for(int j=0; j<k; j++){
            int child; cin >> child;
            def_father(index, child);
            isUsed[child] = true;
        }
        cin >> num[index] >> area[index];
    }
    for(int i=0; i<N; i++){
        if(isUsed[i])
            def_ancester(i);
    }
    for(int i=0; i<N; i++){
        if(isUsed[i]){
            int index_f = ancester[i];
            isUsed_family[index_f] = true;
            fam[index_f].num += num[i];
            fam[index_f].area += area[i];
            fam[index_f].p_num ++;
            if(fam[index_f].least_num > i)
                fam[index_f].least_num = i;
        }
    }
    vector<Family> v1;
    for(int i=0; i<N; i++){
        if(isUsed_family[i])
            v1.push_back(fam[i]);
    }
    sort(v1.begin(), v1.end(), cmp);
    printf("%d\n", (int)v1.size());
    for(int i=0; i<v1.size(); i++){
        printf("%04d %d %0.3f %0.3f", v1[i].least_num, v1[i].p_num, (double)v1[i].num / v1[i].p_num, v1[i].area / v1[i].p_num);
        if(i != v1.size()-1) printf("\n");
    }
    return 0;
}
```

## 练习3

L3-003  社交集群  (30  分)

当你在社交网络平台注册时，一般总是被要求填写你的个人兴趣爱好，以便找到具有相同兴趣爱好的潜在的朋友。一个“社交集群”是指部分兴趣爱好相同的人的集合。你需要找出所有的社交集群。

### 输入格式：

输入在第一行给出一个正整数 N（≤1000），为社交网络平台注册的所有用户的人数。于是这些人从 1 到 N 编号。随后 N 行，每行按以下格式给出一个人的兴趣爱好列表：

K​i​​:  h​i​​[1]  h​i​​[2]  ...  h​i​​[K​i​​]

其中K​i​​(>0)是兴趣爱好的个数，h​i​​[j]是第j个兴趣爱好的编号，为区间 [1, 1000] 内的整数。

### 输出格式：

首先在一行中输出不同的社交集群的个数。随后第二行按非增序输出每个集群中的人数。数字间以一个空格分隔，行末不得有多余空格。

### 输入样例：

```
8
3: 2 7 10
1: 4
2: 5 3
1: 4
1: 3
1: 4
4: 6 8 1 5
1: 4

```

### 输出样例：

```
3
4 3 1
```

### 解题思路：
这道题的关键是如何对关系编码，因为并查集需要的“人和人之间具有关系，且具有传递性”中，关系没有直接表示，而是以共处一类表示。

解决：对于每个关系设立了一个**代表元**，避免暴力检查人和人之间的关系造成的高复杂度（平方，甚至立方）。结果居然过了

### 代码
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdio>
#include <bitset>
using namespace std;

const int N = 1003;

static int father[N];
static int ancester[N];
static int repre[N];

int def_ancester(int i){
    // 确定并赋值ans
    int ans = i;
    while(father[ans] != -1)
        ans = father[ans];
    ancester[i] = ans;
    return ans;
}

void def_father(int i, int j){
    // 确定并查集的关系，有赋值副作用
    int ans_i = def_ancester(i);
    int ans_j = def_ancester(j);
    if(ans_i != ans_j)
        father[ans_i] = ans_j;
}

int main(){
    for(int i=0; i<N; i++){
        father[i] = repre[i] = -1;
    }
    int n; cin >> n;
    for(int i=0; i<n; i++){
        int k; cin >> k;
        cin.get();
        for(int j=0; j<k; j++){
            int index; cin >> index;
            if(repre[index] == -1) repre[index] = i;
            else def_father(repre[index], i);
        }
    }
    for(int i=0; i<n; i++){
        def_ancester(i);
    }
    // 利用之前的代表元数组计一下数
    for(int i=0; i<n; i++){
        repre[i] = 0;
    }
    for(int i=0; i<n; i++){
        repre[ancester[i]] ++;
    }
    vector<int> v1;
    for(int i=0; i<n; i++){
        if(repre[i])
            v1.push_back(repre[i]);
    }
    sort(v1.begin(), v1.end());
    reverse(v1.begin(), v1.end());
    printf("%d\n", (int)v1.size());
    for(int i=0; i<v1.size(); i++){
        printf("%d", v1[i]);
        if(i != v1.size()-1) printf(" ");
    }
    return 0;
}
```

## 练习4

L2-013  红色警报  (25  分)

战争中保持各个城市间的连通性非常重要。本题要求你编写一个报警程序，当失去一个城市导致国家被分裂为多个无法连通的区域时，就发出红色警报。注意：若该国本来就不完全连通，是分裂的k个区域，而失去一个城市并不改变其他城市之间的连通性，则不要发出警报。

### 输入格式：

输入在第一行给出两个整数`N`（0  <  `N`  ≤  500）和`M`（≤  5000），分别为城市个数（于是默认城市从0到`N`-1编号）和连接两城市的通路条数。随后`M`行，每行给出一条通路所连接的两个城市的编号，其间以1个空格分隔。在城市信息之后给出被攻占的信息，即一个正整数`K`和随后的`K`个被攻占的城市的编号。

注意：输入保证给出的被攻占的城市编号都是合法的且无重复，但并不保证给出的通路没有重复。

### 输出格式：

对每个被攻占的城市，如果它会改变整个国家的连通性，则输出`Red Alert: City k is lost!`，其中`k`是该城市的编号；否则只输出`City k is lost.`即可。如果该国失去了最后一个城市，则增加一行输出`Game Over.`。

### 输入样例：

```
5 4
0 1
1 3
3 0
0 4
5
1 2 0 4 3

```

### 输出样例：

```
City 1 is lost.
City 2 is lost.
Red Alert: City 0 is lost!
City 4 is lost.
City 3 is lost.
Game Over.
```
### 输入样例：

```
5 4
0 1
1 3
3 0
0 4
5
1 2 0 4 3

```

### 输出样例：

```
City 1 is lost.
City 2 is lost.
Red Alert: City 0 is lost!
City 4 is lost.
City 3 is lost.
Game Over.
```

### 解题思路：
这是一道很明显的连通域问题，就用并查集，在每一次丢失城市的时候更新连通域的个数。注意已经连通域下降可能是孤立的城市丢失or what，所以判断标准应该是“只算没有丢失的节点，连通域个数有没有上升”。

### 代码：
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdio>
#include <bitset>
using namespace std;

const int N = 503;
const int M = 5003;

static bool isAbandoned[N];
static int father[N];
static int ancester[N];
static int i1[M], i2[M];
static int n, m;

void renew_father(int n){
    for(int i=0; i<n; i++) 
        father[i] = -1;
}

int def_ancester(int i){
    // 确定并赋值ans
    int ans = i;
    while(father[ans] != -1)
        ans = father[ans];
    ancester[i] = ans;
    return ans;
}

void def_father(int i, int j){
    // 确定并查集的关系，有赋值副作用
    int ans_i = def_ancester(i);
    int ans_j = def_ancester(j);
    if(ans_i != ans_j)
        father[ans_i] = ans_j;
}

int check_groups(int n){
    // n: people number
    // given ancester[], return how many linked areas
    int result = 0;
    for(int i=0; i<n; i++){
        if(ancester[i] == i && !isAbandoned[i]) 
            result ++;
    }
    return result;
}

int mainloop(){
    renew_father(n);
    for(int i=0; i<m; i++){
        // 防止给出一条假的路。但其实没用，因为如果是假的路，def_father没有任何效果。
        if(i1[i] == i2[i]) continue;
        // 确定关系
        if(!isAbandoned[i1[i]] && !isAbandoned[i2[i]])
            def_father(i1[i], i2[i]);
    }
    for(int i=0; i<n; i++)
        def_ancester(i);
    return check_groups(n);
}

int main(){
    for(int i=0; i<N; i++){
        father[i] = -1;
    }
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> i1[i] >> i2[i];
    }
    int g_s = mainloop();
    int k; cin >> k;
    bool flag;
    // printf("%d\n", g_s);
    for(int i=0; i<k; i++){
        int index; cin >> index;
        isAbandoned[index] = true;
        int t_s = mainloop();
        flag = t_s > g_s;
        g_s = t_s;
        // printf("%d\n", g_s);
        if(flag) printf("Red Alert: City %d is lost!", index);
        else printf("City %d is lost.", index);
        if(i != k-1) printf("\n");
    }
    if(k == n) printf("\nGame Over.");
    return 0;
}
```

## 练习5

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
