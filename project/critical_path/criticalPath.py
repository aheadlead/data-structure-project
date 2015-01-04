# coding=utf-8

u'''关键路径的计算程序。'''

__author__ = u"aheadlead"

import copy

from directedGraph import DirectedGraph
from topologicSort import TopologicSort

class CriticalPath(object):
    def __call__(self, DG):
        self.graph = DG

        topsort = TopologicSort()

        # 求正向的情况
        forwardTopSequence, forwardVe = topsort(self.graph)
        # 总时长为最后一个时间完成的最早时间
        total = forwardVe[forwardTopSequence[-1]]
        
        # 这里用了一个小技巧，教材上是写了两段不同的拓扑排序（而且写得很丑陋）
        # ，事实上，可以这么做：将所拥有边反向，正常的进行一次拓扑排序（也就是
        # 带有最早完成时间的拓扑排序），对反向图求出结果后，把 ve 数组里面的每
        # 个元素，都被正向拓扑排序时得到的总时长减去即可。
        # 这样可以节省代码量。

        # 将边反向
        self.reversedGraph = DirectedGraph() # 新图
        for u in self.graph: # 枚举点
            self.reversedGraph.addVertex(u) # 将原图所有点添加到新图
        for u in self.graph: # 枚举边
            for v in self.graph[u]:
                # 当枚举到一条边时，在新图里面插入一条同权反向边
                self.reversedGraph.insertEdge(v, u, self.graph[u][v])

        # 求反向的情况
        backwardTopSequence, backwardVe = topsort(self.reversedGraph)
        # 减总时长
        backwardVe = {key:total-backwardVe[key] for key in backwardVe}
        
        # 求关键活动
        criticalEvent = {}
        for u in forwardVe:
            if forwardVe[u] == backwardVe[u]:
                criticalEvent[u] = forwardVe[u]

        return (criticalEvent, 
                (forwardTopSequence, forwardVe),
                (backwardTopSequence, backwardVe))
