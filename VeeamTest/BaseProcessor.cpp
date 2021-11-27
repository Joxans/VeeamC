#include "BaseProcessor.h"
#include "Hasher.h"
#include "Block.h"
#include "BlocksHandler.h"
#include "StreamReader.h"
#include "StreamWriter.h" 
#include "HashTypes.h"
#include "Header.h"
#include <iostream>
#include <math.h>

BaseProcessor::BaseProcessor(std::string inFilePath, std::string outFilePath, int blockSize, HashTypes hashType)
{
    try
    {
        this->inputStream = new StreamReader(inFilePath, blockSize);
        this->outputStream = new StreamWriter(outFilePath);
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what();
        this->abortProcess();
        return;
    }
    this->hashType = hashType;
    this->blockSize = blockSize;
    this->isAborted = false;
    this->isRun = false;
    this->blocksCount = ceil(this->inputStream->getLength() / (blockSize + 0.0));
}

BaseProcessor::~BaseProcessor()
{
    if (!this->isAborted)
    {
        if (isRun)
        {
            delete this->producer;
            delete this->consumer;
            delete this->blocksHandler;
        }
        delete this->inputStream;
        delete this->outputStream;
    }
}


void BaseProcessor::init()
{
    Header* header = new Header();
    
    header->blocksCount = this->blocksCount;
    header->hashType = this->hashType;
    header->hashSize = Hasher::getHashSize(this->hashType);
    
    this->outputStream->writeHeader(header);
}

void BaseProcessor::process()
{
    int numCPU = std::thread::hardware_concurrency();
    this->blocksHandler = new BlocksHandler(numCPU == 0 ? 1 : numCPU, this->hashType);
    
    this->producer = new std::thread(&BaseProcessor::produce, this);
    this->consumer = new std::thread(&BaseProcessor::consume, this);
    
    this->isRun = true;
    this->producer->detach();
    
    this->blocksHandler->start();
    this->consumer->join();
}

void BaseProcessor::produce()
{
    Block* block;
    
    for (int i = 0; i < this->blocksCount; i++)
    {
        if (this->isAborted)
            std::abort();
        try
        {
            block = this->inputStream->getBlock();
            this->blocksHandler->addUnhandledBlock(block);
        }
        catch (std::out_of_range e)
        {
            this->isAborted = true;
            std::cout << "Block reading fail. Reading of input file are stoped. " << e.what() << std::endl;
            return;
        }
        catch (std::runtime_error e)
        {
            std::cout << e.what();
            return;
        }
    }
}

void BaseProcessor::consume()
{
    Block* block;
    
    for (int i = 0; i < this->blocksCount; )
    {
        if (this->isAborted)
            std::abort();
        
        block = this->blocksHandler->getHandledBlock();
        if (block != NULL)
        {
            i++;
            this->outputStream->writeBlock(block);
        }
    }
}

bool BaseProcessor::run()
{
    if (isAborted)
        return false;
    this->init();
    this->process();
    return !isAborted;
}

void BaseProcessor::abortProcess()
{
    this->isAborted = true;
    
    if (isRun)
    {
        if (this->producer != NULL)
            delete this->producer;
        if (this->blocksHandler != NULL)
        {
            this->blocksHandler->abortProcess();
            delete this->blocksHandler;
        }        
        if (this->consumer != NULL)
            delete this->consumer;
    }
}
