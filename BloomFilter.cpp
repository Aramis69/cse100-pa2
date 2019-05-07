#include "BloomFilter.hpp"
#include <math.h>

/* Main hashfunction for buz Algorithm
 *
 * Sourced from Bob uzgalis lecture note in Sample_hash_functions
 */
unsigned int BloomFilter::hash1(const string& key){
    
    unsigned int hashValue = BUZINIT;
    for(string::const_iterator i = key.begin(); i != key.end();i++){
        unsigned int ch = *i;
        if(hashValue & (1 << (WORD_WIDTH -1))){
            hashValue = ((hashValue <<1) | 1)^BUZ_Table[ch%buzS];
        }
        else{
            hashValue = (hashValue << 1) ^ BUZ_Table[ch%buzS];   
        }
    }
    hashValue = hashBUZ((unsigned char*)&hashValue,sizeof hashValue);
    return hashBUZ((unsigned char *)&hashValue, sizeof hashValue);
    
}

/* Helper function for hashStringBuz
 *
 * sourced from Bob uzgalis lecture note in Sample_hash_functions
 * */
unsigned int BloomFilter::hashBUZ(const unsigned char* key,int keylen){
    unsigned int hashValue = BUZINIT;
    while(--keylen >= 0){
        unsigned int ch = *key++;
        if(hashValue & (1 << (WORD_WIDTH -1))){
            hashValue = (hashValue <<1 | 1)^BUZ_Table[ch%buzS];
        }
        else{
            hashValue = (hashValue << 1) ^ BUZ_Table[ch%buzS];
        }
        return hashValue;
    }
    return hashValue;
}

/* My second hashfunction
 *
 * Sourced from WEISS hashfuntion
 * */
unsigned int BloomFilter::hash2(const string& key){
    
    
    unsigned int hashValue = 0;
    
    for(string::const_iterator i = key.begin(); i != key.end();i++){
        hashValue = hashValue ^ ( hashValue << WEISS_HASH_SHIFT)^(unsigned)*i;
    }
    return hashValue;
    
}

/* My third hashfunction
 *
 * Sourced from PJW hash function 
 * */
unsigned int BloomFilter::hash3(const string& key){
    unsigned int hashValue = 0;
    for(string::const_iterator i = key.begin(); i != key.end(); i++){
        hashValue = (hashValue << PJW_HASH_SHIFT)+(unsigned)*i;
        unsigned int rotate_bits = hashValue & PJW_HASH_MASK;
        hashValue ^= rotate_bits | (rotate_bits >> PJW_HASH_RIGHT_SHIFT);
    }
    return hashValue;
}

/* Create a new bloom filter with the size in bytes */
BloomFilter::BloomFilter(size_t numBytes)
{   
    //initialize the size of the table
    unsigned int size = (ceil ((numBytes*3)/2) );
    myBytes = size;
    table = new unsigned char[size]();
    //set the numSlots
    numSlots = BYTE_WIDTH*numBytes; 
    
}

/* Insert an item into the bloom filter */
void BloomFilter::insert(std::string item) 
{
    //insert with first function
    unsigned int hashVal = (hash1(item));
    unsigned int index = hashVal % myBytes;
    table[index] |= (1 << hashVal % BYTE_WIDTH);
    
    //insert with second function
    hashVal = (hash2(item));
    index = hashVal % myBytes;
    table[index] |= (1 << hashVal % BYTE_WIDTH);
    
    //insert with third function
    hashVal = (hash3(item));
    index = hashVal % myBytes;
    table[index] |= (1 << hashVal % BYTE_WIDTH);
}    
    

/* Determine whether an item is in the bloom filter */
bool BloomFilter::find(std::string item) 
{
    //call first function
    unsigned int hashVal = (hash1(item));

    //get index
    unsigned int index = hashVal % myBytes;

    unsigned char bit = (table[index] >> (hashVal%BYTE_WIDTH)) & 1;
    //if the bit was not set
    if(bit == 0){
        return false;
    }
    
    //search second function
    hashVal = (hash2(item));

    //get index
    index = hashVal % myBytes;

    bit = (table[index] >> (hashVal%BYTE_WIDTH)) & 1;
    //if the bit was not set
    if(bit == 0){
        return false;
    }

    //search third function
    hashVal = (hash3(item));

    //get index
    index = hashVal % myBytes;

    bit = (table[index] >> (hashVal%BYTE_WIDTH)) & 1;
    //if the bit was not set
    if(bit == 0){
        return false;
    }
        
    return true;
}

/* Destrctor for the bloom filter */
BloomFilter::~BloomFilter()
{
    //call to delete the char array with set bits
    delete(table);
}
