# coding=utf-8

'''桶排序。'''

import math

def sort(L):
    ans = list(L)
    
    # 得到最大的数字的长度
    maxDigit = int(math.ceil(
        reduce(lambda a, b: max(a, math.log10(b)), [0]+L))) + 1

    for d in xrange(maxDigit):
        bucket = [[] for i in range(10)]
        for number in ans:
            bucket[number%(10**(d+1))/(10**d)].append(number)
        ans = reduce(lambda a, b: a+b, bucket) # 合并桶子

    return ans

