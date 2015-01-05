# coding=utf-8

'''快速排序。

划分的位置取最右边的位置。

'''

def qs(d, L, R):
    if R == L:
        return []
    rangeL = [number for number in d[:-1] if number < d[-1]]
    rangeR = [number for number in d[:-1] if number >= d[-1]]
    return qs(rangeL, 0, len(rangeL)) + [d[-1]] + qs(rangeR, 0, len(rangeR))

def sort(L):
    ans = list(L)
    ans = qs(ans, 0, len(ans))
    return ans

