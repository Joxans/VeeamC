#pragma once
#include "HashTypes.h"
#include <cstddef>
#include <iostream>

class Hasher
{
public:
    Hasher() {};
    static Hasher* getHasher(HashTypes);
    static int getHashSize(HashTypes);

    virtual std::shared_ptr<char> toString() { return NULL; };
    virtual std::shared_ptr<char> getHash(std::shared_ptr<char> input) { return NULL; };
    virtual bool verifyHash(std::shared_ptr<char> originData, std::shared_ptr<char> hash) { return false; };
    virtual ~Hasher() {}
};
