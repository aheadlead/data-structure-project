#!/usr/bin/env python
# coding=utf-8

'''对排序函数的单元测试。

待测试的排序函数应当只有一个参数，即为待排序的列表。
函数应返回一个对原列表升序排序的列表。

测试方法是随机生成长度为100的整数序列，与 Python 的内建函数 sorted() 进行比对。
如果测试10000次都没有问题的话，则认为测试通过。
'''

import random

def rand():
    return [random.randint(1, 10000) for i in xrange(100)]

def main():
    packageName = raw_input("测试文件名（不带后缀名） ")
    
    exec "import " + packageName

    for round_ in xrange(10000):
        if round_ % 1000 == 0:
            print 100.0*round_/10000, "%"
        raw = rand()
        refer = sorted(raw)
        exec "test = " + packageName + ".sort(raw)"
        if refer != test:
            print "测试不通过"
            print "raw = ", raw
            print "refer = ", refer
            print "test = ", test
            exit(1)

    print "测试通过"
    exit(0)

if __name__ == "__main__":
    main()
