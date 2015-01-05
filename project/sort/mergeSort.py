# coding=utf-8

'''归并排序。'''

def ms(L):
    if len(L) == 1:
        return L
    ret = []
    rangeA = ms(L[:len(L)/2])
    rangeB = ms(L[len(L)/2:])
    while len(rangeA) > 0 and len(rangeB) > 0:
        ret.append(rangeA.pop() if rangeA[-1] > rangeB[-1] else rangeB.pop())
    while len(rangeA) > 0:
        ret.append(rangeA.pop())
    while len(rangeB) > 0:
        ret.append(rangeB.pop())
    ret.reverse()
    return ret

def sort(L):
    ans = list(L) # 深拷贝
    ans = ms(ans)
    return ans

