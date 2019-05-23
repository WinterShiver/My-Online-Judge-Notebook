# My-Online-Judge-Notebook

持续记录自己在过OJ时遇到的问题和积累的经验心得。
下面的内容是最常见、普遍的一些问题。

## 边界条件

关于边界条件第一开始就写好，或者在提交之前把所有的边界条件都试一遍然后打补丁，不要漠视。一些琐碎的题目要求也属此类，不要忽视。
```diff
- 边界条件相当重要！只要是有可能恶心人的，都不要怕麻烦提前写好
- 要不要删除冗余的边界条件？如果过OJ就没必要删除了，在影响效率的时候才删除，但一定要分析清楚再删除。
- 要不要释放内存？过OJ无所谓，做工程一定要释放。
```

## 数据范围

* 卡数据范围果断long long
* int的数据范围
  * 用负数的好处：int的负极值比正极值更大，所以比起用abs，反而把整数转换成负数操作要更简单。
  * 用正数的好处：C++ int 负数没有左移右移，而且正数更好。如果用正数不妨直接unsigned
  * 容易卡int数据范围：abs(INT_MIN) 除以0或-1 接近上下限的值加减 接近上下限的值做乘法
    * 用 mid = head+(tail-head)/2; 代替 mid = (tail+head)/2;
* double的数据范围
  * 卡误差：算好最大误差
  * 卡太大太小：善用eps

## 状态数

一个状态数很多的解法也许可以骗一些分，但永远不可能AC。如果你能预料到你的写法会产生很多状态（例如多层迭代，多重循环），就不要用在一个需要AC的地方。

减少状态数的方法

* 动态规划（May 02 Leetcode 010 Regular Expression Matching）
```diff
+ 涉及状态，状态数不多，动态规划就特别好用
```
* （实际遇到）数据规模很大但取值集合（取值范围）很小，则针对每个可能取值保存信息（May 01 Leetcode 739）（然后再动态规划，美滋滋）
  * 这个思路还有进阶：在卡空间复杂度不到O(n)，只给常数空间或者对数空间时，可以利用输入的空间。比如括号里面的题目利用交换让原输入数组起到了存储作用，避免再存储一次数据，特别巧妙。（May 12 Leetcode 041 First Missing Positive）
