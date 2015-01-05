# coding=utf-8

'''希尔排序。

一种有点奇葩的排序。'''

magic = [150958081, 67084289, 37730305, 16764929, 9427969, 4188161, 2354689,
        1045505, 587521, 260609, 146305, 64769, 36289, 16001, 8929, 3905, 2161,
        929, 505, 209, 109, 41, 19, 5, 1]

def sort(L):
    ans = list(L)

    for gap in magic:
        for i in xrange(gap, len(L)):
            t = ans[i]
            j = i-gap
            while j>=0 and ans[j]>t:
                ans[j+gap] = ans[j]
                j = j-gap
            ans[j+gap] = t

    return ans
