#pragma once
#include "Hasher.h"
#include <boost/algorithm/hex.hpp>
#include <iostream>

template <class Th, typename Td>
class CommonHasher : public Hasher
{
    Th* hasher;
    Td digest;

public:
    CommonHasher();
    ~CommonHasher() override;

    std::shared_ptr<char> toString() override;
    std::shared_ptr<char> getHash(std::shared_ptr<char>) override;
    bool verifyHash(std::shared_ptr<char>, std::shared_ptr<char>) override;
};


template <class Th, typename Td>
CommonHasher<Th, Td>::CommonHasher()
{
    this->hasher = new Th();
}

template <class Th, typename Td>
CommonHasher<Th, Td>::~CommonHasher()
{
    delete hasher;
}

template <class Th, typename Td>
std::shared_ptr<char> CommonHasher<Th, Td>::toString()
{
    const auto charDigest = reinterpret_cast<const char*>(&(this->digest));
    std::shared_ptr<char> result(new char[sizeof(Td) * 2 + 2]{ '\0' }, std::default_delete<char[]>());
    boost::algorithm::hex(charDigest, charDigest + sizeof(Td), result.get());
    return result;
}

template <class Th, typename Td>
std::shared_ptr<char> CommonHasher<Th, Td>::getHash(std::shared_ptr<char> input)
{
    this->hasher->process_bytes(input.get(), strlen(input.get()));
    this->hasher->get_digest(this->digest);
    return this->toString();
}

template <class Th, typename Td>
bool CommonHasher<Th, Td>::verifyHash(std::shared_ptr<char> originData, std::shared_ptr<char> hash)
{
    return !strcmp(this->getHash(originData).get(), hash.get());
}
