/* To hold the class i made for the nodes being used in the tree
 * File: DictionaryTrieNode.hpp
 *
 */

#ifndef DICTIONARY_TRIE_NODE_HPP
#define DICTIONARY_TRIE_NODE_HPP


using namespace std;

class DictionaryTrieNode{

    public:
        bool endOfWord;
        unsigned int freq;
        char value;       
        unsigned int maxFreq;
    
        DictionaryTrieNode* left;       
        DictionaryTrieNode* equal;       
        DictionaryTrieNode* right;       

        DictionaryTrieNode();

        
};


#endif //DictionaryTrieNode


