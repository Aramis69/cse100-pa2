/*  File:BloomFilter.hpp
 *  contains class definition for bloomfilter along with
 *  public and private helper functions.
 *  This bloom filter is useful for hashing string into a array
 *  to later search and see if that string was inserted.
 * */

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>

using namespace std;

/**
 * The class for bloom filter that provides memory efficient check
 * of whether an item has been inserted before. Small amount of 
 * false positives is possible but there will be no false negatives.
 *
 * Sources: Sample_hash_function.docx
 * I took the complex hashStringBUZ, hashPJW and hashStringWeiss1 
 * algorithm and implimented it in my code. 
 *
 */
class BloomFilter {

public:

    /* Create a new bloom filter with the size in bytes */
    BloomFilter(size_t numBytes);

    /* Insert an item into the bloom filter */
    void insert(std::string item);

    /* Determine whether an item is in the bloom filter */
    bool find(std::string item);

    /* Destrctor for the bloom filter */
    ~BloomFilter();

private:

    // The char array as the hash table
    unsigned char* table;
    unsigned int numSlots;
    unsigned int myBytes; 
    // TODO: Add your own data and method here

    //constants for the buz algorithm 
    const unsigned int BUZINIT = 0x7b4402a2;
    static const unsigned int BYTE_WIDTH = 8;
    static const unsigned int WORD_WIDTH = sizeof(int)*BYTE_WIDTH;
    const unsigned int buzS =256;
    //table of constants used in buz hash
    unsigned int BUZ_Table[256] = {
    0xc70bb269, 0x13299943, 0xe9cee5e1, 0x32119a79,
    0xc2365851, 0x169ee8e3, 0x094c1ed8, 0x58e1d4e0,
    0x96eb1762, 0xfe296797, 0x89082f47, 0x27d5078d,
    0x8ebb9de0, 0x14df49e0, 0x38d21c63, 0x1f5b2770,
    0xaa6b0150, 0x7b0b656e, 0x98d37bc2, 0x4d7e85ec,
    0x987910e2, 0xb8cbac89, 0xa3f664a3, 0xeca3003c,
    0x7b364137, 0xb2a6edae, 0x5ef72906, 0x64a9e7b7,
    0x28cd6520, 0xca3c72df, 0x57398ce2, 0x8db893d4,
    0x0a5995cd, 0x2d109fb4, 0x0491162f, 0xb3488737,
    0x6fc4eb03, 0x9903cb21, 0xe82ff831, 0xb03ff8e5,
    0x054836ca, 0x5335e6f8, 0x01396c2a, 0xf9000899,
    0x03ed9d63, 0x2bf6946b, 0x9097fa8b, 0xacd8dfc7,
    0x8488b8a6, 0x0e39cd2e, 0xac1a4517, 0xcd49e035,
    0xe98b7e7b, 0xd3571502, 0xd602805e, 0xe7143cfe,
    0x46db0a6b, 0x0a4c9ebe, 0x4e2e1ca7, 0x3040fc62,
    0xe8818c02, 0x37155e7b, 0xe44ba138, 0x43cacdd4,
    0x53d986ba, 0xdd4dca35, 0x0f680f71, 0x6c1a551e,
    0x74263e95, 0xcfc4f5d5, 0x37b8ef45, 0xc00ac71d,
    0x3b059e0d, 0x208bc754, 0x41335fbe, 0x785a0ffc,
    0x189f024f, 0xd669c2d8, 0xe1b20f87, 0xba2550da,
    0x10167369, 0x85fad38f, 0x97d20e4e, 0x5bc0da5e,
    0x80799570, 0x93eb4058, 0x139042a6, 0x40b34bf6,
    0x15c21dfa, 0x8f852660, 0xa3d20fb3, 0x3d175cf9,
    0x792441a8, 0xdc5e71b5, 0x925f6350, 0x66e8d08b,
    0xc4606b59, 0x85d8b88c, 0x1ea4f459, 0x664f62bc,
    0x77407de3, 0x73d158ca, 0xb76ab172, 0xe9ed1aeb,
    0x93dc2009, 0xeb9da6ac, 0x3d26cf05, 0x675132bc,
    0xc29196fe, 0x2a62486f, 0x914e75e1, 0xa1c31883,
    0x1c28291c, 0xc73c668c, 0xf4ac07e6, 0x87c9a9ac,
    0xb7196ea7, 0x67cb7fa2, 0x55987797, 0x29ce38ea,
    0x427361b3, 0x5b5667a6, 0x68a72fb0, 0xcef8235a,
    0xd06e8f5b, 0x4d3633f5, 0x214d3a19, 0xbd09ec15,
    0x5c61c24b, 0x3928573c, 0x26083ab8, 0x857a5dee,
    0x3203e50c, 0x52a1a713, 0xa8270ee2, 0xdfb643a9,
    0x7797c1f3, 0x0f8ddc9f, 0x9368de21, 0x638ebd4e,
    0xd91808d7, 0x28ce69b8, 0xe424b0ce, 0xfe52fdef,
    0x89126c74, 0xdb5f3d91, 0xba488f47, 0x2b15cdb8,
    0xa517b0f9, 0x53950632, 0x1159546a, 0xe50f65a3,
    0x5f26b5d1, 0x68a3a955, 0xc2b78ea1, 0x49c33701,
    0x45457aee, 0xd49b550a, 0x244379b8, 0xec826af5,
    0x4fa6e0c9, 0xd4633425, 0x82f0bd85, 0xc23ccc2e,
    0xac73e11a, 0xdc94b283, 0x13e59bb2, 0x23b4880e,
    0x1d295c45, 0xef67488c, 0x6b74149e, 0xdf90d4ac,
    0xfc6e65a9, 0x406a3734, 0x86999303, 0xc73e7180,
    0x3c8a0b31, 0x75fa9249, 0xaca5e0e2, 0x4d0cc60d,
    0x4b174606, 0x836fb602, 0x4f9fc83a, 0xe16477a7,
    0xda1506a9, 0x905b28b7, 0x4229f5c2, 0xdf4c9144,
    0x731888e9, 0x2e37421f, 0x0c67c385, 0x44a2e520,
    0xfe3ee655, 0x92547582, 0x9525f4d4, 0xdaa8caf8,
    0xa25bd583, 0x0e315733, 0xd35fea29, 0xc9cfaa0f,
    0xc6bdf7e9, 0xa48b4e01, 0xfd30ffe0, 0xd0f63421,
    0x2b84803d, 0xe1b368a4, 0xbae5daa5, 0x4dd6336a,
    0xb60c4030, 0x7bb552f1, 0xf1b91481, 0xc8929b82,
    0xa1c22bf8, 0xd585aae4, 0x17fb4f6a, 0xa9c0d32e,
    0x2036f9b5, 0x3a95d611, 0xd554f25d, 0x3441153f,
    0x7fa89ff4, 0x8f91241c, 0x4b2cc5a9, 0xd3035a00,
    0x5c80707f, 0xe610fd47, 0xf60958c2, 0xb55a6fe7,
    0x3e1ba335, 0x2dead082, 0x1a8877e8, 0xd0791aad,
    0x9706ee52, 0xfb1dc525, 0x7fa1ba54, 0x6a3e9f81,
    0xa85a906a, 0x86ce1b46, 0x3b05833e, 0xc8d8fdcb,
    0x44e606c5, 0x8807beb2, 0xe46047d3, 0x85b9f5f8,
    0x56ed0cba, 0x3cf4e646, 0x970fd9dd, 0xd0600895,
    0x2d0a5f92, 0x891c4220, 0x017fbfe0, 0x4dde2016,
    0x3a6e421d, 0x7e3f2285, 0xdf7956e3, 0x52fdcf83
    };
    //constant used in WEISS hash function
    const unsigned int WEISS_HASH_SHIFT = 5;
    
    //constants use in PJW hash
    const unsigned int PJW_HASH_SHIFT = 4;    
    const unsigned int PJW_HASH_RIGHT_SHIFT = 24;
    const unsigned int PJW_HASH_MASK = 0xf0000000;    
        
    //buz algorithm functions
    unsigned int hash1(const string& key);
    //buz algorithm helper
    unsigned int hashBUZ(const unsigned char* key,int keylen);
    //Weiss hashfunction
    unsigned int hash2(const string& key);
    //PJW hashfunction
    unsigned int hash3(const string& key);

};

#endif // BLOOM_FILTER
