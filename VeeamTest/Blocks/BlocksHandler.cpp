#include "BlocksHandler.h"
#include "Block.h"
#include "Hasher.h"
#include "HashTypes.h"
#include "QueueManager.h"

void BlocksHandler::run()
{
	Hasher* hasher = Hasher::getHasher(this->hashType);

	while (true)
	{
		Block* block = NULL;
		try
		{
			block = this->input.pop();
			if (block == NULL)
				return;
			else
			{
				block->hash = hasher->getHash(block->data);
				this->output.push(block);
			}

		}
		catch (std::exception e)
		{
			std::cout << e.what();
			this->abortProcess();
			return;
		}
	}
}

BlocksHandler::BlocksHandler(int threadsCount, HashTypes hashType)
{
	this->threads = std::vector<std::thread*>(threadsCount);

	for (int i = 0; i < threadsCount; i++)
	{
		this->threads[i] = new std::thread(&BlocksHandler::run, this);
	}

	this->hashType = hashType;
	this->isAborted = false;
}

BlocksHandler::~BlocksHandler()
{
	if (!isAborted)
	{
		for (int i = 0; i < this->threads.size(); i++)
		{
			delete this->threads[i];
		}
	}
}

void BlocksHandler::start()
{
	for (int i = 0; i < this->threads.size(); i++)
	{
		this->threads[i]->detach();
	}
}

void BlocksHandler::stop()
{
	this->input.push(NULL);
}

void BlocksHandler::abortProcess()
{
	this->isAborted = true;
	for (int i = 0; i < this->threads.size(); i++)
	{
		delete this->threads[i];
	}
}

void BlocksHandler::addUnhandledBlock(Block* block)
{
	this->input.push(block);
}

Block* BlocksHandler::getHandledBlock()
{
	return this->output.pop();
}
