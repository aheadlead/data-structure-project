#!/usr/bin/env python
# coding=utf-8

'''
这是一个数据结构课程中，演示树的一个类。
开发环境：
OS X 10.10
Python 2.7.6
'''

__author__ = '魏宇蓝'

class Tree(object):
    '''
    类Tree描述了一棵树，也可以理解为描述了某棵树的根节点。
    对于这个根节点，可以有以下属性：
        parent          父亲
        childs          所有孩子的list
        left            前一个兄弟
        right           后一个兄弟
        content         这个节点的内容
        ID              这个节点的序号（用于人工索引）

    空树刻画为None。
    
    Python具备垃圾回收的机制，所以不提供销毁的方法。
    本对象不提供清空的方法，清空树可以简单的使用以下代码：
        dirtyTree = Tree()

    构造树：
    >>> A = Tree('A')
    >>> B = A.locate(A.insert(Tree('B')))
    >>> C = A.locate(A.insert(Tree('C')))
    >>> D = B.locate(B.insert(Tree('D')))
    >>> E = B.locate(B.insert(Tree('E')))
    >>> F = C.locate(C.insert(Tree('F')))
    >>> G = C.locate(C.insert(Tree('G')))
    >>> H = C.locate(C.insert(Tree('H')))
    >>> I = C.locate(C.insert(Tree('I')))
    >>> J = F.locate(F.insert(Tree('J')))
    >>> K = F.locate(F.insert(Tree('K')))
    >>> L = I.locate(I.insert(Tree('L')))
    >>> M = I.locate(I.insert(Tree('M')))
    >>> N = I.locate(I.insert(Tree('N')))
    >>> print A
    A(0)
    -----------
    |         |                                     
    B(1)      C(2)                                  
    ------    ----------------------                
    |    |    |          |    |    |                
    D(3) E(4) F(5)       G(6) H(7) I(8)             
              ------               -------------    
              |    |               |     |     |    
              J(9) K(10)           L(11) M(12) N(13)
    '''

    maxID = 0 # ID的最大值，添加新节点时会使用此ID。

    def __init__(self, content=None):
        self.parent = None
        self.childs = []
        self.left = None
        self.right = None
        self.content = content
        self.ID = Tree.maxID
        Tree.maxID = Tree.maxID+1

    def insert(self, subTree, offset=-1):
        '''
        将subTree插入到当前树的根节点。
        返回subTree的ID。
    
        offset参数是指定子树位置的，如果不给定offset的值，将作为最后一个孩子插入。
        如果给定了offset的值，那么子树将会被插入到childs的第offset个对象之前。
        函数认定subTree和本树不相交。
        
        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('Hua')
        >>> print A
        Hua(0)
        >>> B_ID = A.insert(Tree('JuHua'))
        >>> print A
        Hua(0)
        -
        |       
        JuHua(1)

        '''
        subTree.parent = self
        if offset != -1: # 提供了offset的值
            #  <- childs[0] <-> childs[1] <-> ...
            #  <- subTree <-> childs[0] <-> childs[1] <-> ...
            subTree.left, subTree.right = \
                    self.childs[offset].left, self.childs[offset]
            self.childs[offset].left = subTree
            self.childs.insert(offset, subTree)
        else: # 没提供offset的值
            if len(self.childs) == 0: # 插这颗子树之前还没孩子
                subTree.left = None
            else:   # 插这颗子树之前已经有了孩子
                subTree.left = self.childs[-1]
                self.childs[-1].right = subTree
            subTree.right = None
            self.childs.append(subTree)
        return subTree.ID

    def delete(self):
        '''
        删除自己。

        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> B = A.locate(A.insert(Tree('B')))
        >>> C = A.locate(A.insert(Tree('C')))
        >>> D = B.locate(B.insert(Tree('D')))
        >>> E = B.locate(B.insert(Tree('E')))
        >>> F = C.locate(C.insert(Tree('F')))
        >>> G = C.locate(C.insert(Tree('G')))
        >>> print A
        A(0)
        -----------
        |         |        
        B(1)      C(2)     
        ------    ------   
        |    |    |    |   
        D(3) E(4) F(5) G(6)
        >>> C.delete()
        >>> print A
        A(0)
        -
        |        
        B(1)     
        ------   
        |    |   
        D(3) E(4)
        '''
        if None != self.left and None != self.right:
            self.left.right, self.right.left = \
                    self.right, self.left
        elif None != self.left and None == self.right:
            self.left.right = None
        elif None == self.left and None != self.right:
            self.right.left = None
        if None != self.parent:
            self.parent.childs.remove(self)
            
    def __iter__(self):
        '''
        迭代子树的方法。

        若有这样一棵树root：（图中数字都是ID）

        这个方法使得本类可以这样调用：

        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> A.insert(Tree('B'))
        1
        >>> A.insert(Tree('C'))
        2
        >>> A.insert(Tree('D'))
        3
        >>> A.insert(Tree('E'))
        4
        >>> for child in A:
        ...     print child.ID, child.content
        1 B
        2 C
        3 D
        4 E

        '''
        return iter(self.childs)

    def levelOrderTraverse(self):
        '''
        层次遍历。

        返回一个遍历结果的list，内容物为子树。
        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> B = A.locate(A.insert(Tree('B')))
        >>> C = A.locate(A.insert(Tree('C')))
        >>> D = B.locate(B.insert(Tree('D')))
        >>> E = B.locate(B.insert(Tree('E')))
        >>> F = C.locate(C.insert(Tree('F')))
        >>> G = C.locate(C.insert(Tree('G')))
        >>> print A
        A(0)
        -----------
        |         |        
        B(1)      C(2)     
        ------    ------   
        |    |    |    |   
        D(3) E(4) F(5) G(6)
        >>> ret = A.levelOrderTraverse()
        >>> for subTree in ret:
        ...     print subTree.ID, subTree.content
        0 A
        1 B
        2 C
        3 D
        4 E
        5 F
        6 G

        '''
        queue = []
        result = []
        queue.append(self)
        while len(queue) != 0:
            frontTree = queue[0]
            map(queue.append, [child for child in frontTree])
            result.append(frontTree)
            queue = queue[1:]    # 去掉第一个元素
        return result

    def locate(self, findID):
        '''
        在本树中寻找ID为findID的对象。
        找不到返回None

        由于频繁调用levelOrderTraverse()方法，locate()方法的效率可能不会很高。
        因为这是演示目的的程序，所以没没有顾及性能问题。
        可以采用缓存（在树没有修改的前提下，不用重复做层次遍历），或者动态迭代器的方法实现。
        当然也可以使用二叉查找树的方法做个缓存，进一步提高效率，虽然这样感觉非常奇怪。（菊：这个程序到底是为了什么，233333）
        '''
        t = self.levelOrderTraverse()
        for tree in t:
            if tree.ID == findID:
                return tree 
        return None
         
    def __getitem__(self, findID):
        '''
        locate方法的别名。
        对于树A来说，寻找ID为findID的子树，可以使用locate()方法：
        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> B = A.locate(A.insert(Tree('B')))
        >>> C = A.locate(A.insert(Tree('C')))
        >>> D = B.locate(B.insert(Tree('D')))
        >>> E = B.locate(B.insert(Tree('E')))
        >>> F = C.locate(C.insert(Tree('F')))
        >>> G = C.locate(C.insert(Tree('G')))
        >>> print A
        A(0)
        -----------
        |         |        
        B(1)      C(2)     
        ------    ------   
        |    |    |    |   
        D(3) E(4) F(5) G(6)
        >>> findID = 4
        >>> print A.locate(findID).content
        E
        
        也可以使用这样的方法：
        >>> print A[4].content
        E
        '''
        return self.locate(findID)

    def __len__(self):
        '''
        获得树的元素的数目。
        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> B = A.locate(A.insert(Tree('B')))
        >>> C = A.locate(A.insert(Tree('C')))
        >>> D = B.locate(B.insert(Tree('D')))
        >>> E = B.locate(B.insert(Tree('E')))
        >>> F = C.locate(C.insert(Tree('F')))
        >>> G = C.locate(C.insert(Tree('G')))
        >>> print A
        A(0)
        -----------
        |         |        
        B(1)      C(2)     
        ------    ------   
        |    |    |    |   
        D(3) E(4) F(5) G(6)
        >>> print len(A)
        7
        >>> print len(C)
        3
        >>> print len(G)
        1
        '''
        return reduce(lambda count, subTree: count+len(subTree), [1]+self.childs)

    def depth(self):
        '''
        获得树的深度。
        >>> Tree.maxID = 0  # 这一行是为了方便通过文档测试，用户不要管这一行
        >>> A = Tree('A')
        >>> B = A.locate(A.insert(Tree('B')))
        >>> C = A.locate(A.insert(Tree('C')))
        >>> D = B.locate(B.insert(Tree('D')))
        >>> E = B.locate(B.insert(Tree('E')))
        >>> F = C.locate(C.insert(Tree('F')))
        >>> G = C.locate(C.insert(Tree('G')))
        >>> print A
        A(0)
        -----------
        |         |        
        B(1)      C(2)     
        ------    ------   
        |    |    |    |   
        D(3) E(4) F(5) G(6)
        >>> print A.depth()
        3
        >>> print C.depth()
        2
        >>> print G.depth()
        1
        '''
        return reduce(lambda maxDepth, subTree: max(maxDepth, 1+subTree.depth()), [1]+self.childs)

    def stringlize(self):
        '''
        将这颗树转换为人类可以阅读的字符串。
        然而，这个函数的代码可能不太适合人类阅读。
        '''
        if 0 == len(self.childs):  # 叶子节点
            return {'string' : ['|', str(self.content) + '(' + str(self.ID) + ')'], \
                    'maxWidth' : max(1, len(str(self.content) + '(' + str(self.ID) + ')'))}

        root = str(self.content) + '(' + str(self.ID) + ')'
        leavesHat = ''
        leaves = []

        ret = []
        for child in self.childs:
            ret.append(child.stringlize())
        
        # 求出孩子中最大的行数的数目
        lineNumber = reduce(lambda n, leavesRet: max(n, len(leavesRet['string'])), [0] + ret)
        leaves = ['' for num in range(lineNumber)]
        
        # 构造leavesHat
        for childStrs in ret:
            leavesHat = leavesHat + '-'*childStrs['maxWidth'] + '-'
        leavesHat = leavesHat[:-ret[-1]['maxWidth']]    # 去掉最后一个元素的大部分帽子
            
        # 填充leaves
        for childStrs in ret:
            for (index, childStr) in enumerate(childStrs['string']):
                childStr = childStr.ljust(childStrs['maxWidth'], ' ')
                leaves[index] = leaves[index] + childStr + ' '
            for index in range(len(childStrs['string']), lineNumber):
                leaves[index] = leaves[index]+' '*childStrs['maxWidth'] + ' '
        for index in range(len(leaves)):
            leaves[index] = leaves[index][:-1]

        return {'string' : ['|', root, leavesHat]+leaves, \
                'maxWidth' : reduce(lambda n, line: max(n, len(line)), [0] + leaves)}

    def __str__(self):
        return '\n'.join(self.stringlize()['string'][1:])

