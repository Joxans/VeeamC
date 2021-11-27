#pragma once
#include "Block.h"
#include "HashTypes.h"
#include "QueueManager.h"
#include <thread>

class BlocksHandler
{
	QueueManager<Block*> input;
	QueueManager<Block*> output;

	std::vector<std::thread*> threads;
	HashTypes hashType;
	bool isAborted;

	void run();

public:
	BlocksHandler(int, HashTypes);
	~BlocksHandler();

	void start();
	void stop();
	void abortProcess();

	void addUnhandledBlock(Block*);
	Block* getHandledBlock();
};
