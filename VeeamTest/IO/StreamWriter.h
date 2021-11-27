#pragma once
#include "IStreamWriter.h"
#include <fstream>
#include <iostream>

class StreamWriter : public IStreamWriter
{
    std::ofstream stream;
    int blockSize;

public:
    StreamWriter(std::string);
    ~StreamWriter();

    void writeHeader(Header*) override;
    std::shared_ptr<char> toString(Header*) override;
    void writeBlock(Block*) override;
    std::shared_ptr<char> toString(Block*) override;
};