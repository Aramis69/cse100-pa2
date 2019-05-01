#include "DictionaryTrie.hpp"


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
    root = nullptr;
}

/** 
 * Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string). This might be useful for testing
 * when you want to test a certain case, but don't want to
 * write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    //if no word to insert
    if(word.empty()){
        return false;
    }
    //to access word indicies
    unsigned int i=0;
    //handle root case
    if(root == nullptr){
        root = new DictionaryTrieNode();
        root->value = word[i];
    }

    //to move through tree  
    DictionaryTrieNode* move = root;
    //loop to find position of last char in prefix
    while(true){

        //if current char is less than node
        if(word[i] < move->value){
 
            //if left is null insert
            if(move->left == nullptr){
                //insert new node with current char val
                move->left  = new DictionaryTrieNode();
                move = move->left;
                move->value = word[i];
                //will move to newley created node after this
            }   
            else{     
                //move to left node
                move = move->left;
            }
        }
        //if current char is greater than node
        else if(move->value < word[i]){
            //if right is null
            if(move->right == nullptr){
                move->right  = new DictionaryTrieNode();
                move = move->right;
                move->value = word[i];
            }
            else{        
                move = move->right;
            }
        }
        else{
        //if current character is equal to node
            //if move is on the node containing last char of pref
            if(i == (word.length()-1)){
                //if it was in container but not set
                if(move->endOfWord == true){
                    return false;    
                }
                //set end node values
                move->endOfWord = true;
                move->freq = freq;
                return true;
            }
            else{   
            //current i is same char as node

                //if the next equal is null
                if(move->equal == nullptr){
                    //create node for next char at equal position;
                    move->equal = new DictionaryTrieNode();
                    move = move->equal;
                    move->value = word[i+1];
                    i = i+1;
                    //move will then go to this new node
                }
                else{
                    //when there is still chars in word
                    move = move->equal; 
                    i = i+1;
                }
            }

        }
    }
    return false;
}


/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
    //if word is empty
    if(word.length() == 0){
        return false;
    }
    if(root == nullptr){
        return false;
    }
    //to iterate through tree
    DictionaryTrieNode* move = root;

    
    unsigned int i = 0;
    //loop to find position of last char in prefix
    while(i < (word.length())){
            
        //if current char is less than node
        if(word[i] < move->value){
            move = move->right;
        }
        //if current char is greater than node
        else if(move->value < word[i]){        
            move = move->left;
        }
        //if current character is equal to node
        else{
            //if move is on the node containing last char of pref
            if(i == (word.length()-1)){
                i++;   
            }
            else{
                move = move->equal; 
                i++;
            }
        }

        //if the node moved to is null
        if(move == nullptr){
            return false;
        }
    }
    //return status of this node. marked as word or not
    return move->endOfWord;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{   
    //holds strings i will return
    vector<string> myWords;
    //if the tree has no root
    if(root == nullptr){
        return myWords;
    }
 
    //start at root
    DictionaryTrieNode* move = root;
    
    unsigned int i = 0;
    //loop to find position of last char in prefix
    while(i < (prefix.length())){
            
        //if current char is less than node
        if(prefix[i] < move->value){
            move = move->right;
        }
        //if current char is greater than node
        else if(move->value < prefix[i]){        
            move = move->left;
        }
        //if current character is equal to node
        else{
            //if move is on the node containing last char of pref
            if(i == (prefix.length()-1)){
                i++;   
            }
            else{
                move = move->equal; 
                i++;
            }
        }

        //if the node moved to is null
        if(move == nullptr){
            return myWords;
        }
    }
    //handle if prefix is a word
    if(move->endOfWord){
        //make a pair of the prefix and place in pairs
        pair<unsigned int,string> word = make_pair(move->freq,prefix);      
        pairs.push(word);
    }
    //find other words from current node
    findWords(move->equal,prefix);

    //move from pairs to myWord vector
    for(unsigned int x=0; x < num_completions; x++){
        //if num_completions > amount of competions in pairs        
        if(pairs.empty()){
            return myWords;
        }
        //take top element and insert into vector then remove from que
        pair<unsigned int, string> top = pairs.top();
        myWords.push_back(top.second);
        pairs.pop(); 
    }
    while(!(pairs.empty())){
        pairs.pop();
    }
    
    return myWords;
}
    
void DictionaryTrie::findWords(DictionaryTrieNode* mov, string pre){ 

    if(mov == nullptr){
        return;
    }
    
    if(mov->endOfWord){
        
        pair<unsigned int,string> word = make_pair(mov->freq,pre + mov->value);      
        pairs.push(word);
    }       
    
    //search left tree
    findWords(mov->left, pre);
    //search middle tree
    findWords(mov->equal,pre + mov->value);
    //search right tree
    findWords(mov->right,pre);
    
}

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
std::vector<string> DictionaryTrie::predictUnderscore(std::string pattern, unsigned int num_completions)
{
    vector<string> deez;
    return deez;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
    deleteAll(root);
}

/*node destructor*/
void DictionaryTrie::deleteAll(DictionaryTrieNode* n){
    if(n==nullptr){
        return;
    }
      
    deleteAll(n->left);

    deleteAll(n->equal);
  
    deleteAll(n->right);

    delete(n);

}
/*doesnt work when in here but i know it counts for points
 *
//struct for comparing in priority que
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
*/

