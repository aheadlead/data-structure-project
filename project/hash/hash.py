#!/usr/bin/env python
# coding=utf-8

u''' Hash 表应用
使用 Hash 表来实现一个身份证查找系统，对身份证号码进行 Hash 。

我们随机生成一个身份证信息文件 data.txt ，这里面包含了 131653 条身份信息记录，
每条身份记录包含邮箱地址、姓名、身份证号码，以空格隔开。身份记录之间以换行分割
。

如：
    woshizhangsan@gmail.com 张三 12345678901234567X


使用方法：
$ ./hash.py [file] 
程序会从文件 [file] 读入身份记录。（ file 的默认值是 data.txt ）
用户从控制台输入欲查询身份证号码，即可知道此身份证有没有出现在 [file] 中。
'''

__author__ = u"aheadlead"

from pprint import *
import sys

# 类BKDR哈希函数
def hashFn(string):
    ret = 0
    for ch in string:
        ret = ret*131 + ord(ch)
    return ret

if __name__ == "__main__":
    filename = 'data.txt'
    if len(sys.argv) == 2:
        filename = sys.argv[1]

    # 读入文件
    with open(filename, 'r') as h:
        data = [tuple(line.strip('\n').split(' ')) for line in h.xreadlines()]

    openingAddressHashTableLength = 150000
    openingAddressHashTable = [None] * openingAddressHashTableLength
    openingAddressHashTableRelocate = {}

    chainAddressHashTableLength = 10000
    chainAddressHashTable = [[] for i in xrange(chainAddressHashTableLength)]
    chainAddressHashTableRelocate = {}

    for index, record in enumerate(data):
        hashValue = hashFn(record[2])
        
        # 开放定址法
        oh = hashValue % openingAddressHashTableLength
        oRelocateCount = 0
        while openingAddressHashTable[oh] != None: # 确定位置 oh 没有元素
            oRelocateCount = oRelocateCount+1
            oh = (oh+1) % openingAddressHashTableLength
        openingAddressHashTable[oh] = record
        if oRelocateCount != 0:
            openingAddressHashTableRelocate[record[2]] = oRelocateCount

        # 链地址法
        ch = hashValue % chainAddressHashTableLength
        cRelocateCount = len(chainAddressHashTable[ch])
        chainAddressHashTable[ch].append(record)
        if cRelocateCount != 0:
            chainAddressHashTableRelocate[record[2]] = cRelocateCount
    
    print u"开放定址法的冲突情况"
    print u"冲突次数", len(openingAddressHashTableRelocate)
    pprint(openingAddressHashTableRelocate)

    print u"链定址法的冲突情况"
    print u"冲突次数", len(chainAddressHashTableRelocate)
    pprint(chainAddressHashTableRelocate)

    # 接受用户查询
    while True:
        idcard = raw_input(">>> ")
        
        hashValue = hashFn(idcard)
        print u" %(idcard)s 的哈希结果是 %(hashValue)d 。" % \
            { "idcard": idcard, \
              "hashValue": hashValue }

        # 开放定址法
        oh = hashValue % openingAddressHashTableLength
        while openingAddressHashTable[oh] != None and \
              openingAddressHashTable[oh][2] != idcard:
            oh = (oh+1) % openingAddressHashTableLength
        print u"使用开放定址法确定的地址是 %d 。" % (oh)
        
        if openingAddressHashTable[oh] == None:
            print u"没有找到这条身份信息。"
        else:
            print u"找到了这条身份证信息！"
            print u"姓名 " + openingAddressHashTable[oh][1].decode('utf-8')
            print u"邮箱地址 " + openingAddressHashTable[oh][0]
            print u"身份证号码 " + openingAddressHashTable[oh][2]

