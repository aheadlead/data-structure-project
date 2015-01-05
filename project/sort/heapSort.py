# coding=utf-8

'''堆排序。

为了方便，采用了 Python 提供的库，我会单独写个堆的库。
'''

import heapq

def sort(L):
    heap = list(L)
    ans = []
    heapq.heapify(heap)
    while len(heap) > 0:
        ans.append(heapq.heappop(heap))
    return ans

