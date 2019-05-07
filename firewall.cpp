#include <iostream>
#include <fstream>
#include "BloomFilter.hpp"

using namespace std;

/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * cout << "This program requires 3 arguments!" << endl;
 * 
 * arg1 - list of malicious urls/bad words filter out
 * arg2 - list of mixed (good/bad) to only write good urls to
 * arg3 - file to write only the good urls to (one on each line)
 */

int main(int argc, char** argv) {
    //check for correct amount of arguments
    if(argc != 4){
        cout << "This program requires 3 arguments!" << endl;
        return -1;
    }
    //holds the bad urls 
    string file = argv[1];
    //holds mix of urls file
    string urls = argv[2];
    //holds urls being inserted
    string line;

    //to count amount of bad URLS
    unsigned int sizeB = 0;
    unsigned int bsizeByte = 0;
    // counts amount of bad URLs we are going to insert
    ifstream myFile;
    myFile.open(file);
    while (getline(myFile,line)){
        //calculate the amount of bytes in string
        bsizeByte = bsizeByte + (line.length());
        //number of bad urls
        sizeB++;
    }    
    myFile.close();
    //end counting

    string ins;
    //create bloom filter with size of bad URLS
    BloomFilter* B = new BloomFilter(sizeB);
    //get from bad urls
    ifstream insFile;
    insFile.open(file);
    //hash the bad urls into the filter
    while (getline(insFile,ins)){
        B->insert(ins);
    }
    insFile.close();
    //end inserting

    //open the outputFile to write to
    ofstream outputFile;
    outputFile.open(argv[3]);

    string ur;
    //bool to check if a url is in Bloom
    bool inBloom = false;
    //to count the size of URLS
    unsigned int sizeU = 0;
    //counts how many URLs get outputted
    unsigned int out = 0;

    //to write good urls to output and count lines
    ifstream uFile;
    uFile.open(urls);
    //count lines in URLS
    while (getline(uFile,ur)){
        inBloom = B->find(ur);
        if(inBloom == false){
            //count how many get written
            out++;
            //write line to file
            outputFile << line << endl;
        }
        sizeU++;
    }
    
    outputFile.close();
    uFile.close();
   
    //here i will calculte values such as false positive rate
    //and saved memory ration 
    unsigned int safe;
    //total urls - badurls gives only good urls
    safe = sizeU-sizeB;
    double falseP = (double)(safe-out)/(double)safe;

    double mem =(double)bsizeByte/(double)((sizeB*3)/2);

    cout << "False positive rate: " << falseP << endl;

    cout << "Saved memory ratio: " << mem << endl;

    delete(B);
}
