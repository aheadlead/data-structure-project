/* 二进制文件按位操作库。
 *
 * 适用于哈夫曼编码的二进制文件的读写库。
 */

#include <cstdio>
#include <cassert>

#define bFBUFFERSIZE 32*1024*1024 // 32MB

class BaseBitFile
{
    public:
        BaseBitFile()
        {
            this->buffer = new unsigned char [bFBUFFERSIZE];
        }

        ~BaseBitFile()
        {
            delete this->buffer;
        }


        // 方法 setBitLength 用于设置这个文件的长度。
        //
        // 由于一个二进制序列存到一个文件里面的最小单位是字节，所以一个文件的二
        // 进制位的数量是 8 的倍数。所以这会带来一个问题，诸如 10100 这个二进制
        // 序列，它的实际长度是 5 。但是存到文件里面就会变成 10100000 ，因为一
        // 个文件的存储是以字节为单位的，所以在后面补了三个零。所以对于一个二
        // 进制文件，我们没有办法从这个二进制文件里面确定这个文件所存储的二进制
        // 序列的长度。你需要手动指定它的长度。
        void setBitLength(unsigned int bitLength)
        {
            // 文件的长度不会比二进制序列的长度短
            assert(this->bitLength >= bitLength); 

            this->bitLength = bitLength;
            return;
        }
        size_t getBitLength()
        {
            return this->bitLength;
        }

        void close()
        {
            fclose(this->hd);
            return;
        }

    protected:
        FILE * hd;
        size_t bitLength;
        unsigned char * buffer;
        unsigned int bufferpos;
        unsigned char byte; // 当前处理的字节
        unsigned int bytepos; // 当前处理字节的位置
};

class iBitFile : public BaseBitFile
{
    public:
        iBitFile(char const * filename) : BaseBitFile()
        {
            this->bufferpos = bFBUFFERSIZE;
            this->bytepos = 8;
            this->open(filename);
        }

        void open(char const * filename)
        {
            this->hd = fopen(filename, "rb+");
            if (this->hd == NULL)
                perror("错误 ");

            // 读取实际的文件大小
            fseek(this->hd, 0, SEEK_END);
            this->bitLength = 8*ftell(this->hd);
            fseek(this->hd, 0, SEEK_SET);
            return;
        }

        // 读取下一段缓冲区
        //
        // 为了提高性能，顺序读取和顺序写入文件使用了缓冲区。读取时，文件按块读
        // 取；写入时，文件按块写入。
        void readNextBuffer()
        {
            fread(this->buffer, bFBUFFERSIZE, 1, this->hd);
            this->bufferpos = 0;
        }

        inline int readNextBit()
        {
            int ret = 0;
            if (this->bytepos == 8) // 如果当前字节的 8 个位都读完了
            {
                if (this->bufferpos == bFBUFFERSIZE) // 如果当前缓冲区已读完
                {
                    this->readNextBuffer();
                }
                this->byte = this->buffer[this->bufferpos];
                this->bytepos = 0;

                this->bufferpos++;
            }

            // 开始读取
            ret = this->byte & 0x01;
            this->byte = this->byte >> 1;
            this->bytepos++;

            return ret;
        }
};

class oBitFile : public BaseBitFile
{
    public:
        oBitFile(char const * filename) : BaseBitFile()
        {
            this->bufferpos = 0;
            this->bitLength = 0;
            this->bytepos = 0;
            this->byte = 0x00;
            this->open(filename);
        }

        void open(char const * filename)
        {
            this->hd = fopen(filename, "wb+");
            if (this->hd == NULL)
                perror("错误 ");
            return;
        }

        // 写入本段缓冲区
        //
        // 为了提高性能，顺序读取和顺序写入文件使用了缓冲区。读取时，文件按块读
        // 取；写入时，文件按块写入。
        void writeNextBuffer(size_t length=bFBUFFERSIZE)
        {
            fwrite(this->buffer, length, 1, this->hd);
            this->bufferpos = 0;
        }

        inline void writeNextBit(int bit)
        {
            if (this->bytepos == 8) // 如果当前字节的 8 个位都写完了
            {
                this->buffer[this->bufferpos] = this->byte;
                this->bufferpos++;
                if (this->bufferpos == bFBUFFERSIZE) // 如果当前缓冲区已写满
                {
                    this->writeNextBuffer();
                }
                this->byte = 0x00;
                this->bytepos = 0;
            }

            // 开始写入
            this->byte = this->byte | (bit << (this->bytepos));
            this->bytepos++;
            this->bitLength++;

            return;
        }

        void close()
        {
            // 把缓冲区没写完的内容写完
            fwrite(this->buffer, this->bufferpos, 1, this->hd);
            // 把缓冲字节没写完的内容写入
            fwrite(&(this->byte), 1, 1, this->hd);

            fclose(this->hd);
        }
};
