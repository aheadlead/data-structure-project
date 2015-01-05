# coding=utf-8

'''冒泡排序。'''

def sort(L):
    ans = list(L) # 深拷贝
    
    for i in xrange(0, len(ans)-1):
        for j in xrange(0, len(ans)-1-i):
            if ans[j] > ans[j+1]:
                ans[j], ans[j+1] = ans[j+1], ans[j]

    return ans
    
