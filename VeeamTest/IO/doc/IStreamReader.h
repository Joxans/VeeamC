#pragma once
#include "Block.h"
#include "Header.h"
#include <iostream>

class IStreamReader
{
public:
    virtual Header* getHeader() { return NULL; };
    virtual std::shared_ptr<char> getHeaderBytes() { return NULL; };

    virtual Block* getBlock() = 0;
    virtual std::shared_ptr<char> getBlockBytes() = 0;
};