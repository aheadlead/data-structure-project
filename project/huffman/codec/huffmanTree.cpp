/* 哈夫曼树的 C++ 实现。
 *
 * 由于 Python 自身的性能问题，在这里我们决定使用 C++ 重写一次哈夫曼编码的过程
 * 。
 *
 * 作者 aheadlead
 *
 */

#include <fstream>
#include <cstdlib>
#include <string>

#include "rapidjson/document.h"

#include "huffmanTree.h"

using namespace std;
using namespace rapidjson;

HuffmanTree::HuffmanTree()
{
    this->key = 0;
    this->value = 0;
    this->childs[0] = NULL;
    this->childs[1] = NULL;
}

HuffmanTree::~HuffmanTree()
{
    if (NULL != this->childs[0])
        delete this->childs[0];
    if (NULL != this->childs[1])
        delete this->childs[1];
}

// 方法 loadFromFile 是将一颗 json 形式的树，从文件读入，再调用
// parseFromJsonCString 解析成树的方法。
// 第一个参数就是要读取的文件名。
void HuffmanTree::loadFromFile(char const * filename)
{
    fstream fin(filename, ios::in | ios::binary);

    // 获得文件大小
    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.seekg(0, fin.beg);

    char * jsonTree; // jsonTree 是 json 形式的哈夫曼树
    jsonTree = new char[length];
    
    // 读入文件
    fin.read(jsonTree, length);

    this->parseFromJsonCString(jsonTree);

    // 谨防内存泄漏，虽然也没多大
    delete jsonTree;
    fin.close();
}

// 方法 parseFromJsonCString 是将一颗存于 C 风格的字符串的 json 形式的树，
// 解析成树的方法。
void HuffmanTree::parseFromJsonCString(char * json)
{
    Document d;
    d.Parse(json);
    this->parseFromJsonDocumentAtRoot(&d);
}

// 方法 parseFromJsonDocumentAtRoot 是将一颗存于 rapidJson 的 Document 对象的
// 树解析成树的方法。但是本方法只处理根节点，因为参数是一个 Document 对象的指针
// 。
void HuffmanTree::parseFromJsonDocumentAtRoot(Document * Json)
{
    this->key = (*Json)["key"].GetInt();
    this->value = (*Json)["value"].GetInt();
        
    if (!(*Json)["childs"][0].IsNull())
    {
        this->childs[0] = new HuffmanTree();
        this->childs[0]->parseFromJsonDocument(&((*Json)["childs"][0]));
    }
    else
        this->childs[0] = NULL;

    if (!(*Json)["childs"][1].IsNull())
    {
        this->childs[1] = new HuffmanTree();
        this->childs[1]->parseFromJsonDocument(&((*Json)["childs"][1]));
    }
    else
        this->childs[1] = NULL;
}

// 方法 parseFromJsonDocument 是将一颗存于 rapidJson 的 Document 对象的
// 树解析成树的方法。但是本方法是由方法 parseFromJsonDocument 调用的，所以本方
// 法只处理非根节点。本方法的参数不是 Document 类型的，因为我不是很熟悉
// rapidJson 的内部实现，只能暂时这么处理。
void HuffmanTree::parseFromJsonDocument(
        GenericValue<rapidjson::UTF8<char>, 
        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > * Json)
{
    if ((*Json)["key"].IsNull())
        this->key = -1;
    else
        this->key = (*Json)["key"].GetInt();
    this->value = (*Json)["value"].GetInt();
        
    if (!(*Json)["childs"][0].IsNull())
    {
        this->childs[0] = new HuffmanTree();
        this->childs[0]->parseFromJsonDocument(&((*Json)["childs"][0]));
    }
    else
        this->childs[0] = NULL;

    if (!(*Json)["childs"][1].IsNull())
    {
        this->childs[1] = new HuffmanTree();
        this->childs[1]->parseFromJsonDocument(&((*Json)["childs"][1]));
    }
    else
        this->childs[1] = NULL;
}

