#!/usr/bin/env python
# coding=utf-8

u'''
测试拓扑排序的一个演示程序。
程序的第一个参数是个文件名，程序会从该文件中读取图，对其进行拓扑排序，并打印在
屏幕上。

用法：
$ ./topologicSortDemo.py graph.json
'''

import sys

from directedGraph import DirectedGraph
from topologicSort import TopologicSort

if __name__ == '__main__':

    if len(sys.argv) == 2:
        filename = sys.argv[1]
    else:
        raise Exception, "需要参数"

    g = DirectedGraph()
    g.loadFromFile(filename)

    t = TopologicSort(g)
    ret, ve = t.do()

    print "ret = ", ret
    print "ve = ", ve

