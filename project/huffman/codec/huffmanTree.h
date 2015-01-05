/* 哈夫曼树的 C++ 实现。
 *
 * 由于 Python 自身的性能问题，在这里我们决定使用 C++ 重写一次哈夫曼编码的过程
 * 。
 *
 * 这个程序完成如下工作：
 *  · 读取压缩文件的哈夫曼树，并构造出来。
 *  · 根据哈夫曼树，对压缩文件解压缩。
 *
 * 作者 aheadlead
 *
 */


#include <fstream>
#include <cstdlib>
#include <string>

#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

class HuffmanTree
{
    public:
        int key;
        int value;
        HuffmanTree * childs[2];
        HuffmanTree();
        ~HuffmanTree();
        void loadFromFile(char const * filename);

    private:
        void parseFromJsonCString(char * json);
        void parseFromJsonDocumentAtRoot(Document * Json);
        void parseFromJsonDocument(
                GenericValue<rapidjson::UTF8<char>, 
                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > * Json);
};

