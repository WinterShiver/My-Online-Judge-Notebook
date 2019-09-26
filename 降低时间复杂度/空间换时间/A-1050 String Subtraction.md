
#  1050 String Subtraction  (20  分)

Given two strings  S​1​​  and  S​2​​,  S=S​1​​−S​2​​  is defined to be the remaining string after taking all the characters in  S​2​​  from  S​1​​. Your task is simply to calculate  S​1​​−S​2​​  for any given strings. However, it might not be that simple to do it  **fast**.

### Input Specification:

Each input file contains one test case. Each case consists of two lines which gives  S​1​​  and  S​2​​, respectively. The string lengths of both strings are no more than  10​4​​. It is guaranteed that all the characters are visible ASCII codes and white space, and a new line character signals the end of a string.

### Output Specification:

For each test case, print  S​1​​−S​2​​  in one line.

### Sample Input:

```
They are students.
aeiou

```

### Sample Output:

```
Thy r stdnts.
```

### 思路

> 空间换时间的概念：某些数组，我们对其位置信息不关心，但是关心统计信息（是否出现，出现次数）。 在这种情况下，在使用这个数组的信息时，与其每次都遍历这个数组，不如先把这个数组的信息提取成一个统计数组（是否出现，出现次数），然后在以后的使用中就使用统计数组。

注意到要去掉的串可能很长，但实际上ASCII码根本没有那么多，所以不能判断主串每个字母的时候都遍历一遍要去掉的串。在这种情况下，想到用一个数组记录要去掉的串中出现的字符，然后在主串输出时直接在这个数组里面检索当前字符是否出现即可。

```cpp
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAX = 100005;
const int INF = 0x3f3f3f3f;

int main(){
    char source[MAX], no_occur[MAX];
    cin.get(source, MAX);
    cin.get();
    cin.get(no_occur, MAX);
    // main logic
    bool ASCII_allowed[128+3];
    for(int i=0; i<128+3; i++){
        ASCII_allowed[i] = true;
    }
    for(int i=0; i<strlen(no_occur); i++){
        ASCII_allowed[no_occur[i]] = false;
    }
    for(int i=0; i<strlen(source); i++){
        if(ASCII_allowed[source[i]]) cout << source[i];
    }
    return 0; 
}
```
