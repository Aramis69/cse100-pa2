#include "DictionaryTrie.hpp"


/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
    root = nullptr;
}
 
/* 
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
    bool myBool = insertHelp(move,i,word,freq);
    return myBool;
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
            move = move->left;
        }
        //if current char is greater than node
        else if(move->value < word[i]){        
            move = move->right;
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

bool DictionaryTrie::insertHelp(DictionaryTrieNode* move, unsigned int i,
                                string word, unsigned int freq){
    bool boolRet;
    //if current char is less than node
    if(word[i] < move->value){
        //if left is null insert
        if(move->left == nullptr){
            //insert new node with current char val
            move->left  = new DictionaryTrieNode();
            move->left->value = word[i];
            //recursive call
            boolRet = insertHelp(move->left,i,word,freq);   
            //update the max
            setMax(move); 
        }   
        else{     
            //recursive call
            boolRet = insertHelp(move->left,i,word,freq);            
            //update the max
            setMax(move);
        }
    }
    //if current char is greater than node
    else if(move->value < word[i]){
        //if right is null
        if(move->right == nullptr){
            move->right  = new DictionaryTrieNode();
            move->right->value = word[i];
            //recursive call
            boolRet = insertHelp(move->right,i,word,freq);
            //update the max
            setMax(move);
        }
        else{        
            //recursive call
            boolRet = insertHelp(move->right,i,word,freq);
            //update the max
            setMax(move);
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
            //update the max
            setMax(move);
            return true;
        }
        else{   
        //current i is same char as node
            //if the next equal is null
            if(move->equal == nullptr){
                //create node for next char at equal position;
                move->equal = new DictionaryTrieNode();
                move->equal->value = word[i+1];
                //move will then go to this new node
                boolRet = insertHelp(move->equal,i+1,word,freq);
                //update the max
                setMax(move);
            }
            else{
                //when there is still chars in word
                boolRet = insertHelp(move->equal,i+1,word,freq);
                //update the max
                setMax(move);
            }
        }
    }
    return boolRet;
}
void DictionaryTrie::setMax(DictionaryTrieNode* mov){
        //set the maxFrequency
        unsigned int max = mov->freq;
        if(!(mov->left == nullptr)){
            if(max < mov->left->maxFreq){
                max = mov->left->maxFreq;
            } 
        }          
        if(!(mov->equal == nullptr)){
            if(max < mov->equal->maxFreq){
                max = mov->equal->maxFreq;
            } 
        }
        if(!(mov->right == nullptr)){
            if(max < mov->right->maxFreq){
                max = mov->right->maxFreq;
            } 
        }
        mov->maxFreq = max;        
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
    //if word is empty
    if(prefix.length() == 0){
        return myWords;
    }
    //if the tree has no root
    if(root == nullptr){
        return myWords;
    }
    if(num_completions == 0){
        return myWords;
    } 
    //start at root
    DictionaryTrieNode* move = root;
    
    unsigned int i = 0;
    //loop to find position of last char in prefix
    while(i < (prefix.length())){
            
        //if current char is less than node
        if(prefix[i] < move->value){
            move = move->left;
        }
        //if current char is greater than node
        else if(move->value < prefix[i]){        
            move = move->right;
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
    if(move->endOfWord == true){
        //make a pair of the prefix and place in pairs
        pair<unsigned int,string> word = make_pair(move->freq,prefix);      
        minPairs.push(word);
    }
    //find other words from current node
    findWords(move->equal,prefix, num_completions);

    vector<string>::iterator start;
    //move from pairs to myWord vector
    while(!(minPairs.empty())){

        //take top element and insert into vector then remove from que
        pair<unsigned int, string> top = minPairs.top();
        
        //get iterator at begining of vector
        start = myWords.begin();
        //insert top of min que to front
        myWords.insert(start, top.second);
        //take this completion out of minPairs
        minPairs.pop();
    }

    
    return myWords;
}
    
void DictionaryTrie::findWords(DictionaryTrieNode* mov, string pre, unsigned int num){ 

    if(mov == nullptr){
        return;
    }
    //if this is a completed word
    if(mov->endOfWord){
        if(minPairs.size() == num){
            pair<unsigned int,string> top = minPairs.top();   
            if(top.first < mov->freq){
                minPairs.pop();
                pair<unsigned int,string> word = make_pair(mov->freq,pre + mov->value);      
                minPairs.push(word);    
            }
        }
        else{
            //add to minPairs que
            pair<unsigned int,string> word = make_pair(mov->freq,pre + mov->value);      
            minPairs.push(word);
        }
    }       

    //if the priority que is full
    if(minPairs.size() == num){
        /*  only go down if the smallest frequency is smaller than the 
            max of the branch */
        if(mov->left != nullptr){ 
            pair<unsigned int,string> top = minPairs.top();
            if(top.first < mov->left->maxFreq){
                //search left tree
                findWords(mov->left, pre, num);
            }
        }  
    }
    //else traverse regularly
    else{
        //search left tree
        findWords(mov->left, pre, num);
    }

    //if the priority que is full
    if(minPairs.size() == num){
        /*  only go down if the smallest frequency is smaller than the 
            max of the branch */
        if(mov->equal != nullptr){
            pair<unsigned int,string> top = minPairs.top();   
            if(top.first < mov->equal->maxFreq){
                //search middle tree
                findWords(mov->equal,pre + mov->value, num);
            }
        }  
    }
    //else traverse regularly
    else{
        //search middle tree
        findWords(mov->equal,pre + mov->value, num);
    }

    //if the priority que is full
    if(minPairs.size() == num){
        /*  only go down if the smallest frequency is smaller than the 
            max of the branch */
        if(mov->right != nullptr){    
            pair<unsigned int,string> top = minPairs.top();  
            if(top.first < mov->right->maxFreq){
                //search right tree
                findWords(mov->right,pre,num);
            }
        }  
    }
    //else traverse regularly
    else{
        //search right tree
        findWords(mov->right,pre,num);
    }   
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

    bool myBool = true;
    //holds strings i will return
    vector<string> myWords;

    //if the tree has no root
    if(root == nullptr){
        return myWords;
    }
    if(num_completions == 0){
        return myWords;
    } 
    //start at root
    DictionaryTrieNode* move = root;
                
    unsigned int i = 0;
    //loop to find position of last char in prefix
    while(myBool){
        if(pattern[i] == '_'){
            break; 
        }    
        //if current char is less than node
        if(pattern[i] < move->value){
            move = move->left;
        }
        //if current char is greater than node
        else if(move->value < pattern[i]){        
            move = move->right;
        }
        //if current character is equal to node
        else{
            //if move is on the node containing last char of pref
            if(i == (pattern.length()-1)){
                return myWords;   
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

    //call recursive to find underscore parts
    findUnd(move);
    

    /*the following long section handles different cases of where the _ can be
    * the main difference is the way that the string is put back together with
    * its missing underscore part
    *  */
    
    //handle if only underscore was passed in
    if(pattern.length() == 1){
        while(!(potentialComp.empty())){
            //access potential completion to this single underscore 
            DictionaryTrieNode* findN = potentialComp.back();

            if(findN->freq > 0){
                //this case only requires making a string out of the values of out nodes
                pair<unsigned int, string> ins = make_pair(findN->freq,string(1,findN->value));
                minPairs.push(ins);    
                //to only have num_completion amount of completions  
                if(num_completions < minPairs.size()){
                    minPairs.pop();
                }
                //remove from options
                potentialComp.pop_back(); 
            }
            else{
                //remove from options
                potentialComp.pop_back(); 
            }
        }
    }
    //if underscore is at end
    else if(i == pattern.length()-1){ 
        while(!(potentialComp.empty())){

            //to hold current potential completion
            DictionaryTrieNode* findN = potentialComp.back();
            //if this potential completion has a frequence
            if(findN->freq > 0){
                pair<unsigned int,string> ins =  make_pair(findN->freq,
                    pattern.substr(0,(pattern.length()-1)) + string(1,findN->value));
                //add to min que
                minPairs.push(ins);  
  
                //to only have num_completion amount of completions  
                if(num_completions < minPairs.size()){
                    minPairs.pop();
                }
                //remove from potential completions
                potentialComp.pop_back(); 
            }
            else{
                //remove from potential completions
                potentialComp.pop_back(); 
            }
        }     
    }
    //if underscore is at beggining
    else if(i == 0){
        
        while(!(potentialComp.empty())){
        
            //to hold current potential completion
            DictionaryTrieNode* findN = potentialComp.back();
            //search for the remainder of the patter from this node    
            unsigned int freq = completeWord(pattern,findN->equal,i+1);

            if(freq > 0){
                pair<unsigned int,string> ins =  make_pair(freq,
                    string(1,findN->value) + pattern.substr(1,(pattern.length()-1)));
                //add to min que
                minPairs.push(ins); 
                //to only have num_completion amount of completions  
                if(num_completions < minPairs.size()){
                    minPairs.pop();
                }
                //remove from potential completions
                potentialComp.pop_back(); 
            }
            else{
                //remove from potential completions
                potentialComp.pop_back();  
            }
        }
    }
    //if underscore is anywhere else inbetween the string
    else{
        while(!(potentialComp.empty())){
            //to hold current potential completion
            DictionaryTrieNode* findN = potentialComp.back();
            //search for the remainder of the patter from this node    
            unsigned int freq = completeWord(pattern,findN->equal,i+1);

            if(freq > 0){
                pair<unsigned int,string> ins =  make_pair(freq,
                    pattern.substr(0,i) + string(1,findN->value) + 
                    pattern.substr(i+1,(pattern.length()-i)));
                //add to min que
                minPairs.push(ins); 
                //to only have num_completion amount of completions  
                if(num_completions < minPairs.size()){
                    //eliminate the less frequent completion
                    minPairs.pop();
                }
                //remove from potential completions
                potentialComp.pop_back(); 
            }
            else{
                //remove from potential completions
                potentialComp.pop_back();  
            }
        
                
        }

    }
    vector<string>::iterator start;

    while(!(minPairs.empty())){
        //access pair with lowest freq from minPairs
        pair<unsigned int,string> word = minPairs.top();
        //get iterator at begining of vector
        start = myWords.begin();
        //insert top of min que to front
        myWords.insert(start, word.second);
        //remove this from minPairs
        minPairs.pop();
        
    }

    return myWords;
}



//helper to fill a priority que with all possible fillers to the blank
void DictionaryTrie::findUnd(DictionaryTrieNode* mov){ 

    if(mov == nullptr){
        return;
    }
         
    potentialComp.push_back(mov);    
   
    //search left tree
    findUnd(mov->left);
    //search right tree
    findUnd(mov->right);
    
}

//return true if this "underscore" value completes the word
unsigned int DictionaryTrie::completeWord(string word,DictionaryTrieNode* here, unsigned int x){
    
    DictionaryTrieNode* move = here;

    //if the node moved to is null
    if(move == nullptr){
        return 0;
    }

    bool myBool = true;
   
    //i was ++ before passed in to g _a is on a and not _
    while(myBool){
    
        //if current char is less than node
        if(word[x] < move->value){
            move = move->left;
        }
        //if current char is greater than node
        else if(move->value < word[x]){        
            move = move->right;
        }
        //if current character is equal to node
        else{
            //if move is on the node containing last char of pref
            if(x == (word.length()-1)){
                
                return move->freq;   
            }
            else{
                move = move->equal; 
                x++;
            }
        }
        
        //if the node moved to is null
        if(move == nullptr){
            return 0;
        }
    }
    return 0;
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
//doesnt work when in here but i know it counts for points
 
