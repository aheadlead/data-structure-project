# coding=utf-8

u'''此文件实现了一个有向图的类。'''

__author__ = u"aheadlead"

u'''这个类存储了一个带权有向图。
利用 Python 的语法，我们可以使用字典建立一个图。
由于题目中对图的点数要求较小，所以在这里我们不考虑 Python 的性能问题。

首先，点在这个类中可以是任意可哈希的对象，这是应 Python 的字典所要求的。
字典是 Python 提供的一种 键-值（ Key-Value ） 型的数据类型。
通常，我们会使用数字或着一个字符串来标定一个点。

边是这个类所主要描述的内容，边的权可以是任意对象。

对于类 DirectedGraph 中，有一个成员是 graph ，是一个字典。
对于一个图G(V, E)，点集中所有的点都是 graph 的键。
而字典 graph 的所有的成员，也是一个字典。
为了方便描述，不妨设一条 有向边e ， 有向边e 是由 点1 指向 点2 的。
那么记为self.graph[1][2] = 1。
这里的权是1，这是为描述 点1 到 点2 有一条边。

此类的使用方法和传统的C语言风格的邻接矩阵是一样的。

这个类不支持多重边，但是修改成支持多重边的版本是简单的。

对于4个点的这样一个图：
    A --> B
    ^     ^
    |     |
    C <-- D
描述上图的字典 graph 是这样的：
    { 
      'A' : { 'B' : 1 },
      'B' : {},
      'C' : { 'A' : 1 },
      'D' : { 'B' : 1 , 'C', 1 },
    }
这里的权都描述为1。

这个类是对字典的重新封装。
'''

import json

class DirectedGraph(object):
    def __init__(self):
        self.graph = {}

    def addVertex(self, vertex):
        # 不会添加已有的点
        assert not self.graph.has_key(vertex), "此点已存在"
        self.graph[vertex] = {}

    def insertEdge(self, src, dst, weight=1):
        assert not self.graph[src].has_key(dst), "此边已存在"
        self.graph[src][dst] = weight

    def __getitem__(self, key):
        return self.graph[key]

    # 此函数仅可工作在图的点和边权可json化时
    def loadFromFile(self, filename):
        with open(filename, 'r') as f:
            self.graph = json.loads(''.join(f.readlines()))

    # 此函数仅可工作在图的点和边权可json化时
    def saveToFile(self, filename):
        with open(filename, 'w') as f:
            f.write(json.dumps(self.graph, sort_keys=True, indent=4,
                separators=(',', ': ')))
