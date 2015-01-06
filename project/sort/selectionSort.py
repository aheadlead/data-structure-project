# coding=utf-8

'''选择排序。'''

def sort(L):
    ans = list(L)

    for round_ in xrange(len(ans)):

        minimum = ans[round_]
        minimumIndex = round_

        for index in xrange(round_, len(ans)):
            if ans[index] < minimum:
                minimum = ans[index]
                minimumIndex = index
        ans[round_], ans[minimumIndex] = ans[minimumIndex], ans[round_]
    
    return ans
    
