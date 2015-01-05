#!/usr/bin/env python
# coding=utf-8

'''根据一个文件生成对应的哈夫曼树的程序。'''

import sys
import json

from huffmanTree import *

buffersize = 32*1024*1024 # 32MB

if __name__ == "__main__":
    if len(sys.argv) == 2:
        filename = sys.argv[1]
    else:
        sys.stderr.write("no input file.\n")
        sys.exit(1)

    hg = HuffmanTreeGenerator()

    with open(filename, 'rb') as fhd:
        while True:
            buf = fhd.read(buffersize)
            if len(buf) == 0: # 文件读完了
                break
            map(hg.insertCharacter, buf)

    print json.dumps(hg())

