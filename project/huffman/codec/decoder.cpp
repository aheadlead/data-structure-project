/* 哈夫曼解码器。
 *
 * 用法：
 * $ ./encoder [file] [tree] [bitlength]
 *
 * 本程序接受三个参数，前两个参数为两个文件的文件名。
 * 第一个文件名 [file] 是待解码的文件名称。
 * 第二个文件名 [tree] 是应用于待解码的文件的哈夫曼树，使用 json 存储的一个树。
 *
 * 第三个参数是指待解码的文件的比特位的数量。
 *
 * 注意， [file] 必须以 ".hfm" （不含引号）结尾。
 *
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
    printf("哈夫曼解码器\n"
           "用法：./encoder [file] [tree] [bitLength]\n"
           "\n"
           " file - 待解码的文件名称\n"
           " tree - 应用于待解码文件的哈夫曼树的文件名\n"
           " bitlength - 待解码的文件的比特位的数量\n"
           "\n"
           "注意：file 必须以 \".hfm\" （不含引号）结尾。\n");
    return;
}

// 输入文件的名称 和 输入文件的对应树的文件的名称
string filename, treeFilename; 
size_t bitLength; // 输入文件的比特位数量

unsigned char buffer[BUFFERSIZE]; // 输出文件的缓冲区
unsigned int bufferpos = 0; // 缓冲区指针
vector<int> mapping[256]; // 映射表（未使用）

FILE * file; // 输出文件的指针

// 把 buffer 写入到文件
inline void
commitBuffer(size_t length)
{
    fwrite(buffer, length, 1, file);    
}

// 写入一个字符到 buffer
void
writeToBuffer(unsigned char ch)
{
    buffer[bufferpos] = ch;
    bufferpos++;
    if (bufferpos == BUFFERSIZE) // 缓冲区满了
    {
        commitBuffer(BUFFERSIZE);
        bufferpos = 0;
    }
}

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
    if (argc != 4) // 检查参数数量
    {
        showUsage();
        return 1;
    }
    else
    {
        filename = argv[1];
        // 判断文件名的后缀是不是 ".hfm"
        if (string(".hfm") != filename.substr(filename.length()-4, 4))
        {
            fprintf(stderr, "输入文件的后缀不是 .hfm 。\n");
            return 1;
        }
        treeFilename = argv[2];
        sscanf(argv[3], "%lu", &bitLength);
    }

    // 载入哈夫曼树
    HuffmanTree tree;
    tree.loadFromFile(treeFilename.c_str());

    // 构造映射表
    // 映射表是将字符映射到一个二进制序列的表
    constructMapping(&tree, vector<int>());
    
    // 打开待解码的文件
    iBitFile bin((filename).c_str());

    // 打开输出的文件
    // file 定义在了本文件头部，为了方便函数 commitBuffer 而调整。
    file = fopen((filename.substr(0, filename.length()-4)).c_str(), "wb");
    
    // 解码
    HuffmanTree * p = &tree;
    for (size_t i=0; i<bitLength; ++i)
    {
        int bit = bin.readNextBit();
        p = p->childs[bit];
        if (p == NULL)
        {
            fprintf(stderr, "待解码文件和树文件似乎不是对应的。");
            return 1;
        }
        if (p->key != -1)
        {
            writeToBuffer((unsigned char)p->key);
            p = &tree;
        }
    }

    commitBuffer(bufferpos);

    fclose(file);
    bin.close();
    fflush(stdout);

    return 0;
}


