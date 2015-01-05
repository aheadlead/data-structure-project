#include <iostream>
#include "bitFile.h"
//#include "huffmanTree.h"

using namespace std;

int main()
{
    //HuffmanTree tree;
    //char filename[] = "tree.json";
    //tree.loadFromFile(filename);

    //cout << tree.key << endl;
    //cout << tree.value << endl;

    //cout << tree.childs[0]->key << endl;
    //cout << tree.childs[0]->value << endl;
    
    oBitFile bout("binaryfile");

    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);

    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);

    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);

    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(1);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);
    bout.writeNextBit(0);

    bout.close();

    iBitFile bin("binaryfile");
    bin.setBitLength(32);
    for (int i=0; i<32; ++i)
    {
        printf("%d", bin.readNextBit());
    }
    printf("\n");

    return 0;
}
