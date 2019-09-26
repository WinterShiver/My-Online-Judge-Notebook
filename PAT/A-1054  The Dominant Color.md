
# 1054  The Dominant Color  (20  分)

Behind the scenes in the computer's memory, color is always talked about as a series of 24 bits of information for each pixel. In an image, the color with the largest proportional area is called the dominant color. A  **strictly**  dominant color takes more than half of the total area. Now given an image of resolution  M  by  N  (for example,  800×600), you are supposed to point out the strictly dominant color.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive numbers:  M  (≤800) and  N  (≤600) which are the resolutions of the image. Then  N  lines follow, each contains  M  digital colors in the range [0,2​^24​​). It is guaranteed that the strictly dominant color exists for each input image. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, simply print the dominant color in a line.

### Sample Input:

```
5 3
0 0 255 16777215 24
24 24 0 0 24
24 0 24 24 24

```

### Sample Output:

```
24
```

### 解题思路

这道题实际要求我们在一个数组当中找到个数严格多于一半的元素。两个思路：

1.两两去除不相等的元素对，最后剩下的元素即为所求。

2.取这组数据的中位数即为所求。

直接试着交了一下第二种思路基于排序求中位数的O(n^logn)的方法，而且也没有用scanf/printf，居然直接过了。实际上取中位数有近似线性的做法。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 800 * 600 + 3;

int main(){
    int N, M;
    cin >> N >> M;
    int color[MAX];
    // main logic
    for(int i=0; i<N*M; i++){
        cin >> color[i];
    }
    sort(color, color+N*M);
    cout << color[N*M/2] << endl;
    return 0; 
}
```
