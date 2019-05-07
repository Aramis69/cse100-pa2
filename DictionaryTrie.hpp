/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include "DictionaryTrieNode.hpp"


using namespace std;
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 */
/*regular comparator for priority que*/
struct comparePair{
          bool operator()(const pair<unsigned int, string> & p1,
                          const pair<unsigned int, string> & p2){
              if(p1.first == p2.first){
                  if((p1.second).compare(p2.second) < 0 ){
                      return false;
                  }
                  else{
                      return true;
                  }
              }
              else{
                  return p1.first < p2.first;
              }
         }
      };


/*min comparator for priority que*/  
struct comparePairMin{
          bool operator()(const pair<unsigned int, string> & p1,
                          const pair<unsigned int, string> & p2){
              if(p1.first == p2.first){
                  if((p1.second).compare(p2.second) < 0 ){
                      return true;
                  }
                  else{
                      return false;
                  }
              }
              else{
                  return p1.first > p2.first;
              }
         }
      };


class DictionaryTrie
{ 
public:

  DictionaryTrieNode * root;
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /** 
   * Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string). This might be useful for testing
   * when you want to test a certain case, but don't want to
   * write out a specific word 300 times.
   */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise. */
  bool find(std::string word) const;

  /* 
   * Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Return up to num_completions of the most frequent completions
   * of the pattern, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The pattern itself might be included in the returned words if the pattern
   * is a word (and is among the num_completions most frequent completions
   * of the pattern)
   */
  std::vector<std::string>
  predictUnderscore(std::string pattern, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:

    //helper method to recursivly find completions to prefix
    void findWords(DictionaryTrieNode* mov, string pre, unsigned int num);

    //helper method for predict underscore
    void findUnd(DictionaryTrieNode* mov);
    
    /*starts from a node and checks if the word is completed*/
    unsigned int completeWord(string word, DictionaryTrieNode*here, 
                            unsigned int x);
  
    /*function recursively inserts into trie*/
    bool insertHelp(DictionaryTrieNode* mov,unsigned int i,string word,
                    unsigned int freq);

    //sets max value at passed in node
    void setMax(DictionaryTrieNode* mov); 

    //helper method to delete a Trie tree
    static void deleteAll(DictionaryTrieNode* n);
    
    /*was used for unoptimized insert*/
    priority_queue<pair<unsigned int,string>,vector<pair<unsigned int,string>>,
                comparePair> pairs;

    /*min priority que*/
    priority_queue<pair<unsigned int,string>,vector<pair<unsigned int,string>>,
                comparePairMin> minPairs;
    
    /*stores potential underscore fillers*/
    vector<DictionaryTrieNode*> potentialComp;

};

#endif // DICTIONARY_TRIE_H
