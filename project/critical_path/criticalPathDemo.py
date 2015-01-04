#!/usr/sbin/env python
# coding=utf-8

u'''此文件用于演示关键路径的计算。
程序的第一个参数是个文件名，程序会从该文件中读取图，对其进行拓扑排序，并打印在
屏幕上。

用法：
$ ./topologicSortDemo.py graph.json
'''
__author__ = u"aheadlead"

import sys

from directedGraph import DirectedGraph
from criticalPath import CriticalPath

if __name__ == '__main__':
    if len(sys.argv) == 2:
        filename = sys.argv[1]
    else:
        raise Exception, "需要参数"

    g = DirectedGraph()
    g.loadFromFile(filename)

    cp = CriticalPath()
    criticalPath, forward, backward = cp(g)

    print u"关键路径 ", criticalPath
    print u"正向拓扑排序 ", forward
    print u"逆向拓扑排序 ", backward

