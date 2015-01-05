# 这是一个手写的 makefile 。
# automake 神马的太麻烦啦呀...

encoder: encoder.o huffmanTree.o
	g++ encoder.o huffmanTree.o -o encoder -O2

encoder.o: encoder.cpp
	g++ -c encoder.cpp

huffmanTree.o: huffmanTree.cpp huffmanTree.h
	g++ -c huffmanTree.cpp

	
