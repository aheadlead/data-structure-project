# coding=utf-8

'''哈夫曼树的类。'''

__author__ = u"aheadlead"

import json
import heapq

'''类 HuffmanTree 提供了一个对哈夫曼树的简单的封装。

哈夫曼树中的节点可以分为两种，一种是叶子结点，另一种是非叶子节点。

叶子节点存放的一个 key-value 对，key 是一个字符， value 则是这个字符的权重。在
这里我们的字符均为 ASCII 字符，字符的权重即是这个 ASCII 字符在文件中出现的次数
。

非叶子节点则是两棵树的父亲，这两颗树可能是两个叶子结点，也有可能是一个叶子结点
和一颗以非叶子结点为根节点的树，也有可能是两颗以非叶子结点为根节点的树。对于非
叶子结点，我们把它的 key 定义为 None 。这样可以区分是不是叶子结点。
'''

class HuffmanTree(dict):
    def __init__(self, key=None, value=0):
        self["key"] = key
        self["value"] = value
        self["childs"] = (None, None) # 对应两个孩子节点

    # 为了实现用堆对哈夫曼树的操作，这里特别设定。
    #  heapq 库对于对象的比较，是使用了小于这个关系比较，所以在这里我们用__lt__
    # 来定制类。我们要的是一个小根堆，所以可以在__lt__这个方法里面写个小于比较
    # 的关系。
    def __lt__(self, anotherTree):
        return self["value"] < anotherTree["value"]


'''类 HuffmanTreeGenerator 是一个生成哈夫曼树的生成器。

成员 mapping 是一个由 ASCII 字符编码到出现次数的映射（dict）。
注意， mapping 的 key 是个数字，而不是个字符，这是为了方便导出哈夫曼树的 json
文件而设计的。
'''
class HuffmanTreeGenerator(object):
    def __init__(self):
        self.mapping = {i:0 for i in range(256)} # 覆盖 ASCII 的区间

    def insertCharacter(self, ch):
        self.mapping[ord(ch)] = self.mapping[ord(ch)]+1

    def generate(self):
        # 将 self.mapping 转化为一片森林。
        forest = [HuffmanTree(key=key, value=value) \
                for key, value in self.mapping.iteritems() if value != 0]
        heapq.heapify(forest) # 建立堆
        
        while len(forest) > 1: # 建立哈夫曼树的终止条件是森林里面只剩一颗树
            # 在森林中取两棵树
            treeA = heapq.heappop(forest)
            treeB = heapq.heappop(forest)
            
            # 合并
            treeNew = HuffmanTree(key=None, value=treeA["value"]+treeB["value"])
            treeNew["childs"] = (treeA, treeB)

            # 放回森林
            heapq.heappush(forest, treeNew)

        # 返回哈夫曼树
        return forest[0]

    def __call__(self):
        return self.generate()

