# 这是一个手写的 makefile 。
# automake 神马的太麻烦啦呀...
#
# 要用就直接make build就ok了

build: encoder decoder
	make encoder
	make decoder

encoder: encoder.o huffmanTree.o
	g++ encoder.o huffmanTree.o -o encoder -O2

decoder: decoder.o huffmanTree.o
	g++ decoder.o huffmanTree.o -o decoder -O2

encoder.o: encoder.cpp
	g++ -c encoder.cpp -O2

huffmanTree.o: huffmanTree.cpp huffmanTree.h
	g++ -c huffmanTree.cpp -O2

clean:
	-rm encoder
	-rm *.o

test: encoder
	#clear
	./encoder ../testfile ../testfile.tree.json
	xxd -b ../testfile.hfm
	
