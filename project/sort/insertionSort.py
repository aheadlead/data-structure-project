# coding=utf-8

'''插入排序。'''

def sort(L):
    ans = []
    for number in L:
        pos = None
        for index, n in enumerate(ans): # 确定位置
            if n > number:
                pos = index
                break
        if pos == None:
            ans.append(number)
        else:
            ans.insert(index, number) 
    return ans
    
