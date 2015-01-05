# coding=utf-8

'''快速排序。

划分的位置取最右边的位置。

'''

def qs(d, L, R):
    while True:
        if L == R:
            return
        rangeL = [number for number in d[L+1:R] if number < d[L]]
        rangeR = [number for number in d[L+1:R] if number >= d[L]]
        d[L:R] = rangeL + [d[L]] + rangeR
        if len(rangeL) < len(rangeR):
            qs(d, L, L+len(rangeL))
            L = L+len(rangeL)+1
        else:
            qs(d, L+len(rangeL)+1, R)
            R = L+len(rangeL)

def sort(L):
    ans = list(L)
    qs(ans, 0, len(ans))
    return ans

