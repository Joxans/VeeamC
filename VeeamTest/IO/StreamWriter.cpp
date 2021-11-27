#include "StreamWriter.h"

StreamWriter::StreamWriter(std::string file)
{
    this->stream.open(file.data());
    this->blockSize = 0;

    if (!this->stream.good())
        throw std::invalid_argument("Cannot open output file.\n");
}

StreamWriter::~StreamWriter()
{
    if (this->stream.good())
        this->stream.close();
}

void StreamWriter::writeHeader(Header* header)
{
    std::shared_ptr<char> buffer = this->toString(header);
    this->stream.write(buffer.get(), this->blockSize);
}

void StreamWriter::writeBlock(Block* block)
{
    std::shared_ptr<char> buffer = this->toString(block);
    this->stream.write(buffer.get(), this->blockSize);
}

std::shared_ptr<char> StreamWriter::toString(Header* header)
{
    this->blockSize = sizeof(int) * 4;
    std::shared_ptr<char> result(new char[this->blockSize], std::default_delete<char[]>());
    int hashT = static_cast<std::underlying_type<HashTypes>::type>(header->hashType);

    memcpy(result.get(), &this->blockSize, sizeof(int));
    memcpy(result.get() + sizeof(int), &header->blocksCount, sizeof(int));
    memcpy(result.get() + sizeof(int) * 2, &hashT, sizeof(int));
    memcpy(result.get() + sizeof(int) * 3, &header->hashSize, sizeof(int));

    return result;
}

std::shared_ptr<char> StreamWriter::toString(Block* block)
{
    int hashLen = (int)strlen(block->hash.get()) + 1;
    int dataLen = (int)strlen(block->data.get()) + 1;
    this->blockSize = sizeof(int) * 3 + hashLen + dataLen;
    std::shared_ptr<char> result(new char[this->blockSize], std::default_delete<char[]>());

    memcpy(result.get(), &this->blockSize, sizeof(int));
    memcpy(result.get() + sizeof(int), &block->id, sizeof(int));
    memcpy(result.get() + sizeof(int) * 2, &block->originBlockSize, sizeof(int));
    memcpy(result.get() + sizeof(int) * 3, block->hash.get(), hashLen);
    memcpy(result.get() + sizeof(int) * 3 + hashLen, block->data.get(), dataLen);
    
    return result;
}
