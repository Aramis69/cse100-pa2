/* To hold the class i made for the nodes being used in the tree
 * File: DictionaryTrieNode.cpp
 *
 */
#include "DictionaryTrieNode.hpp"


DictionaryTrieNode::DictionaryTrieNode()
{   
    maxFreq = 0;
    value = 0; 
    endOfWord = false;
    freq = 0;
    left = nullptr;
    equal = nullptr;
    right = nullptr;
}


