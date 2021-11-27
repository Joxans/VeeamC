#pragma once
#include "Hasher.h"
#include "Block.h"
#include "BlocksHandler.h"
#include "StreamReader.h"
#include "StreamWriter.h" 
#include "HashTypes.h"
#include "Header.h"
#include <iostream>

class BaseProcessor
{
	int blockSize;
	int blocksCount;
	StreamReader* inputStream;
	StreamWriter* outputStream;

	BlocksHandler* blocksHandler;
	HashTypes hashType;

	bool isRun;
	bool isAborted;
	std::thread* producer;
	std::thread* consumer;

	void init();
	void process();
	void produce();
	void consume();

public:
	BaseProcessor(std::string, std::string, int, HashTypes);
	~BaseProcessor();

	bool run();
	void abortProcess();
};
