#pragma once
#include "IStreamReader.h"
#include <fstream>
#include <iostream>

class StreamReader : public IStreamReader
{
    std::ifstream stream;
    int blockSize;
    int counter;
    int length;
        
public:
    StreamReader(std::string, int);
    ~StreamReader();

    int getLength();
    int getPosition();
    Block* getBlock() override;
    std::shared_ptr<char> getBlockBytes() override;
};