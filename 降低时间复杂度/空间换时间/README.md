# 空间换时间

某些数组，我们对其位置信息不关心，但是关心统计信息（是否出现，出现次数）。
在这种情况下，在使用这个数组的信息时，与其每次都遍历这个数组，不如先把这个数组的信息提取成一个统计数组（是否出现，出现次数），然后在以后的使用中就使用统计数组。

典型：PAT A-1050
