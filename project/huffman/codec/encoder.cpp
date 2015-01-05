/* 哈夫曼编码器。
 *
 * 用法：
 * $ ./encoder [file] [tree]
 *
 * 本程序接受两个参数，这两个参数为两个文件的文件名。
 * 第一个文件名 [file] 是待编码的文件名称。
 * 第二个文件名 [tree] 是应用于待编码的文件的哈夫曼树，使用 json 存储的一个树。
 */

#include <iostream>
#include <string>
#include <vector>

#include "bitFile.h"
#include "huffmanTree.h"

#define BUFFERSIZE 32*1024*1024 // 32MB

void 
showUsage()
{
    printf("哈夫曼编码器\n"
           "用法：./encoder [file] [tree]\n"
           "\n"
           " file - 待编码的文件名称\n"
           " tree - 应用于待编码文件的哈夫曼树的文件名\n");
    return;
}

string filename, treeFilename;
unsigned char buffer[BUFFERSIZE];
vector<int> mapping[256];

void 
constructMapping(HuffmanTree * tree, vector<int> code)
{
    if (tree->key != -1) // 是叶子结点
    {
        mapping[tree->key] = code;
    }
    else // 不是叶子结点
    {
        code.push_back(0);
        if (NULL != tree->childs[0])
            constructMapping(tree->childs[0], code);

        code.pop_back();

        code.push_back(1);
        if (NULL != tree->childs[1])
            constructMapping(tree->childs[1], code);
    }
    return;
}

int
main(int argc, char ** argv)
{
    if (argc != 3) // 检查参数数量
    {
        showUsage();
        return 1;
    }
    else
    {
        filename = argv[1];
        treeFilename = argv[2];
    }

    // 输出两个文件名
    printf("%s : %s\n", filename.c_str(),
            treeFilename.c_str());

    // 载入哈夫曼树
    HuffmanTree tree;
    tree.loadFromFile(treeFilename.c_str());

    // 构造映射表
    // 映射表是将字符映射到一个二进制序列的表
    constructMapping(&tree, vector<int>());
    
    // 打开待编码的文件
    FILE *file = fopen(filename.c_str(), "rb");

    // 打开输出的文件
    oBitFile bout((filename + ".hfm").c_str());
    
    // 编码
    while (true)
    {
        int buffersize = fread(buffer, BUFFERSIZE, 1, file);
        for (int i=0; i<buffersize; ++i) // 枚举读入缓冲区的字符
        {
            unsigned char ch = buffer[i]; // 当前字符
            // 写入二进制串
            for (vector<int>::iterator p=mapping[ch].begin();
                    p!=mapping[ch].end();
                    ++p)
            {
                bout.writeNextBit(*p);
            }       
        }
    }

    fclose(file);
    bout.close();

    return 0;
}
