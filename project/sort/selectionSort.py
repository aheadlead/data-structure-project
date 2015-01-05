# coding=utf-8

'''选择排序。'''

def sort(L):
    ans = [] 
    isSelected = [False] * len(L)

    for round_ in xrange(len(L)):

        minimum = "infinity" # 在 Python 中，字符串比任何整数都要大
        minimumIndex = -1

        for index, number in enumerate(L):
            if isSelected[index]:
                continue
            if number < minimum:
                minimum = number
                minimumIndex = index
        
        isSelected[minimumIndex] = True
        ans.append(minimum)
    
    return ans
    
