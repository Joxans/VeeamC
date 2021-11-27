#include <iostream>
#include "BaseProcessor.h"
using namespace std;

int main()
{
    std::string input;
    std::string output;
    int blocksSize;
    int hashType;
    
    cout << "!!! Welcome to the data hashing program !!!" << endl;
    cout << "Input file path: ";
    cin >> input;
    cout << "Output file path: ";
    cin >> output;
    cout << "Data block size: ";
    cin >> blocksSize;
    cout << "Hash functions:" << endl;
    cout << "\t 1. SHA1" << endl;
    cout << "\t 2. MD5" << endl;
    cout << "Input an index of hash function: ";
    cin >> hashType;
    cout << endl;
    
    BaseProcessor processor = BaseProcessor(input, output, blocksSize, hashType == 1 ? HashTypes::SHA1 : HashTypes::MD5);
    bool result = processor.run();
    
    if (result)
        cout << "Hashing was successful" << endl << endl;
    else
        cout << "There is some error with hashing" << endl << endl;
    
    return 0;
}
