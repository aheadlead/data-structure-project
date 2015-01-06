#!/usr/bin/env python
# coding=utf-8

'''一大堆排序算法的比较。

    算法名字         程序文件名
    -----------------------------------
    插入排序         insertionSort.py
    希尔排序         shellSort.py
    冒泡排序         bubbleSort.py
    快速排序         quickSort.py
    选择排序         selectionSort.py
    堆排序           heapSort.py
    递归归并排序     mergeSort.py
    非递归归并排序   mergeSortNonRecursive.py
    基数排序         radixSort.py
    Python排序       pythonSort.py

'''

import os
import timeit

from prettytable import PrettyTable
    
def CR():
    print "\r"



if __name__ != "__main__":
    print __file__ + u"不是一个模块。不可被导入。"
    exit(1)

sortAlgorithm = [ 
        { "name": u"插入排序", "module": "insertionSort" },
        { "name": u"希尔排序", "module": "shellSort" },
        { "name": u"冒泡排序", "module": "bubbleSort" },
        { "name": u"快速排序", "module": "quickSort" },
        { "name": u"选择排序", "module": "selectionSort" },
        { "name": u"堆排序", "module": "heapSort" },
        { "name": u"归并排序A", "module": "mergeSort" },
        { "name": u"归并排序B", "module": "mergeSortNonRecursive" },
        { "name": u"基数排序", "module": "radixSort" },
        { "name": u"Python排序", "module": "pythonSort" } ]

os.system("python makeRandomNumber.py")

# 读入数据
samples = []
for path, dirnames, filenames in os.walk("sample"):
    for filename in filenames:
        print u"读入文件" + filename
        with open("sample/"+filename, "r") as h:
            rawsample = []
            for strNumber in h.xreadlines():
                rawsample.append(int(strNumber))
            samples.append({"filename": filename, "data": rawsample})

# 导入模块
for m in sortAlgorithm:
    try:
        print u"导入模块" + m["module"]
        exec "import " + m["module"]
        m["function"] = eval(m["module"] + ".sort")
    except ImportError:
        print u"导入模块" + m["module"] + u"时发生问题。"
        exit(1)

sample = None
module = None
def run():
    module["function"](sample["data"])

# 开始比较
##########
print u"开始测试"
x = PrettyTable(["测试用例 \ 算法"] + [m["name"] for m in sortAlgorithm])
for sample in samples:   
    row = [sample["filename"]]
    for module in sortAlgorithm:
        print u"正在以" + module["name"] + u"算法测试测试用例" + sample["filename"]
        timeList = timeit.repeat(stmt="run()", \
                setup="from __main__ import sample, module, run", repeat=3,
                number=1)
        row.append("%.3f" % (sum(timeList)/len(timeList)))
    x.add_row(row)

print x
