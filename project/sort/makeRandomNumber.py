#!/usr/bin/env python
# coding=utf-8

'''一个生成随机数的小程序。

程序会在 sample 文件夹中生成10个文件：
    rand0.txt
    rand1.txt
    rand2.txt
    rand3.txt
    rand4.txt
    rand5.txt
    rand6.txt
    rand7.txt
    asc.txt
    desc.txt
每个文件中有 N 个随机整数。
前八个文件是随机顺序， asc.txt 是升序， desc.txt 是降序。
'''

__author__ = u"aheadlead"

import sys
import os
import random

N = 5000

def rand():
    ret = []
    for i in xrange(N):
        ret.append(random.randint(1, 10000))
    return ret

def main():
    if not os.path.exists("sample"):
        print "创建了一个文件夹 sample"
        os.mkdir("sample")

    # 生成前八个文件
    for i in xrange(8):
        filename = "sample/rand" + str(i) + ".txt"
        print "生成样本 " + filename
        with open(filename, "w") as hd:
            sample = rand()
            for number in sample:
                hd.write(str(number) + "\n")
    
    # 生成升序文件
    filename = "sample/asc.txt"
    print "生成样本 " + filename
    with open(filename, "w") as hd:
        sample = rand()
        sample.sort()
        for number in sample:
            hd.write(str(number) + "\n")
    
    # 生成降序文件
    filename = "sample/desc.txt"
    print "生成样本 " + filename
    with open(filename, "w") as hd:
        sample = rand()
        sample.sort(reverse=True)
        for number in sample:
            hd.write(str(number) + "\n")

if __name__ == "__main__":
    main()
