#include "Hasher.h"
#include "CommonHasher.h"
#include <cstddef>
#include <iostream>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>

Hasher* Hasher::getHasher(HashTypes hashType)
{
	switch (hashType)
	{
	case HashTypes::SHA1:
		return new CommonHasher<boost::uuids::detail::sha1, boost::uuids::detail::sha1::digest_type>();
	case HashTypes::MD5:
		return new CommonHasher<boost::uuids::detail::md5, boost::uuids::detail::md5::digest_type>();
	default:
		return new CommonHasher<boost::uuids::detail::md5, boost::uuids::detail::md5::digest_type>();
	}
}

int Hasher::getHashSize(HashTypes hashType)
{
	switch (hashType)
	{
	case HashTypes::SHA1:
		return sizeof(boost::uuids::detail::sha1::digest_type);
	case HashTypes::MD5:
		return sizeof(boost::uuids::detail::md5::digest_type);
	default:
		return sizeof(boost::uuids::detail::md5::digest_type);
	}
}
