## 边界条件

关于边界条件第一开始就写好，或者在提交之前把所有的边界条件都试一遍然后打补丁，不要漠视。一些琐碎的题目要求也属此类，不要忽视。
```diff
- 边界条件相当重要！一定要一开始想着写好！
```

## 数据范围

卡数据范围果断long long

## 状态数

一个状态数很多的解法也许可以骗一些分，但永远不可能AC。如果你能预料到你的写法会产生很多状态（例如多层迭代，多重循环），就不要用在一个需要AC的地方。

减少状态数的方法

* 动态规划（May 02 Leetcode 010 Regular Expression Matching）
* （实际遇到）数据规模很大但取值范围很小，则针对每个可能取值保存信息（May 01 Leetcode 739）


```diff
+ this will be highlighted in green
- this will be highlighted in red
```
