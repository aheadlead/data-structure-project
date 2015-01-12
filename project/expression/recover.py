#!/usr/bin/env python
# coding=utf-8

import re

def precede(a, b):
    if a in ['+', '-']:
        return '<' if b in ['*', '/', '('] else '>'
    if a in ['*', '/']:
        return '<' if b in ['('] else '>'
    if a == '(':
        if b == ')':
            return '='
        if b == '#':
            raise "未闭合的括号（左括号）"
        return '<'
    if a == ')':
        if b == '(':
            raise "括号不匹配"
        return '>'
    if a == '#':
        if b == '#':
            return '='
        if b == ')':
            raise "未闭合的括号（右括号）"
        return '<'

if __name__ == '__main__':
    exp = raw_input()
    #raw_exp = '123+234*345*(456/567-678)'
    #exp = raw_exp

    # 把表达式的运算元与运算符分开
    exp = re.sub('(?P<OPT>\+|\-|\*|\/|\(|\))', '!\g<OPT>!', exp) # 将所有运算符两边加上'!'
    exp = exp.split('!') # 通过'!'分割字符串
    exp = [int(item) if item.isdigit() else item for item in exp] # 把字符串类型的数字转换成int类型的数字
    # [123, '+', 234, '*', 345, '(', 456, '/', 567, '-', 678, ')', '']
    exp = filter(lambda a: a != '', exp)    # 删除元素''

    OPND = []
    OPTR = ['#']
    exp.append('#')

    pitem = iter(exp)
    item = pitem.next()
    try:
        while True:
            print 'OPND: ', OPND
            print 'OPTR: ', OPTR
            print '当前元素: ', item,
            if type(item) is int:
                print ' 是运算元, 将压入栈OPND'
                OPND.append(item)
                item = pitem.next()
            else:
                print ' 是运算符, ',
                preceding = precede(OPTR[-1], item)
                if preceding == '<':
                    print '且OPTR栈顶运算符优先级小于当前运算符'
                    print '将压入栈OPTR'
                    OPTR.append(item)
                    item = pitem.next()
                elif preceding == '>':
                    print '且OPTR栈顶运算符优先级大于当前运算符'
                    print '将取OPND栈顶两元素进行计算'
                    opt = OPTR.pop()
                    b = OPND.pop()
                    a = OPND.pop()
                    OPND.append(eval(str(a)+opt+str(b)))
                elif preceding == '=':
                    print '且OPTR栈顶运算符优先级等于当前运算符'
                    print '这意味着是一对括号，弹掉'
                    OPTR.pop()
                    item = pitem.next()
            raw_input()
    except StopIteration, e:
        pass

    print '计算结果是', OPND[0]

