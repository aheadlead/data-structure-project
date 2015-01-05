# coding=utf-8

'''归并排序，非递归版本。'''

def merge(d, rangeL, rangeM, rangeR):
    pA = rangeL
    pB = rangeM
    tmp = []
    while pA != rangeM and pB != rangeR:
        if d[pA] < d[pB]:
            tmp.append(d[pA])
            pA = pA+1
        else:
            tmp.append(d[pB])
            pB = pB+1
    while pA != rangeM:
        tmp.append(d[pA])
        pA = pA+1
    while pB != rangeR:
        tmp.append(d[pB])
        pB = pB+1
    d[rangeL:rangeR] = tmp
    

def sort(L):
    ans = list(L)
    a = 1
    while a < len(ans):
        for rangeL in xrange(0, len(ans), 2*a):
            if rangeL+a<len(ans):
                rangeM = rangeL+a
                rangeR = rangeM+a if rangeM+a<len(ans) else len(ans)
                merge(ans, rangeL, rangeM, rangeR)
        a = a*2
    return ans
    
