#!/usr/bin/env python
# coding=utf-8

u'''
测试文件。

输出一个图文件。
'''

import sys

from directedGraph import DirectedGraph

if __name__ == '__main__':
    g = DirectedGraph()
    g.addVertex('A')
    g.addVertex('B')
    g.addVertex('C')
    g.addVertex('D')
    g.insertEdge('A', 'B')
    g.insertEdge('A', 'D')
    g.insertEdge('A', 'C')
    g.insertEdge('B', 'D')
    g.insertEdge('C', 'D')
    g.saveToFile('testgraph.json')
