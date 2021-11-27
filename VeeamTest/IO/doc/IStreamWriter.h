#pragma once
#include "Block.h"
#include "Header.h"
#include <iostream>

class IStreamWriter
{
public:
    virtual void writeHeader(Header*) {};
    virtual std::shared_ptr<char> toString(Header*) { return NULL; };

    virtual void writeBlock(Block*) = 0;
    virtual std::shared_ptr<char> toString(Block*) = 0;
};