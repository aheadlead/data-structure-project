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

// 调试用函数，输出一棵树
void printtree(HuffmanTree * tree, int level)
{
    if (tree == NULL) return;
    for (int i=0; i<level; ++i) printf(" ");
    printf("%d\n", tree->key);
    printtree((tree->childs[0]), level+1);
    printtree((tree->childs[1]), level+1);
    fflush(stdout);
}

// 调试用函数，显示mapping
void printmapping()
{
    for (int i=0; i<256; ++i)
    {
        if (mapping[i].size() != 0)
        {
            printf("%d\t", i);
            for (vector<int>::iterator p=mapping[i].begin();
                    p!=mapping[i].end();
                    ++p)
            {
                printf("%d", *p);
            }
            printf("\n");
        }
    }
    fflush(stdout);
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
    while (!feof(file))
    {
        // TODO 这个 fread() 函数有潜在的性能问题。为了获得读取到的字符数目，我
        // 将原本的第二的参数与第三个参数进行了调换。因为对 fread 的行为不是太
        // 清楚，我担心 fread 会进行 BUFFERSIZE 次磁盘IO，这样会大大减慢读取速
        // 度。
        int buffersize = fread(buffer, 1, BUFFERSIZE, file);
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

    printf("%lu", bout.getBitLength());

    fclose(file);
    bout.close();
    fflush(stdout);

    return 0;
}
