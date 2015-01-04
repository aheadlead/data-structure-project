# coding=utf-8

u'''此文件是一个实现拓扑排序的类。'''

__author__ = u"aheadlead"

u'''
这个拓扑排序是用于求关键路径的，所以返回结果不仅有排序结果 ret ，
还有一个顶点事件最早的发生时间 ve 。

拓扑排序是通过不断的找入度为零的顶点，从而形成一个序列的过程。

在拓扑排序的过程中，可以求得关键路径中关注的一个参数 ve 。
'''

import Queue

class TopologicSort(object):
    # 拓扑排序的参数 DG 是一个 DirectedGraph
    def __call__(self, DG):
        self.graph = DG

        # 计算所有顶点的入度
        inDegree = self.evaluateInDegree()
        
        # 排序结果存于 ret 中， ve 是个顶点事件最早的发生时间
        ret = []
        ve = dict([[vertex, 0] for vertex in self.graph])

        # 零入度顶点队列
        zeroInDegreeQ = Queue.Queue()
        for vertex in inDegree:
            if inDegree[vertex] == 0:
                zeroInDegreeQ.put(vertex)
        
        while not zeroInDegreeQ.empty():
            u = zeroInDegreeQ.get()
            ret.append(u)
            for v in self.graph[u]:
                inDegree[v] = inDegree[v]-1
                if inDegree[v] == 0:
                    zeroInDegreeQ.put(v)  
                if ve[u]+self.graph[u][v] > ve[v]:
                    ve[v] = ve[u]+self.graph[u][v]

        return (ret, ve)
                
    # 计算入度
    def evaluateInDegree(self):
        inDegree = dict([[vertex, 0] for vertex in self.graph])
        for u in self.graph:
            for v in self.graph[u]:
                inDegree[v] = inDegree[v]+1
        return inDegree
