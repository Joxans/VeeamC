#pragma once
#include <iostream> 

class Block
{
public:
    int id;
    int originBlockSize;
    std::shared_ptr<char> hash;
    std::shared_ptr<char> data;
};