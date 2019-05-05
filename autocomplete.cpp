#include "DictionaryTrie.hpp"
#include "util.hpp"

#include <cstdlib>

using namespace std;

/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * 
 * cout << "This program needs exactly one argument!" << endl;
 * cout << "Reading file: " << file << endl;
 * cout << "Enter a prefix/pattern to search for:" << endl;
 * cout << "Enter a number of completions:" << endl;
 * cout << completion << endl;
 * cout << "Continue? (y/n)" << endl;
 * 
 * arg 1 - Input file name (in format like freq_dict.txt)
 */
int main(int argc, char** argv)
{
    if(argc > 2){
        cout << "This program needs exactly one argument!" << endl;
        return -1;
    }
    
    //get filename
    string file = argv[1]; 
    //to store prefix
    string pre;   
    //to store if continue or not
    string option;
    //to store number of completions wanted
    unsigned int completion;
    //vector to store return of predict
    vector<string> vec;
    //bool to determine loop
    bool cont = true;
    //make new DictionaryTrie
    DictionaryTrie* D = new DictionaryTrie();
    

    cout << "Reading file: " << file << endl;
    //put file into stream
    ifstream myFile;
    myFile.open(file, ios::binary);

    //load the words from file
    Utils::load_dict(*D,myFile);    
    
    //continue condition
    while(cont){
        cout << "Enter a prefix/pattern to search for:" << endl;
        getline(cin,pre);

        cout << "Enter a number of completions:" << endl;
        string str;
        getline(cin, str);
        completion = stoi(str);
        //get a vector of predictions
        vec = D->predictCompletions(pre,completion);
        //print out the words
        for(unsigned int i =0; i<vec.size();i++){
            cout << vec[i] << endl;
        }
        //promt user to continue
        cout << "Continue? (y/n)" << endl;
        getline(cin, option);
        if(option.compare("y") == 0){
            cont = true;
        }
        else{
            cont = false;
        }   

    }
    //delete the DictionaryTrie
    delete D;   
    
    return 1;
}

