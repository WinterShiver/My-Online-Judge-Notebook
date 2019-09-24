
# 1049  Counting Ones  (30  分)

The task is simple: given any positive integer  N, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to  N. For example, given  N  being 12, there are five 1's in 1, 10, 11, and 12.

### Input Specification:

Each input file contains one test case which gives the positive  N  (≤2​30​​).

### Output Specification:

For each test case, print the number of 1's in one line.

### Sample Input:

```
12

```

### Sample Output:

```
5
```

### 解析和代码

之所以把这道题归为简单题，是因为这道题的思考过程不难，只要看过就能理解这个过程，从而代码实现出来。题目本身很新颖，但背后也没有特别深刻的思想体系。

这道题的核心是：针对个、十、百、千每一位出现1的次数，对数字1进行统计。然后只要在纸上写一下每一位1的个数是怎么统计的，就知道如何写统计的代码了。

具体的逻辑是要看这一位的值，如果小于1或大于1，则这一位1的个数是整的，由高位；如果是1则要额外考虑高位相等同位是1的数的个数，这个个数由低位确定。

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

const int MAX = 100005;
const int INF = 0x3f3f3f3f;

int count_num(int n_in, int num){
    int n = n_in;
    int result = 0;
    int ten = 1;
    while(n > 0){
        int tail = n % 10;
        n /= 10;
        if(tail < num){
            result += n * ten;
        }
        else if(tail == num){
            result += n * ten + (n_in - n * ten * 10 - ten + 1);
        }
        else{
            result += (n + 1) * ten;
        }
        ten *= 10;
    }
    return result;
}

int count1(int n){
    return count_num(n, 1);
}

int main(){
    int n;
    cin >> n;
    cout << count1(n);
    return 0; 
}
```
