#!/usr/bin/env python
# coding=utf-8

'''
这只是一个演示二叉树的先序、中序、后序遍历的一个简单的程序。
'''

def preOrderTraverse(tree, nodeNumber):
    '''
    先序遍历
    >>> D = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    >>> print preOrderTraverse(D, 1)
    [1, 2, 4, 8, 5, 3, 6, 7]
    '''
    try:
        ret = [tree[nodeNumber]]
    except:
        return []
    ret = ret + preOrderTraverse(tree, nodeNumber*2)
    ret = ret + preOrderTraverse(tree, nodeNumber*2+1)
    return ret

def inOrderTraverse(tree, nodeNumber):
    '''
    中序遍历
    >>> D = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    >>> print inOrderTraverse(D, 1)
    [8, 4, 2, 5, 1, 6, 3, 7]
    '''
    try:
        ret = [tree[nodeNumber]]
    except:
        return []
    ret = inOrderTraverse(tree, nodeNumber*2) + ret
    ret = ret + inOrderTraverse(tree, nodeNumber*2+1)
    return ret

def postOrderTraverse(tree, nodeNumber):
    '''
    后序遍历
    >>> D = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    >>> print postOrderTraverse(D, 1)
    [8, 4, 5, 2, 6, 7, 3, 1]
    '''
    try:
        ret = [tree[nodeNumber]]
    except:
        return []
    ret = postOrderTraverse(tree, nodeNumber*2) + postOrderTraverse(tree, nodeNumber*2+1) + ret
    return ret

if __name__ == "__main__":  
    import doctest
    doctest.testmod()
    
    D = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    print preOrderTraverse(D, 1)
    print inOrderTraverse(D, 1)
    print postOrderTraverse(D, 1)
